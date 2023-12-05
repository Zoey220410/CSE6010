#include "collision.h"

int main(int argc, char *argv[]){
	char *filename = argv[1];
	FILE *file;
	file = fopen(filename, "r");  // read the file data
	
	int num, i;
	double r, lx, ly;
	fscanf(file, "%d %lf %lf %lf", &num, &r, &lx, &ly); 
	
	Particle* particles = (Particle *)malloc(num * sizeof(Particle));
    Collision* collisions = (Collision *)malloc(num * (num + 1) / 2 * sizeof(Collision));
	
	//Save the information of each particle in the struct array 
	i = 0;
	double data1, data2, data3, data4;
	while(fscanf(file, "%lf %lf %lf %lf\n", &data1, &data2, &data3, &data4) == 4){
		particles[i] = createParticle(data1, data2, data3, data4);
		i++;
	}
	fclose(file);
	
	double threshold = atof(argv[2]);
	
	calculateInitialCollisions(particles, collisions, num, lx, ly, r);  // calculate initial collision, including colliding with wall and particles
	while(1){
		sortCollisions(collisions, num); // at the start or after each update, the collision time needs to be sorted to find the earlist one
		if(collisions[0].time > threshold){ // check whether the earliest collision happens after the end time
			updateFinalPos(particles, threshold, num);
			break;  
		}
		processParticles(particles, collisions[0], num); // update the position and velocity of particles which are invovled in the collision 
		updateCollisions(particles, collisions, num, lx, ly, r);  // update all collisions that contain particles from the last collision
	}
	
	for(int i = 0; i < num; i++){
		printf("%.6f, %.6f, %d, %d\n", particles[i].xpos, particles[i].ypos, particles[i].cwall, particles[i].cpart); // output the result
	}
	
	free(particles);
	free(collisions);
}

Particle createParticle(double data1, double data2, double data3, double data4){
	/* Record the particle position, velocity, update time and number of collisions.*/
	Particle newParticle;  
	newParticle.xpos = data1;  // particle position
	newParticle.ypos = data2;
	newParticle.u = data3;  // particle velocity
	newParticle.v = data4;
	newParticle.lastUpdateTime = 0;
	newParticle.cwall = 0;  // number of collisions
	newParticle.cpart = 0; 
	return newParticle;
}