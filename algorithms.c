#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int count = 0;
// Create a new node
struct node* createNode(char *name) {

  struct node* newNode = malloc(sizeof(struct node));
  newNode->name = malloc(strlen(name)+1);

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
  graph->a_list = malloc(v * sizeof(struct node));

  graph->visited = malloc(v * sizeof (int *));


  for (int i = 0; i <= v; i++){
    graph->a_list[i] = NULL;
    graph->visited[i] = 0;

  }

  return graph;
}

struct Queue* createQ(int v)
{
  struct Queue *q = malloc(sizeof(struct Queue));

  q->array = malloc (v*sizeof (int*));

  if ( q->array )
  {
    q->size =v;
    q->count = 0;
    q->head = 0;
    q->tail = 0;
  }
  return q;
}



/* Adds an edge to a graph*/
void addEdge(struct Graph* graph, char * src, char * dest, int v){

    //i create destination vertex and source vertex
    struct node* desti = createNode(dest);//
    struct node* source = createNode(src);
    struct node * temp;

    //empty list
    if (graph->it == 0)
    {
      graph->a_list[0]=source;
      graph->a_list[0]->next=desti;
      ++(graph->it);

    }
    else{

      for (int i = 0; i <= (graph->it); i++){
        //adj empty

        temp = graph->a_list[i];
        if(temp == NULL){
          graph->a_list[i]=source;
          graph->a_list[i]->next=desti;
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
    struct node* temp;

    for (int i = 0; i <= graph->it; i++){
      temp = graph->a_list[i];
      while(temp)
      {
          printf(" %s   ", temp->name);
          temp=temp->next;
      }
      printf("\n");
    }
}

void BFS(struct Graph* graph, int size){

  int next = 0;
  int id_name_pos = 0;
  //fifo list
  struct Queue* q = createQ(size);

  char * id_name[size];

  struct node* temp = graph->a_list[0];

  id_name[id_name_pos] = temp->name;

  push_queue(q, 0);
  printf("Visited: %d\n", id_name_pos); //-> corresponde a um name

  while (q->count != 0){

    int id = pop_queue(q);

    for(int i = 0; i <= size; i++)
    {
      if(graph->a_list[i] == NULL){
        break;
      }
      else if(id_name[id] == graph->a_list[i]->name && graph->visited[i] == 0){
        temp = graph->a_list[i];
        break;
      }
    }
    while(temp)
    {
        if (graph->visited[id_name_pos] == 0) {
          if(id_name_pos<= size){
            id_name[id_name_pos] = temp->name;
          }
          graph->visited[id_name_pos] = 1;
          printf("Visited: %d\n", id_name_pos); //-> corresponde a um name
          push_queue(q, id_name_pos);
          if(id_name_pos<= size)
            id_name_pos++;
        }
        temp=temp->next;

    }
  }
  free(q->array);
  free(q);

}

int connected(struct Graph* graph, int n_nodes) {
    //pick node from graph
    BFS(graph, n_nodes);
    int gc = 1;
    for(int i = 0; i< n_nodes; i++){
      if(graph->visited[i] == 0){
        gc = 0;
      }
    }
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
    if(q->head > q->tail)
    {
      //reset queue
      q->head = q->tail = 0;
    }
    q->count--;
  }

  return item;
}
