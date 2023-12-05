#include "collision.h"

void processParticles(Particle* particles, Collision firstCollision, int num){
	/*update collided particles' pos, velocity, and record the update time.*/
	int i = firstCollision.p1;
	int j = firstCollision.p2;
	double t = firstCollision.time;
		
	particles[i].xpos = particles[i].xpos + particles[i].u * (t - particles[i].lastUpdateTime); //update position
	particles[i].ypos = particles[i].ypos + particles[i].v * (t - particles[i].lastUpdateTime);
	particles[i].lastUpdateTime = firstCollision.time;
	
	if(j > 0){
		/* if two particles collides, update both particles' pos and velocity.*/
		particles[j].xpos = particles[j].xpos + particles[j].u * (t - particles[j].lastUpdateTime); // update position
		particles[j].ypos = particles[j].ypos + particles[j].v * (t - particles[j].lastUpdateTime);
		particles[j].lastUpdateTime = firstCollision.time;
		
		swap(&particles[i].u, &particles[j].u);  // update speed
		swap(&particles[i].v, &particles[j].v);
		
		particles[i].cpart++;  // record collision number
		particles[j].cpart++;
		
	} else if(j % 2 != 0){
		/* collide with left or right wall*/
		particles[i].u = -particles[i].u; // update speed
		particles[i].cwall++;   // record collision number
		
	} else {
		/* collide with top or bottom wall*/
		particles[i].v = -particles[i].v; // update speed
		particles[i].cwall++;  // record collision number
	}		
}

void swap(double *a, double *b){
	/*Swap the values of two variables*/
	double temp = *a;
	*a = *b;
	*b = temp;
}

void updateFinalPos(Particle* particles, double threshold, int num){
	/* Update the position and lastUpdateTime of each particle to the value at the threshold time point. */
	for(int i = 0; i < num; i++){
		particles[i].xpos = particles[i].xpos + (threshold - particles[i].lastUpdateTime) * particles[i].u;
		particles[i].ypos = particles[i].ypos + (threshold - particles[i].lastUpdateTime) * particles[i].v;
		particles[i].lastUpdateTime = threshold;
	}
}