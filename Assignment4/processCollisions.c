#include "collision.h"

void calculateInitialCollisions(Particle* particles, Collision* collisions, int num, double lx, double ly, double r){
	/*Calculate the initial collision array*/
	double x, y, u, v, t_wall;
	int c = 0;
	for(int i = 0; i < num; i++){
		collisions[c++] = calculateWallCollision(particles[i], 0, lx, ly, r, i); // the collisions of each particle with the wall.
		for(int j = i + 1; j < num; j++){
			collisions[c++] = calculateParticleCollision(particles[i], particles[j], i, j, r); // the collisions of each particle with each of the other particles
		}
	}
}

void updateCollisions(Particle* particles, Collision* collisions, int num, double lx, double ly, double r){
	/* find the collisions included particles that invovled in last collision and update them*/
	int m, n;
	Collision firstCollision = collisions[0];
	for(int i = 0; i < (num+1)*num/2; i++){
		// find the collisions included particles that invovled in last collision
		if(collisions[i].p1 == firstCollision.p1 || collisions[i].p1 == firstCollision.p2 || collisions[i].p2 == firstCollision.p1 || collisions[i].p2 == firstCollision.p2){
			if(collisions[i].p1 < 0 || collisions[i].p2 < 0){
				m = max(collisions[i].p1, collisions[i].p2);
				if(m == firstCollision.p1 || m == firstCollision.p2){
					collisions[i] = calculateWallCollision(particles[m], firstCollision.time, lx, ly, r, m); // update wall collision
				} else{
					continue;
				}
			} else{
				m = collisions[i].p1;
				n = collisions[i].p2;
				if((m == firstCollision.p1 && n == firstCollision.p2) || (m == firstCollision.p2 && n == firstCollision.p1)){
					collisions[i] = createCollision(m, n, INFINITY);
				} else {
					collisions[i] = calculateParticleCollision(particles[m], particles[n], m, n, r); // update particle collision
				}
			}
		}
	}
}

int max(int a, int b){
	/* Find the larger of the two values*/
	 return (a > b) ? a : b;
}

Collision createCollision(int i, int j, double t){
	/*Record the number and time of the two objects involved in the collision*/
	Collision newCollision;
	newCollision.p1 = i;
	newCollision.p2 = j;
	newCollision.time = t;
	return newCollision;
}

Collision calculateParticleCollision(Particle p1, Particle p2, int i, int j, double r){
	/*Determine whether two particles can collide, and if so, record the minimum time required for the collision and the particles number.
	The particles are numbered 0~N-1.*/
	
	//Updates the particle position so that they are both at the last updated time point.
	double time;
	if(p1.lastUpdateTime > p2.lastUpdateTime){  
		p2.xpos = p2.xpos + p2.u * fabs(p1.lastUpdateTime - p2.lastUpdateTime);
		p2.ypos = p2.ypos + p2.v * fabs(p1.lastUpdateTime - p2.lastUpdateTime);
		time = p1.lastUpdateTime;
	} else{
		p1.xpos = p1.xpos + p1.u * fabs(p1.lastUpdateTime - p2.lastUpdateTime);
		p1.ypos = p1.ypos + p1.v * fabs(p1.lastUpdateTime - p2.lastUpdateTime);
		time = p2.lastUpdateTime;
	}
	
	// set t = tc - tr, time equaltion: (x1-x2+(u1-u2)t)^2 + (y1-y2+(v1-v2)t)^2 = 4R^2 
	double a, b, c, d, equal_a, equal_b, equal_c;
	a = p1.xpos - p2.xpos;
	b = p1.u - p2.u;
	c = p1.ypos - p2.ypos;
	d = p1.v - p2.v;   
	
	// time equaltion: (b^2+d^2)t^2+(2ab+2cd)t+(a^2+c^2-4R^2) = 0
	equal_a = b * b + d * d;
	equal_b = 2 * a * b + 2 * c * d;
	equal_c = a * a + c * c- 4 * r * r;
	 
	double root1, root2, discriminant;
	discriminant = equal_b * equal_b - 4 * equal_a * equal_c;
	
	// Check if the equaltion has root. When two particles can not collide, set the time to infinity.
	if(discriminant < 0){   
		time = INFINITY;
		return createCollision(i, j, time);
	} 
	
	root1 = (-equal_b + sqrt(discriminant)) / (2 * equal_a);
	root2 = (-equal_b - sqrt(discriminant)) / (2 * equal_a);
	
	// choose the postive and smallest root
	if (root1 > 0 && (root2 <= 0 || root1 < root2)) { 
        time = root1 + time;
    } else if (root2 > 0) {
        time = root2 + time;
    } else {  
        time = INFINITY;   // If there is no positove root, set the time to infinity.
    }
	
	return createCollision(i, j, time);
}

Collision calculateWallCollision(Particle p, double lastUpdateTime, double lx, double ly, double r, int i){
	/*Compare the time the particle hits the wall in the x-axis and y-axis and record the smaller value and the number of the wall. 
	The left, bottom, right, top walls are numbered -1, -2, -3, -4.*/
	double t, x, y, u, v;
	int wall;
	x = p.xpos;
	y = p.ypos;
	u = p.u;
	v = p.v;
	if(u > 0 && v > 0){
		if((lx - r - x) / u < (ly - r - y) / v){
			t = (lx - x - r) / u;
			wall = -3;
		}
		else{
			t = (ly - r - y) / v;
			wall = -4;
		}
	}
	else if(u > 0 && v < 0){
		if((lx - r - x) / u < (r - y) / v){
			t = (lx - x -r) / u;
			wall = -3;
		}
		else{
			t = (r - y) / v;
			wall = -2;
		}
	}
	else if(u < 0 && v > 0){
		if((r - x) / u < (ly - r - y) / v){
			t = (r - x) / u;
			wall = -1;
		}
		else{
			t = (ly - r - y) / v;
			wall = -4;
		}
	}
	else{
		if((r - x) / u < (r - y) / v){
			t = (r - x) / u;
			wall = -1;
		}
		else{
			t = (r - y) / v;
			wall = -2;
		}
	}
	return createCollision(i, wall, t+lastUpdateTime);
}