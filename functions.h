#ifndef FUNC_H
#define FUNC_H

#define MAX_NODES 65536

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
    int * queue; //stores sons of visited nodes
    int * tier1; //stores tier-1 nodes
    int n_tier1;
    size_t count; //n_items in queue
    size_t head; //location to pop from
    size_t tail;  //location to push from
};

struct Graph *graph;

struct node* createNode(int id_node, int type);
struct Graph* createGraph();
struct Queue* createQ(int v);
void addEdge(struct Graph* graph, int src, int dest, int type);
void printGraph(struct Graph* graph);
void connected(struct Graph* graph);
int findTier1(struct Graph* graph);
void CommerciallyConn(struct Graph* graph);
struct Graph* BFS(struct Graph* graph);
int pop_queue(struct Graph* graph);
int push_queue(struct Graph* graph, int a);
int DFS_cycles(struct Graph* graph, int v, int curr, int curr_path[], int stack[]);
void checkCycles(struct Graph* graph);
void freeAll(struct Graph* graph);

//name funct BFS
// name funct CONNECTED

#endif