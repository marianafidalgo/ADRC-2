#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void freeAll(struct Graph* graph){
  struct node * temp;

  for (int i = 0; i < MAX_NODES; i++){
    while(graph->a_list[i] != NULL){
      printf("no %d        ", i);
      temp = graph->a_list[i];
      printf("free %d\n", temp->name);
      graph->a_list[i] = graph->a_list[i]->next;
      free(temp);
    }
  }

  free(graph->visited);
  free(graph->queue);
  free(graph->tier1);
  free(graph->curr_path);
  free(graph->a_list);
  free(graph);
}
int count = 0;
// Create a new node
struct node* createNode(int id_node, int type) {

  struct node* newNode = malloc(sizeof(struct node));

  newNode->name = id_node;
  newNode->counted = 0;
  newNode->type = type;
  newNode->next = NULL;

  return newNode;
}

// Create a graph of V vertices
struct Graph* createGraph() {

  struct Graph* graph = malloc(sizeof(struct Graph));

  graph->num_V = 0;
  graph->it = 0;

// Create vertical array of nodes (size v)
  graph->a_list = (struct node **) malloc(MAX_NODES * sizeof(struct node *));
  graph->visited =(int*) malloc(MAX_NODES * sizeof(int*));
  graph->queue = (int*) malloc(MAX_NODES * sizeof(int*));
  graph->tier1 = (int*) malloc(MAX_NODES * sizeof(int*));
  graph->curr_path = (int*) malloc(MAX_NODES * sizeof(int*));

  for(int i = 0; i < MAX_NODES ; ++i )
  {
    graph->visited[i] = 0;
    graph->a_list[i] = NULL;
    graph->queue[i] = 0;
    graph->tier1[i] = 0;
  }

  graph->count = 0;
  graph->head = 0;
  graph->tail = 0;

  return graph;
}

/* Adds an edge to a graph*/
void addEdge(struct Graph* graph, int src, int dest, int type){

    //create destination vertex and source vertex
    struct node* source;
    struct node* desti;
    struct node* temp;

    if(type == 1){
      source = createNode(src, 1);
      desti = createNode(dest, 3);
    }
    else{
      source = createNode(src, 2);
      desti = createNode(dest, 2);
    }

    temp = graph->a_list[src];
    if(temp == NULL){
      graph->a_list[src] = desti;
      (graph->num_V)++;
      if( graph->a_list[dest] == NULL && type != 2){
        graph->a_list[dest] = source;
        (graph->num_V)++;
      }
      else if(type != 2){
        source->next = graph->a_list[dest]->next;
        graph->a_list[dest]->next = source;
      }
    }
    else{
      desti->next = graph->a_list[src]->next;
      graph->a_list[src]->next = desti;
      if( graph->a_list[dest] == NULL && type != 2){
          graph->a_list[dest] = source;
          (graph->num_V)++;
      }
      else if(type != 2){
        source->next = graph->a_list[dest]->next;
        graph->a_list[dest]->next = source;
      }
    }
}

// Print the graph
void printGraph(struct Graph* graph)
{
  struct node* temp;
  for (int i = 1; i < MAX_NODES; i++){
    temp = graph->a_list[i];
    if(temp != NULL){
      printf("%d ->"      , i);
      while(temp){
        printf(" %d,%d -> ", temp->name, temp->type);
        temp = temp->next;
      }
      printf("\n");
    }
  }
}

struct Graph* BFS(struct Graph* graph_){

  int flag = 0;
  int id_visited = 0;
  //fifo list
  struct Graph* graph = graph_;
  struct node* temp = graph->a_list[0];

  for(int i = 1; i < MAX_NODES; i++)
  {
    if(graph->a_list[i] != NULL){
      push_queue(graph, graph->a_list[i]->name);
      break;
    }
  }

  while (graph->count != 0){
    int id_pop = pop_queue(graph);
    graph->visited[id_pop] = 1;

    temp = graph->a_list[id_pop];

    flag = 0;
    while(temp)
    {
      for(int i = 1; i < MAX_NODES; i++)
      {
        if(temp->name == graph->queue[i]){
          flag = -1;
          break;
        }

        if(graph->queue[i] == 0)
          break;
      }

      if(flag == 0){
        push_queue(graph, temp->name);
      }
      flag = 0;
      temp = temp->next;
    }
  }

