#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>
#include "shortpath.h"

Vertex* createVertex(FILE* file, int num_vertex){
	/* Record every vertexes and edges, and then initial the path and its distance*/
	
	// Initializtion the distance and path
	Vertex* vertexes = (Vertex*)malloc(num_vertex * sizeof(Vertex));
	for (int i = 0; i < num_vertex; i++) {
			vertexes[i].d = INFINITY;
			vertexes[i].p = -1;
	}
	
	vertexes[0].d = 0; // the distance from source to source is 0
	
	return vertexes;
}

Edge* createEdge(FILE* file, int num_edge){
	/* Record every vertexes and edges, and then initial the path and its distance*/

	Edge* edges = (Edge*)malloc(num_edge * sizeof(Edge));
	//create the edge struct array
	for(int i = 0; i < num_edge; i++){
		fscanf(file, "%d %d %lf", &(edges[i].src), &(edges[i].dest), &(edges[i].weight));
	}
	
	return edges;
}


bool relax(Edge e, Vertex* vertexes){
	/* Compare the distance to find the shortest path and then update*/
	Vertex u = vertexes[e.src];
	Vertex v = vertexes[e.dest];
	double w = e.weight;

	if(u.d != INFINITY && u.d + w < v.d){
		vertexes[e.dest].d = u.d + w;
		vertexes[e.dest].p = e.src; // record its former node on the path
		return true;
	}
	return false;
}

void printShortPath(Vertex* vertexes, int dest_specify, int num){
	/* Print the output, including outputing the specified vertex and all the vertexes path. */
	if(dest_specify != -1){
		//print the specified vertex's shortest path
		printf("%d: %.5lf;", dest_specify, vertexes[dest_specify].d);
		output(dest_specify, vertexes);
		printf("\n");
	}
	else{
		// print all the vertexes' shortest path
		for(int i = 0; i < num; i++){
			printf("%d: %.5lf;", i, vertexes[i].d);
			output(i, vertexes);
			printf("\n");
		}
	}
}

void output(int v, Vertex* vertexes){
	/* Traversal the path from the end to the source, and put every node
	into a linked-list, so that it can be tranversed. */
	Res* dummyHead = createNode(-1);
	int cur = v;
	Res *node, *temp, *newNode;
	node = createNode(v);
	dummyHead->next = node;
	
	while(vertexes[cur].p != -1){
		newNode = createNode(vertexes[cur].p);
		// insert the new node between the dummy head and the true first node
		temp = dummyHead->next;
		dummyHead->next = newNode;
		newNode->next = temp;
		cur = vertexes[cur].p;
	}
	
	// print the result and free the linked-list memory
	Res* res_cur = dummyHead->next;
	free(dummyHead);
	while(res_cur){
		printf(" %d", res_cur->v);
		temp = res_cur->next;
		free(res_cur);
		res_cur = temp;
	}
}

Res* createNode(int v){
	/* Initial a new node. */
	Res* node = (Res*)malloc(sizeof(Res));
	node->v = v;
	node->next = NULL;
	return node;
}
	

int main(int argc, char* argv[]) {
	
    char *filename = argv[1];
	FILE *file;
	file = fopen(filename, "r");
	
	int num_edge, num_vertex;
	fscanf(file, "%d %d", &(num_vertex), &(num_edge));
	
	// read the file data to create the graph, including vertexs and edges
    Vertex* vertexes = createVertex(file, num_vertex);
	Edge* edges = createEdge(file, num_edge);
    fclose(file);

	int source = 0;
    int dest_specify = (argc == 4) ? atoi(argv[3]) : -1;
	
	// set the parallel parameters
	int num_threads = atoi(argv[2]);
    omp_set_num_threads(num_threads);
	
	double start_time, end_time, elapsed_time;
	elapsed_time = 0;
	
	/* "flag" is used to check whether the distance is updated,
	if one vertex's path is updated, the flag will be set to true
	and the whole edges array needs to be traversed again. */
	int flag = 1;
	start_time = omp_get_wtime(); // record the start time
    while(flag == 1){
		flag = 0;
		// use parallel omp to run the traversal loop
		#pragma omp parallel for reduction(max: flag)
		{
			for(int i = 0; i < num_edge; i++){
				if(relax(edges[i], vertexes)){
					#pragma omp atomic write
					flag = 1;
				}
			}
		}
	}
	
	end_time = omp_get_wtime(); // record the end time
	elapsed_time = elapsed_time + end_time - start_time; // calculate the running time
	
	// output the result
	printShortPath(vertexes, dest_specify, num_vertex);
	printf("%.5lf\n", elapsed_time);
	
	// free the memory
    free(edges);
	free(vertexes);

    return 0;
}
