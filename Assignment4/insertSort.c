#include "collision.h"

void sortCollisions(Collision* collisions, int num){  
	/* Sort the time in collision using insertion sort in order to find the earliest collision time */
	for(int i = 0; i < num * (num + 1) / 2; i++){
		Collision temp = collisions[i];
		int j;
		for(j = i-1; j >=0 && collisions[j].time > temp.time; j--){
			collisions[j+1] = collisions[j];
		}
		collisions[j+1] = temp;
	}
}