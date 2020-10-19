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

  newNode->id = 0;
  newNode->next = NULL;

  return newNode;
}

// Create a graph of V vertices
struct Graph* createGraph(int v) {

  struct Graph* graph = malloc(sizeof(struct Graph));

  graph->num_V = 0;
  graph->it = 0;

// Create vertical array of nodes (size v)
  graph->a_list = malloc(v * sizeof(struct node));

  graph->visited =(char**) malloc(v * sizeof(char*));

  for(int i=0; i < v ; ++i )
  {
      graph->visited[i] = (char*) malloc(10*sizeof(char)); //2 is for the letter and null terminator
      strcpy(graph->visited[i] , "");
      graph->a_list[i] = NULL;
  }

  graph->queue = (char**) malloc(v * sizeof(char*));

  for(int i=0; i < v ; ++i )
  {
      graph->queue[i] = (char*) malloc(10*sizeof(char)); //2 is for the letter and null terminator
      strcpy(graph->queue[i] , "");
  }

    graph->size =v;
    graph->count = 0;
    graph->head = 0;
    graph->tail = 0;


  return graph;
}


/* Adds an edge to a graph*/
void addEdge(struct Graph* graph, char * src, char * dest){

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
        else if(strcmp(temp->name, src) == 0){
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

struct Graph* BFS(struct Graph* graph, int size){

  int flag = 0;
  int id_visited = 0;
  //fifo list

  struct node* temp = graph->a_list[0];

  push_queue(graph, graph->a_list[0]->name);

  while (graph->count != 0){

    graph->visited[id_visited] = pop_queue(graph);

    for(int i = 0; i <= size; i++)
    {

      if(graph->a_list[i] == NULL){
        break;
      }
      else if(strcmp(graph->visited[id_visited] ,graph->a_list[i]->name ) == 0){
        temp = graph->a_list[i];
        temp=temp->next;
        break;
      }
    }
    flag = 0;
    while(temp)
    {
      for(int i = 0; i <= size; i++)
      {
        if(strcmp(temp->name,graph->queue[i])== 0){
          flag = -1;
          break;
        }

        if(strcmp("",graph->queue[i])== 0)
          break;
      }

      if(flag ==0){
        push_queue(graph, temp->name);
      }
      temp=temp->next;
    }

    id_visited++;
  }

  return graph;

}

int connected(struct Graph* graph, int size, int nodes) {
    //pick node from graph
    graph = BFS(graph, size);

    int gc = 1;
    printf("nodes %d\n", nodes);
    for(int i = 0; i< nodes; i++){
      if(graph->visited[i] == ""){
        gc = 0;
      }
    }
    return gc;
}

int push_queue(struct Graph* graph, char* new_id )
{

  if ( graph->count == graph->size )
  {
    // queue full, handle as appropriate
    return 0;
  }
  else
  {
    strcpy(graph->queue[graph->tail] , new_id);
    graph->count++;
    graph->tail++;
  }
}

char * pop_queue( struct Graph* graph )
{
  char* item;
  if ( graph->count == 0 )
  {
    // queue is empty

    return 0;
  }
  else
  {
    strcpy(item , graph->queue[graph->head]);
    graph->head++;
    if(graph->head > graph->tail)
    {
      //reset queue
      graph->head = graph->tail = 0;
    }
    graph->count--;
  }

  return item;
}
