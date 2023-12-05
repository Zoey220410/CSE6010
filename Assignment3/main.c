#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dfs.h"

int main(int argc, char *argv[])
{
	char *filename = argv[1];
	FILE *file;
	file = fopen(filename, "r");  // read the file data
	
    int num;
	fscanf(file, "%d", &num); // the total number of nodes
	
	Node** adjList = (Node**)malloc(num * sizeof(Node*)); // create a adjacency list
	for(int i=0; i<num; i++){
		adjList[i] = (Node*)malloc(sizeof(Node));
		adjList[i]->value = -1;  // set dummy head
		adjList[i]->next = NULL;
	}
	
	bool occasional = atoi(argv[2]) > 1; // to distinguish the infection type
	int from, to, label;
	while(fscanf(file, "%d %d %d", &from, &to, &label) == 3) {
		if(!occasional && label == 2) continue;  // ignore this connect
		Node* newNode = (Node*)malloc(sizeof(Node));  // inset the neighbor to the adjacency list
		newNode->value = to;
		newNode->next = adjList[from]->next;
		adjList[from]->next = newNode;
    } 

    fclose(file);
	
	int component = dfsGraph(adjList, num);
	
	printf("%d\n", component); // output the number of the components
	
	freeList(adjList, num); 
}

int dfsGraph(Node** adjList, int num){
	int *visited = (int*)malloc(num * sizeof(int)); // record the vertex status
	for(int i=0; i<num; i++){
		visited[i] = 0;    // at start, the vertex is not visited
	}
	
	int result = 0;
	for(int i=0; i<num; i++){
		if(visited[i] == 0){  // apply dfs algorithm to each node that has not been visited
			result += 1;  // it means the last component search ends and start the next component
			dfs(adjList, i, visited);			
		}
	}
	free(visited);
	return result;
}
	
void dfs(Node** adjList, int i, int* visited){
	visited[i] = 1;
	Node* cur = adjList[i]->next;
	while(cur){  // tranverse all the adjacency vertex
		if(!visited[cur->value]){
			dfs(adjList,cur->value ,visited);
		}
		cur = cur->next;
	}
}

void freeList(Node** adjList, int num){
	for(int i=0; i<num; i++){  
		Node* cur = adjList[i];
		while(cur){   // free all the neighbor nodes
			Node* temp = cur->next;
			free(cur);
			cur = temp;
		}
	}
	free(adjList);
}
	


