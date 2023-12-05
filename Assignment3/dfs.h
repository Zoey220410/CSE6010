typedef struct node {
	int value;
	struct node* next;
} Node;

int dfsGraph(Node** adjList, int num);
void dfs(Node** adjList, int i, int *visited);
void freeList(Node** adjList, int num);


