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
    int * tier1; //stores tier-1 nodes
    int n_tier1;
};

struct Queue {
  int * array; //stores sons of visited nodes
  size_t count; //n_items in queue
  size_t head; //location to pop from
  size_t tail;  //location to push from
};

struct Graph *graph;
struct Queue *queue;

struct node* createNode(int id_node, int type);
struct Graph* createGraph();
struct Queue* createQueue();
void addEdge(struct Graph* graph, int src, int dest, int type);
void printGraph(struct Graph* graph);
void connected(struct Graph* graph, struct Queue * queue);
int findTier1(struct Graph* graph);
void CommerciallyConn(struct Graph* graph);
struct Graph* BFS(struct Graph* graph, struct Queue * queue);
int pop_queue(struct Queue* queue);
int push_queue(struct Queue* queue, int a);
int DFS_cycles(struct Graph* graph, int v, int curr, int curr_path[], int stack[]);
void checkCycles(struct Graph* graph);
void freeAll(struct Graph* graph, struct Queue * queue);

void bridges(struct Graph* graph, int u, int  visited[], int disc[], int l[], int pred[]);
void find_bridges(struct Graph* graph);


//name funct BFS
// name funct CONNECTED

#endif