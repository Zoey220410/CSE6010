// Find diameter using All-pairs shortest paths
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "graph.h"

// #define DEBUG

//===================== Function Prototypes ===========================
void PrepareGraph(int* mygraph);
int calcIterations();
void CalcShortestPaths(int* mygraph);
int CalcDiameter(int* mygraph);
void PrintGraph(int* mygraph);

//========================= Main Function ===========================
int main() {
// initialize the graph here; note it is a 1-dimensional array	
	int* mygraph = (int *) malloc(sizeof(int) * NVERT * NVERT);
	getGraph(mygraph);

	int i, j, k;

#ifdef DEBUG
	printf("\nThe adjacency matrix is\n");
	PrintGraph(mygraph);
#endif

// prepare the graph/array for the all-pairs algorithm
	PrepareGraph(mygraph);

#ifdef DEBUG
	printf("\nThe matrix for calculating all-pairs shortest paths is\n");
	PrintGraph(mygraph);
#endif
	
// set up outer iteration
	int niterations = calcIterations();
#ifdef DEBUG
	printf("number of iterations = %d\n",niterations);
#endif

// calculate shortest paths	
	for(int iiteration = 0; iiteration < niterations; iiteration++) {
#ifdef DEBUG
		printf("\nouter iteration %d:\n",iiteration);
		
#endif
		CalcShortestPaths(mygraph);
	} 
	
#ifdef DEBUG
	printf("\nThe graph diameter is ");
#endif
	printf("%d\n",CalcDiameter(mygraph));

	free(mygraph);
	return 0;
}

//===================== Function Definitions ===========================

// store "Infinity" values (INT_MAX) where there are no edges, other than from each edge to itself
void PrepareGraph(int* mygraph) {
	for(int i = 0; i < NVERT; i++){
		for(int j = 0; j < NVERT; j++){
			if(i == j){
				mygraph[i*NVERT + j] = 0;
			}
			else if(mygraph[i*NVERT + j] == 0){
				mygraph[i*NVERT + j] = INT_MAX;
			}

		}
	}
}

int calcIterations() {
	return (int)ceil(log(NVERT-1)/log(2));
}

// calculate the lengths of all shortest paths using the "matrix multiplication" method
void CalcShortestPaths(int* mygraph) {
	int *temp = (int *) malloc(sizeof(int) * NVERT * NVERT);
	int minDistance;

	for(int i = 0; i < NVERT; i++){
		for(int j = 0; j < NVERT; j++){
			minDistance = INT_MAX;
			temp[i*NVERT+j] = mygraph[i*NVERT+j];
			for (int k = 0; k < NVERT; k++){
				if(mygraph[i*NVERT+k] == INT_MAX || mygraph[k*NVERT+j] == INT_MAX){
					continue;
				}
				else if(mygraph[i*NVERT+k] + mygraph[k*NVERT+j] < minDistance){
					minDistance = mygraph[i*NVERT+k] + mygraph[k*NVERT+j];
				}
			}
			temp[i*NVERT+j] = minDistance;	
		}
	}
	for(int i = 0; i < NVERT; i++){
		for(int j = 0; j < NVERT; j++){
			mygraph[i*NVERT+j] = temp[i*NVERT+j];
		}
	}
	free(temp);
}

// calculate the diameter of the graph as the maximum of the minimum distances
int CalcDiameter(int* mygraph) {
	int maxDistance = 0;
	for(int i = 0; i < NVERT*NVERT; i++){
		if(mygraph[i] != INT_MAX && mygraph[i] > maxDistance ){
			maxDistance = mygraph[i];
		}
	}
	return maxDistance;
}

// print all array entries as an adjacency matrix
void PrintGraph(int* mygraph) {
	for (int i = 0; i < NVERT; i++) {
		for (int j = 0; j < NVERT; j++) {
			printf("%d ", mygraph[i*NVERT+j]);
		}
		printf("\n");
	}
}