#include "dfs.h"

void freeMemory(Graph* graph, int* visited)
{
	for(int i=0; i<graph->num; i++){  // free all the neighbor nodes
		Node* cur = graph->adjList[i];
		while(cur){
			Node* temp = cur->next;
			free(cur);
			cur = temp;
		}
	}
	
	free(graph->adjList);   // free the neighbor list array
	free(graph); 
	free(visited);  // free the visited status array
}