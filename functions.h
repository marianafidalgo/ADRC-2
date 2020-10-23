#ifndef FUNC_H
#define FUNC_H

#define MAX_NODES 65536

struct node {
  int name;
  int type;
  int counted;
  struct node *next;
};

struct node *desti, *source, *newNode, *temp, *pCrawl;

struct Graph {
    int num_V;
    int it;
    struct node ** a_list; //adjacency list
    int * visited; //stores visited nodes
    int * queue; //stores sons of visited nodes
    int * tier1; //stores tier-1 nodes
    int * path;
    size_t size; // max size of queue
    size_t count; //n_items in queue
    size_t head; //location to pop from
    size_t tail;  //location to push from
};

struct Graph *graph;

struct node* createNode(int id_node, int type);
struct Graph* createGraph(int v);
struct Queue* createQ(int v);
void addEdge(struct Graph* graph, int src, int dest, int type);
void printGraph(struct Graph* graph);
int connected(struct Graph* graph, int size);
void CheckComm(struct Graph* graph, int size);
struct Graph* BFS(struct Graph* graph, int size);
int pop_queue(struct Graph* graph);
int push_queue(struct Graph* graph, int a);
int DFS(struct Graph* graph, int v, int discovered[]);
int checkCycles(struct Graph* graph);

//name funct BFS
// name funct CONNECTED

#endif