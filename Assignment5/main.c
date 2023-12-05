#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

#define INFTY INT_MAX

// Structure to represent an edge in the graph
struct Edge {
    int src, dest;
    double weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Function to initialize the graph with given edges
void initializeGraph(struct Graph* graph, FILE* file) {
    // Read the number of vertices and edges
    fscanf(file, "%d %d", &(graph->V), &(graph->E));

    // Allocate memory for edges
    graph->edges = (struct Edge*)malloc(graph->E * sizeof(struct Edge));

    // Read edges from the file
    for (int i = 0; i < graph->E; i++) {
        fscanf(file, "%d %d %lf", &(graph->edges[i].src), &(graph->edges[i].dest), &(graph->edges[i].weight));
    }
}

// Function to print the solution for a single destination vertex
void printShortestPath(int dest, double distance, int* path, int path_length) {
    printf("%d: %.5f; ", dest, distance);
    for (int i = 0; i < path_length; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

// Parallel Bellman-Ford algorithm
void bellmanFord(struct Graph* graph, int src, int num_threads, int dest_vertex) {
    int V = graph->V;
    int E = graph->E;
    double* dist = (double*)malloc(V * sizeof(double));
    int* parent = (int*)malloc(V * sizeof(int));
    int* path = (int*)malloc(V * sizeof(int));

    // Initialize distances from source to all other vertices as INFINITY
    for (int i = 0; i < V; i++) {
        dist[i] = (i == src) ? 0.0 : INFTY;
        parent[i] = -1;
    }

    double start_time = omp_get_wtime();
    int flag;  // Flag to check if any changes were made

    // Parallel Bellman-Ford algorithm
    for (int k = 0; k < V - 1; k++) {
        flag = 0;

#pragma omp parallel for num_threads(num_threads) reduction(|:flag)
        for (int i = 0; i < E; i++) {
            int u = graph->edges[i].src;
            int v = graph->edges[i].dest;
            double weight = graph->edges[i].weight;

            if (dist[u] != INFTY && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                flag = 1;
            }
        }

        // If no updates were made in this iteration, break early
        if (!flag) {
            break;
        }
    }

    double end_time = omp_get_wtime();

    // Output shortest path information
    if (dest_vertex != -1) {
        // Output for a single destination vertex
        int path_length = 0;
        int current_vertex = dest_vertex;

        // Reconstruct the path
        while (current_vertex != -1) {
            path[path_length++] = current_vertex;
            current_vertex = parent[current_vertex];
        }

        // Print the calculated distances
        printShortestPath(dest_vertex, dist[dest_vertex], path, path_length);
    } else {
        // Output for all vertices
        for (int i = 0; i < V; i++) {
            int path_length = 0;
            int current_vertex = i;

            // Reconstruct the path
            while (current_vertex != -1) {
                path[path_length++] = current_vertex;
                current_vertex = parent[current_vertex];
            }

            // Print the calculated distances
            printShortestPath(i, dist[i], path, path_length);
        }
    }

    // Print elapsed time
    printf("%.5f\n", end_time - start_time);

    free(dist);
    free(parent);
    free(path);
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Usage: %s <filename> <num_threads> [dest_vertex]\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    char* filename = argv[1];
    int num_threads = atoi(argv[2]);
    int dest_vertex = (argc == 4) ? atoi(argv[3]) : -1;

    // Open the file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }

    // Create and initialize the graph
    struct Graph* graph = createGraph(0, 0);
    initializeGraph(graph, file);

    // Close the file
    fclose(file);

    int source = 0;

    // Set the number of threads
    omp_set_num_threads(num_threads);

    printf("Parallel Bellman-Ford Algorithm\n");
    bellmanFord(graph, source, num_threads, dest_vertex);

    free(graph->edges);
    free(graph);

    return 0;
}
