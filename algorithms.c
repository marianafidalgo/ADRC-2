#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int count = 0;
// Create a new node
struct node* createNode(int id_node) {

  struct node* newNode = malloc(sizeof(struct node));

  newNode->name = id_node;

  newNode->counted = 0;
  newNode->type = 0;
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

  graph->visited =(int*) malloc(v * sizeof(int*));
  graph->queue = (int*) malloc(v * sizeof(int*));

  for(int i=0; i < v ; ++i )
  {
      graph->visited[i] = 0;
      graph->a_list[i] = NULL;
      graph->queue[i] = 0;
  }

    graph->size =v;
    graph->count = 0;
    graph->head = 0;
    graph->tail = 0;


  return graph;
}


/* Adds an edge to a graph*/
void addEdge(struct Graph* graph, int src, int dest, int type){

    //i create destination vertex and source vertex
    struct node* desti = createNode(dest);
    struct node* source = createNode(src);
    struct node * temp;

    temp = graph->a_list[src];
    if(temp == NULL){
      graph->a_list[src] = source;
      graph->a_list[src]->next = desti;
      (graph->num_V)++;
    }
    else{
      desti->next=temp->next;
      temp->next =desti;
    }

    // //empty list
    // if (graph->it == 0)
    // {
    //   source ->type = 1;
    //   graph->a_list[0]=source;
    //   if(type == 1)
    //     desti->type = 3;
    //   else
    //     desti->type = 2;

    //   graph->a_list[0]->next=desti;
    //   ++(graph->it);

    // }
    // else{

    //   for (int i = 0; i <= (graph->it); i++){
    //     //adj empty

    //     temp = graph->a_list[i];
    //     if(temp == NULL){
    //       source ->type = 1;
    //       if(type == 1)
    //         desti->type = 3;
    //       else
    //         desti->type = 2;
    //       graph->a_list[i]=source;
    //       graph->a_list[i]->next=desti;
    //       ++(graph->it);
    //       break;

    //     }
    //     else if(strcmp(temp->name, src) == 0){
    //         if(type == 1)
    //           desti->type = 3;
    //         else
    //           desti->type = 2;
    //         desti->next=temp->next;
    //         temp->next =desti;
    //         break;
    //     }
    //   }
    // }
}

// Print the graph
void printGraph(struct Graph* graph)
{
    struct node* temp;

    for (int i = 0; i <= graph->size; i++){
      temp = graph->a_list[i];
      if(temp!= NULL && temp->name != 0){
        while(temp)
        {
            printf(" %d,%d   ", temp->name, temp->type);
            temp=temp->next;
        }
        printf("\n");
      }
    }
}

struct Graph* BFS(struct Graph* graph_, int size){

  int flag = 0;
  int id_visited = 0;
  //fifo list
  struct Graph* graph = graph_;
  struct node* temp = graph->a_list[0];

  for(int i = 0; i < size; i++)
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
    temp=temp->next;

    flag = 0;
    while(temp)
    {
      for(int i = 0; i <= size; i++)
      {
        if(temp->name == graph->queue[i]){
          flag = -1;
          break;
        }

        if(graph->queue[i]== 0)
          break;
      }

      if(flag ==0){
        push_queue(graph, temp->name);
      }
      flag = 0;
      temp=temp->next;
    }
  }

  return graph;

}

int connected(struct Graph* graph, int size, int nodes) {
    //pick node from graph
    int n_nos = 0;
    printf("Connected\n");
    //n_nos = CheckComm(graph, size);

    graph = BFS(graph, size);

    int gc = 0;

    for(int i = 1; i <= size; i++){
      if(graph->visited[i]==1)
        n_nos++;
      if( n_nos == graph->num_V){
        gc = 1;
        break;
      }
    }
    printf("nos %d, numv %d\n", n_nos, graph->num_V);

    return gc;
}

// int CheckComm(struct Graph* graph, int size)
// {
//   struct node* temp;
//   int tier1[size];
//   int nodes = 0;

//   for(int i = 0; i< size; i++){
//     tier1[i] = -1;
//   }

//     for (int i = 0; i <= size; i++){
//       if(graph->a_list[i] == NULL){
//         break;
//       }
//       temp = graph->a_list[i];
//       if(tier1[atoi(temp->name)] == -1){
//         tier1[atoi(temp->name)] = 1;
//         nodes++;
//       }
//       temp=temp->next;
//       while(temp)
//       {
//           if(temp->type != 2 && tier1[atoi(temp->name)] != 0){
//             tier1[atoi(temp->name)]=0;
//             nodes++;
//           }
//           temp=temp->next;
//       }
//     }

//   return  nodes;
// }


int push_queue(struct Graph* graph, int new_id )
{

  if ( graph->count == graph->size )
  {
    // queue full, handle as appropriate
    return 0;
  }
  else
  {
    graph->queue[graph->tail] = new_id;
    graph->count++;
    graph->tail++;
  }
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
    item =graph->queue[graph->head];
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
