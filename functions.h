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
    struct node ** a_list; //adjacency list
    int * visited; //stores visited nodes
    int * tier1; //stores tier 1 nodes
    int n_tier1; //number of tier 1 nodes
};

struct Queue {
  int * array; //stores sons of visited nodes
  int count; //number of items in queue
  int head; //location to pop from
  int tail;  //location to push from
};

struct StrongCC {
  int id;
  int * array;
  struct StrongCC *next;
};

struct Graph *graph;
struct Queue queue;

struct node * createNode(int id_node, int type);
struct Graph* createGraph();
struct Queue* createQueue();
struct StrongCC * createSCC();
void addEdge(struct Graph* graph, int src, int dest, int type);
void printGraph(struct Graph* graph);
void BFS(struct Graph* graph, struct Queue * queue);
void connected(struct Graph* graph, struct Queue * queue);
int findTier1(struct Graph* graph);
int pop_queue(struct Queue* queue);
int push_queue(struct Queue* queue, int a);
void DFSbridges(struct Graph* graph, int u, int disc[], int l[], int pred[], int *time, int *bi);
void find_bridges(struct Graph* graph);
int DFS_cycles(struct Graph* graph, int v, int curr, int curr_path[], int stack[]);
void checkCycles(struct Graph* graph);
int DFS_normal(struct Graph * graph, int v, int curr, int curr_path[], int stack[], int * last);
void DFS_inversed(struct Graph * graph, int v, int *curr_path);
void NoTier1_CommerciallyConn(struct Graph * graph);
void CommerciallyConn(struct Graph* graph);
void freeAll(struct Graph* graph, struct Queue * queue);

#endif