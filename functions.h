#ifndef FUNC_H
    #define FUNC_H


struct node {
  char* name;
  int id;
  struct node *next;
};

struct node *desti, *source, *newNode, *temp, *pCrawl;

struct A_List {
  char* name;
  struct node *head;
};

struct Graph {
    int num_V;
    int it;
    struct A_List* a_list;
    int *visited;
};

struct Graph *graph;

struct Queue{
    int *array; //store the data
    size_t size; // max size of queue
    size_t count; //n_items in queue
    size_t head; //location to pop from
    size_t tail;  //location to push from
};

struct node* createNode(char *id_node);
struct Graph* createGraph(int v);
void addEdge(struct Graph* graph, char * src, char * dest, int v);
void printGraph(struct Graph* graph);

int connected(struct Graph* graph, int n_nodes);

int * BFS(struct Graph* graph, int size);
int pop_queue( struct Queue *q );
int push_queue( struct Queue *q, int new_id );


//struct Queue *initArray(int size);




//name funct BFS
// name funct CONNECTED


#endif