#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct particle{
	double xpos, ypos;
	double u, v;
	double lastUpdateTime;
	int cwall, cpart;
}Particle;

typedef struct collision{
	int p1, p2;
	double time;
}Collision;

Particle createParticle(double data1, double data2, double data3, double data4);
void calculateInitialCollisions(Particle* particles, Collision* collisions, int num, double lx, double ly, double r);
void updateCollisions(Particle* particles, Collision* collisions, int num, double lx, double ly, double r);
Collision calculateParticleCollision(Particle p1, Particle p2, int i, int j, double r);
Collision createCollision(int i, int j, double t);
Collision calculateWallCollision(Particle p, double lx, double lastUpdateTime, double ly, double r, int i);
void sortCollisions(Collision* collisions, int num);
void swap(double *a, double *b);
void processParticles(Particle* particles, Collision lastCollision, int num);
int max(int a, int b);
void updateFinalPos(Particle* particles, double threshold, int num);