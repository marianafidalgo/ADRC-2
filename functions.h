#ifndef FUNC_H
#define FUNC_H

#define MAX_NODES 65536
#define min(A,B) ((A)<=(B)?(A):(B))

struct node {
  int name;
  int type;
  struct node *next;
};

struct node *desti, *source, *newNode, *temp, *pCrawl;

struct Graph {
    int num_V; // number of nodes
    struct node ** a_list_c; //adjacency list
    struct node ** a_list_r; //adjacency list
    struct node ** a_list_p; //adjacency list
    int * a_list; //adjacency list
    int * visited; //stores visited nodes
    int * tier1; //stores tier 1 nodes
    int n_tier1; //number of tier 1 nodes
    int * l;
};

struct Queue {
  int * array; //stores sons of visited nodes
  int count; //number of items in queue
  int head; //location to pop from
  int tail;  //location to push from
};

struct Graph *graph;
struct Queue queue;

struct node * createNode(int id_node, int type);
struct Graph* createGraph();
struct Queue* createQueue();
void addEdge(struct Graph* graph, int src, int dest, int type);
void printGraph(struct Graph* graph);
void BFS(struct Graph* graph, struct Queue * queue);
int findTier1(struct Graph* graph);
int pop_queue(struct Queue* queue);
int push_queue(struct Queue* queue, int a);
int DFS_normal(struct Graph * graph, int v, int curr, int curr_path[], int stack[], int * last);
void CommerciallyConn(struct Graph* graph);
void check_length(struct Graph * graph, struct Queue * queue);
void Dijkstra(struct Graph * graph, struct Queue * queue, int src, int** length, int *curr_type);
void freeAll(struct Graph* graph, struct Queue * queue);

#endif
