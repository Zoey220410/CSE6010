#include <stdio.h>
#include <stdlib.h>

void vertexDegrees(int *graph, int n) {
    int degree[2][n];
 
    for (int i = 0; i < 2; i++) {
		for (int j = 0; j < n; j++){
			degree[i][j] = 0;           // the first row is in-degree and the second row is out-degree
		}
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i*n+j] == 1) {
                degree[1][i]++;        // calculate vertex degrees
                degree[0][j]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d: %d, %d\n", i, degree[0][i], degree[1][i]);  // output result
    }
}


void pathsFind(int *graph, int n) {
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (graph[u*n+v] == 1) {
                for (int w = 0; w < n; w++) {
                    if (graph[v*n+w] == 1 && u != w) {
                        printf("%d %d %d\n", u, v, w);
                    }
                }
            }
        }
    }
}

int main() {
    FILE *file = fopen("testgraph.txt", "r");
    if (file == NULL) {
        perror("The file can not be opened.");
        return 1;
    }

    int num;
	fscanf(file, "%d", &num);
	int *graph = (int *)malloc(num * num * sizeof(int));
	if (graph == NULL){
		perror("fail to allocate memory");
		return 1;
	}

    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            fscanf(file, "%d", &graph[i*num+j]);
        }
    }
    fclose(file);

    vertexDegrees(graph, num);     // Calculate the in-degree and out-degree of each vertex
    pathsFind(graph, num);     // Find 2-hop paths with distinct vertices

    free(graph);
    return 0;
}
