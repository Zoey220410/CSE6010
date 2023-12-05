#include "dfs.h"


void dfs(int* graph, int i, int* visited){
	visited[i] = 1;
	for(int j=0; j<num; j++){
		if(graph[i*num+j] != 0 && visited[i*num+j] == 0){
			dfs(graph, j, visited);
		}
	}
}