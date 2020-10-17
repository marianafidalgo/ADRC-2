#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int count = 0;
// Create a new node
struct node* createNode(char *name) {

  struct node* newNode = (struct node*)malloc(sizeof(struct node));
  newNode->name = malloc(strlen(name) *sizeof(char));

  strcpy(newNode->name, name);

  newNode->id = count;
  newNode->next = NULL;


  return newNode;
}

// Create a graph of V vertices
struct Graph* createGraph(int v) {
  struct Graph* graph = malloc(sizeof(struct Graph));

  graph->num_V = v;
  graph->it = 0;

// Create vertical array of nodes (size v)
  graph->a_list =  (struct A_List *)malloc( v*sizeof(struct A_List));

  graph->visited =  malloc( v*sizeof(int));

  for (int i = 0; i <= v; i++){
    graph->a_list[i].head = NULL;
    graph->visited[i] = 0;

  }

  return graph;
}

/* Adds an edge to a graph*/
void addEdge(struct Graph* graph, char * src, char * dest, int v){

    //i create destination vertex and source vertex
    printf("%s, %s\n", src, dest);
    struct node* desti = createNode(dest);//
    struct node* source = createNode(src);
    struct node * temp;

    //empty list
    if (graph->it == 0)
    {
      graph->a_list[0].head=source;
      graph->a_list[0].head->next=desti;
      ++(graph->it);

    }
    else{

      for (int i = 0; i <= (graph->it); i++){
        //adj empty

        temp = graph->a_list[i].head;
        if(temp == NULL){
          graph->a_list[i].head=source;
          graph->a_list[i].head->next=desti;
          ++(graph->it);
          break;

        }
        else if(strcmp(temp->name, src) == 0 ){
            desti->next=temp->next;
            temp->next =desti;

            break;
        }
      }
    }


}

// Print the graph
void printGraph(struct Graph* graph)
{
    struct node* pCrawl;

    for (int i = 0; i <= graph->it; i++){
      pCrawl = graph->a_list[i].head;
      while(pCrawl)
      {
          printf(" %s   ", pCrawl->name);
          pCrawl=pCrawl->next;
      }
      printf("\n");
    }
}

int * BFS(struct Graph* graph, int size){

  //visited list

  //fifo list
  struct Queue *q;
  q->array = malloc( sizeof q->array * size );
  if ( q->array )
  {
    q->size =size;
    q->count = 0;
    q->head = 0;
    q->tail = 0;
  }


  struct node* pCrawl = graph->a_list[0].head;

  //int id_init = pCrawl->id;

  graph->visited[0]= 1;

  push_queue(q, 0);

  while(q->count != -1){
    int id = pop_queue(q);
    printf("Visited: %d\n", id);

    struct node* temp = graph->a_list[id].head;

    while(temp){
      int adjV = 0;//temp->id;
      if (graph->visited[adjV] == 0) {
        graph->visited[adjV] = 1;
        push_queue(q, adjV);
      }
      temp = temp->next;
    }
  }

  return graph->visited;
}

int connected(struct Graph* graph, int n_nodes) {

    int discovered[n_nodes];
    //pick node from graph
    int * visited = BFS(graph, n_nodes );
    int gc = 1;
    for(int i = 0; i< n_nodes; i++)
      if(visited[i] == 0)
        gc = 0;

    return gc;
}

int push_queue( struct Queue *q, int new_id )
{

  if ( q->count == q->size )
  {
    // queue full, handle as appropriate
    return 0;
  }
  else
  {
    q->array[q->tail] = new_id;
    q->count++;
    q->tail++;
  }
}

int pop_queue( struct Queue *q )
{
  int item;
  if ( q->count == 0 )
  {
    // queue is empty
    item = -1;
    return 0;
  }
  else
  {
    item = q->array[q->head];
    q->head++;
    q->count--;
  }

  return item;
}
