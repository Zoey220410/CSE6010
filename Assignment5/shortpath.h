typedef struct vertex{
	double d;  // record the distance
	int p;   // record the path
}Vertex;

typedef struct edge{
	int src, dest;  // represent source and destination
	double weight;   
}Edge;

typedef struct res{
	int v;  // record the distance
	struct res* next;   // record its former node number on the path
}Res;

Edge* createEdge(FILE* file, int num_edge);
Vertex* createVertex(FILE* file, int num_vertex);
bool relax();
void printShortPath(Vertex* vertexes, int dest_specify, int num);
void output(int v, Vertex* vertexes);
Res* createNode(int v);