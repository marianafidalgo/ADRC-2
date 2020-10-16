#ifndef FUNC_H
    #define FUNC_H


struct node {
  int id;
  struct node *next;
};
struct node* createNode(int);

struct A_List {
  int n;
  struct node *head;
};

struct Graph {
    int num_V;
    struct A_List* array;
};

struct node* createNode(int v);
struct Graph* createGraph(int v);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);




//name funct BFS
// name funct CONNECTED

#endif