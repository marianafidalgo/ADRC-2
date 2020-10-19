#ifndef FUNC_H
    #define FUNC_H


struct node {
  char* name;
  int id;
  struct node *next;
};

struct node *desti, *source, *newNode, *temp, *pCrawl;

struct Graph {
    int num_V;
    int it;
    struct node ** a_list;
    char **visited;

    char **queue; //store the data
    size_t size; // max size of queue
    size_t count; //n_items in queue
    size_t head; //location to pop from
    size_t tail;  //location to push from
};

struct Graph *graph;

struct Queue{

};

struct node* createNode(char *id_node);
struct Graph* createGraph(int v);
struct Queue* createQ(int v);
void addEdge(struct Graph* graph, char * src, char * dest);
void printGraph(struct Graph* graph);

int connected(struct Graph* graph, int size, int nodes);

struct Graph* BFS(struct Graph* graph, int size);
char* pop_queue( struct Graph* graph );
int push_queue( struct Graph* graph, char * );




//name funct BFS
// name funct CONNECTED


#endif