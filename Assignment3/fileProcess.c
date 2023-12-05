#include <stdlib.h>
#include "dfs.h"

Graph* createGraph(int num) {
    Graph* graph = (int*)malloc(num * num * sizeof(int));
    return graph;
}

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addConnect(Graph* graph, int src, int dest, int label, bool occasional) {
	if(!occasional && label == 2) return;  // ignore this connect
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];  // insert the new node at the head of the adjList
    graph->adjList[src] = newNode;
}