  return graph;
}

int connected(struct Graph* graph) {
  //pick node from graph
  int n_nos = 0;

  graph = BFS(graph);

  int gc = 0;

  for(int i = 1; i < MAX_NODES; i++){
    if(graph->visited[i]==1)
      n_nos++;
    if( n_nos == graph->num_V){
      gc = 1;
      break;
    }
  }

  return gc;
}

int findTier1(struct Graph * graph)
{
  struct node* temp;
  int count = 0;
  int n_of_tiers1 = 0;
  int n_of_peers_T1 = 0;

  graph->tier1[0] = -2;
  for(int i = 1; i < MAX_NODES; i++){
    graph->tier1[i] = -1;
  }

    for (int i = 1; i < MAX_NODES; i++){
      if(count == graph->num_V)
        break;
      if(graph->a_list[i] == NULL){
        continue;
      }
      temp = graph->a_list[i];
      if(graph->tier1[i] == -1){
        graph->tier1[i] = 1;
        (graph->n_tier1)++;
      }
      while(temp)
      {
        if(temp->type == 3 && graph->tier1[temp->name] != 0){
          if(graph->tier1[temp->name]== 1)
            (graph->n_tier1)--;
          graph->tier1[temp->name] = 0;
        }
        temp=temp->next;
      }
      count++;
    }
}

int CommerciallyConn(struct Graph* graph)
{
  struct node* temp;
  int flag = 0;
  int peert1 = 0;
  int tier1 = 0;

  for(int i = 1; i < MAX_NODES; i++){
    if(graph->tier1[i] == 1){
      temp = graph->a_list[i];
      while(temp){
        if(temp->type == 2 && graph->tier1[temp->name] == 1){
          peert1++;
        }
        temp = temp->next;
      }
      if(graph->n_tier1 - 1 != peert1){
        flag = -1;
        break;
      }
    }
    peert1 = 0;
  }

  return flag;
}

int push_queue(struct Graph* graph, int new_id )
{
  // if ( graph->count == graph->size )
  // {
  //   // queue full, handle as appropriate
  //   return 0;
  // }
  // else
  // {
    graph->queue[graph->tail] = new_id;
    graph->count++;
    graph->tail++;
  //}
}

int pop_queue( struct Graph* graph )
{
  int item = -1;
  if ( graph->count == 0 )
  {
    // queue is empty
    return 0;
  }
  else
  {
    item = graph->queue[graph->head];
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

int DFS_cycles(struct Graph* graph, int v, int discovered[], int curr, int stack[]){
  struct node* temp;
  int cycle = 0, i = 0, j = 0;

  discovered[v] = 1;
  graph->curr_path[v] = 1;
  stack[curr] = v;
  curr++;

  temp = graph->a_list[v];
  while(temp){
    if(temp->type == 3 && graph->curr_path[temp->name] == 1){
      printf("The internet is not commercially acyclic\nCycle: ");
      for(i = 0; i < MAX_NODES; i++){
        if(stack[i] == temp->name)
          break;
      }
      for(j = i; j < MAX_NODES; j++){
        if(stack[j] != 0){
          printf("%d ", stack[j]);
        }
        else
          break;
      }
      printf("\n");
      cycle = 1;
      return cycle;
    }
    if(discovered[temp->name] == 0 && temp->type == 3){
      cycle = DFS_cycles(graph, temp->name, discovered, curr, stack);
      if(cycle == 1)
        return 1;
    }
    temp = temp->next;
  }

  graph->curr_path[v] = 0;

  return cycle;
}

void checkCycles(struct Graph* graph){

  int discovered[MAX_NODES];
  int stack[MAX_NODES];
  int curr = 0;
  int cycle = 0;
  int i;

  for(i = 0; i < MAX_NODES; i++){
    discovered[i] = 0;
    stack[i] = 0;
    graph->curr_path[i] = 0;
  }

  findTier1(graph);

  for(i = 1; i < MAX_NODES; i++){
    if(graph->tier1[i] == 1){
      if(discovered[i] == 0)
        cycle = DFS_cycles(graph, i, discovered, curr, stack);
    }
  }

  if(cycle == 0)
    printf("The internet is commercially acyclic\n");
}