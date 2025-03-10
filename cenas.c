#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int curr_last = 0;
int scc_i = 0;
// Create a new node
struct node* createNode(int id_node, int type) {

  struct node* newNode = malloc(sizeof(struct node));

  newNode->name = id_node;
  newNode->type = type;
  newNode->next = NULL;

  return newNode;
}

// Create a graph of V vertices
struct Graph* createGraph() {

  struct Graph* graph = malloc(sizeof(struct Graph));

  graph->num_V = 0;

  // Create vertical array of nodes (size MAX_NODES)
  graph->a_list_c = (struct node **) malloc(MAX_NODES * sizeof(struct node *));
  graph->a_list_r = (struct node **) malloc(MAX_NODES * sizeof(struct node *));
  graph->a_list_p = (struct node **) malloc(MAX_NODES * sizeof(struct node *));
  graph->visited =(int*) malloc(MAX_NODES * sizeof(int*));
  graph->tier1 = (int*) malloc(MAX_NODES * sizeof(int*));
  graph->a_list= (int*) malloc(MAX_NODES * sizeof(int*));
  //initializes the vectors
  for(int i = 0; i < MAX_NODES ; i++ ){
    graph->visited[i] = 0;
    graph->a_list_c[i] = NULL;
    graph->a_list_r[i] = NULL;
    graph->a_list_p[i] = NULL;
    graph->tier1[i] = 0;
    graph->a_list[i] = 0;
  }

  return graph;
}

// Create a queue for BFS algorithm
struct Queue* createQueue() {

  struct Queue* queue = malloc(sizeof(struct Graph));

  // Create vertical array of nodes (size MAX_NODES)
  queue->array = (int*) malloc(MAX_NODES * sizeof(int));

  for(int i = 0; i < MAX_NODES ; ++i )
  {
    queue->array[i] = 0;
  }

  queue->count = 0;
  queue->head = 0;
  queue->tail = 0;

  return queue;
}

/***************************************************************************
 * Function: addEdge()
 *    Input: pointer to graph struct, source node, destination node, type of
 *           relationship
 *     Task: Adds a link to tha graph (adjacency list)
 *   Output: none
 **************************************************************************/
void addEdge(struct Graph* graph, int src, int dest, int type){

  //create source, destination and auxiliary vertex
  struct node* source;
  struct node* desti;
  struct node* temp;
  struct node* temp2;

  //provider-customer relationship (src - type 1, dest - type 3)
  if(type == 1){
    source = createNode(src, 1);
    desti = createNode(dest, 3);
    temp = graph->a_list_c[src];
    temp2 = graph->a_list_p[dest];
    if(graph->a_list[src] == 0){
      (graph->num_V)++;
      graph->a_list[src] = 1;
    }
    if(graph->a_list[dest] == 0){
      (graph->num_V)++;
      graph->a_list[dest] = 1;
    }
  }
  //peer-to-peer relationship (src - type 2, dest - type 2)
  else if (type == 2){
    source = createNode(src, 2);
    desti = createNode(dest, 2);
    temp = graph->a_list_r[src];
    temp2 = graph->a_list_r[dest];
    if(graph->a_list[src] == 0){
      (graph->num_V)++;
      graph->a_list[src] = 1;
    }
  }

  //first node on the source list
  if(temp == NULL){
    //put dest node on the 1st position of src adjacencies
    if(type == 1)
      graph->a_list_c[src] = desti;
    else if(type == 2)
      graph->a_list_r[src] = desti;
    //checks if the destination list has nodes already
    if(temp2 == NULL && type != 2){
      graph->a_list_p[dest] = source;
    }
    else if(type != 2){
      source->next = graph->a_list_p[dest]->next;
      graph->a_list_p[dest]->next = source;
    }
  }
  //if it is not the first node in the source list
  else{

    if(type == 1){
      desti->next = graph->a_list_c[src]->next;
      graph->a_list_c[src]->next = desti;
    }
    else if(type == 2){
      desti->next = graph->a_list_r[src]->next;
      graph->a_list_r[src]->next = desti;
    }
    //checks if the destination list has nodes already
    if(temp2 == NULL && type != 2){
      graph->a_list_p[dest] = source;
    }
    else if(type != 2){
      source->next = graph->a_list_p[dest]->next;
      graph->a_list_p[dest]->next = source;
    }
  }
}

/***************************************************************************
 * Function: printGraph()
 *    Input: pointer to graph struct
 *     Task: Prints the adjacency list and the total number of nodes
 *   Output: none
 **************************************************************************/
void printGraph(struct Graph* graph)
{
  struct node* temp;
  for (int i = 1; i < MAX_NODES; i++){
    temp = graph->a_list_c[i];
    if(temp != NULL){
      printf("%d Clients ->", i); //print the node
      while(temp){
        printf(" %d,%d -> ", temp->name, temp->type); //print node's adjacents
        temp = temp->next;
      }
      printf("\n");
    }
    temp = graph->a_list_r[i];
    if(temp != NULL){
      printf("%d Peers ->", i); //print the node
      while(temp){
        printf(" %d,%d -> ", temp->name, temp->type); //print node's adjacents
        temp = temp->next;
      }
      printf("\n");
    }
    temp = graph->a_list_p[i];
    if(temp != NULL){
      printf("%d  Providers ->", i); //print the node
      while(temp){
        printf(" %d,%d -> ", temp->name, temp->type); //print node's adjacents
        temp = temp->next;
      }
      printf("\n");
    }
  }
  printf("Number of nodes: %d\n", (graph->num_V));
}

/***************************************************************************
 * Function: findTier1()
 *    Input: pointer to graph struct
 *     Task: Function that checks which nodes are tier1 and counts the total
 *           number of tier1 nodes
 *   Output: none
 **************************************************************************/
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
  //if a node has no providers, it is tier 1
  for (int i = 1; i < MAX_NODES; i++){
    if(count == graph->num_V)
      break;
    if(graph->a_list[i] == 0){
      continue;
    }
    temp = graph->a_list_c[i];
    //if we don't know if it's tier1, we assume it is
    if(graph->tier1[i] == -1){
      graph->tier1[i] = 1;
      (graph->n_tier1)++;
    }
    while(temp)
    {
      //if a node has customers (type 3 link), it is not tier 1
      if(/*temp->type == 3 &&*/ graph->tier1[temp->name] != 0){
        if(graph->tier1[temp->name]== 1)
          (graph->n_tier1)--;
        graph->tier1[temp->name] = 0;
      }
      temp=temp->next;
    }
    count++;
  }
}

/***************************************************************************
 * Function: push_queue()
 *    Input: pointer to queue struct, index of the node to put in vector
 *     Task: Function that simulates the push action of a FIFO stack, by
 *           putting the received element (new_id), in the last position
 *           of the vector(last index is saved in variable tail)
 *   Output: returns popped element
 **************************************************************************/
int push_queue(struct Queue* queue, int new_id )
{
    //adds new node id to the queue, in the position pointed by tail
    queue->array[queue->tail] = new_id;

    //increments number of unvisited nodes in the queue
    queue->count++;
    //tail will now point to the next empty position
    queue->tail++;
}

/***************************************************************************
 * Function: pop_queue()
 *    Input: pointer to queue struct
 *     Task: Function that simulates the pop action of a FIFO stack, by
 *           getting the first element, that wasn't previously
 *           popped (element which index is saved in variable head)
 *   Output: returns popped element
 **************************************************************************/
int pop_queue( struct Queue* queue )
{
  int item = -1;

  //gets id of the node to which head points
  item = queue->array[queue->head];

  //head will now point to the next position to pop
  queue->head++;
  //reset queue
  if(queue->head > queue->tail)
    queue->head = queue->tail = 0;

  //decrements number of unvisited nodes in the queue
  queue->count--;

  return item;
}

/***************************************************************************
 * Function: CommerciallyConn()
 *    Input: pointer to graph struct
 *     Task: Function that checks if every tier 1 node is peer of every other
 *           tier 1 node
 *   Output: none
 **************************************************************************/
int CommerciallyConn(struct Graph * graph)
{
  struct node* temp;
  int flag = 0;
  int peert1 = 0;
  int tier1 = 0;

  //gets all nodes that are tier1
  if(graph->tier1[0] != -2)
     findTier1(graph);

  //for each tier1 node, count the number of peer tier1 nodes
  for(int i = 1; i < MAX_NODES; i++){
    if(graph->tier1[i] == 1){
      temp = graph->a_list_r[i];
      while(temp){
        if(/*temp->type == 2 &&*/ graph->tier1[temp->name] == 1){
          peert1++;
        }
        temp = temp->next;
      }
      //if the number of tier1 nodes equal the number of peer tier1, it means that all tier1 nodes are peers
      //between themselves
      if(graph->n_tier1 - 1 != peert1){
        flag = -1;
        break;
      }
    }
    peert1 = 0;
  }

  if(flag == -1)
    printf("The internet is not commercially connected\n");
  else
    printf("The internet is commercially connected\n");

  return flag;
}

void check_length_type(struct Graph * graph, struct Queue * queue){
  struct node* temp;
  int *length = (int*)malloc(MAX_NODES*sizeof(int));
  int *curr_type = (int*)malloc(MAX_NODES*sizeof(int));
  int *in_queue = (int*)malloc(MAX_NODES*sizeof(int));

  for(int i = 1; i < MAX_NODES; i++){
    if(graph->a_list[i] != 0){
      length[i] = 1000;
      curr_type[i] = 0;
    }
    else
      length[i] = -2;
    in_queue[i] = 0;
  }
  FILE *f1 = fopen("length_stats.txt", "w");
  FILE *f2 = fopen("type_stats.txt", "w");

  if (f1 == NULL || f2 == NULL ){
    printf("Cannot open file \n");
    exit(0);
  }

  if(CommerciallyConn(graph) != -1){
    int n = 0;
    for(int i = 1; i < MAX_NODES; i++){
      if(n == graph->num_V)
        break;
      if(graph->a_list[i] != 0){
        //printf("no src %d\n",i);
        BGP(graph, queue, i, f1, f2, length, curr_type, in_queue);
       // printf("\n\n");
        n++;
      }
    }
  }
  free(length);
  free(curr_type);
  free(in_queue);
  fclose(f1);
  fclose(f2);
  exit(0);
}

void BGP(struct Graph * graph, struct Queue * queue, int src, FILE *f1,  FILE *f2, int *length, int* curr_type, int * in_queue){

  struct node* temp;

  push_queue(queue, src);
  curr_type[src] = -1;

  while (queue->count != 0){

   int id_pop = pop_queue(queue);
   length[src] = 0;

    if(graph->visited[id_pop] == 0){
      graph->visited[id_pop] = 1;
    }

   //printf("num_visited: %d\n", num_visited);

    temp = graph->a_list_p[id_pop];

    //put popped items adjacent nodes in queue
    //printf("No src do provider: %d\n", id_pop);
    while(temp){
     //printf("Vizinho: %d\n",temp->name);
      //printf("curr_type: %d\n", curr_type[temp->name]);
      //printf("visited: %d\n", graph->visited[temp->name]);
      //if(temp->name != src /*&& graph->visited[temp->name] == 0*/){
        //verifies commercial relationships
        if(temp->name != src && (curr_type[id_pop] == -1 || curr_type[id_pop] == 1) && (curr_type[temp->name] == 0 || curr_type[temp->name] > 1)){
         //printf("curr_type pai: %d\n", curr_type[id_pop]);

          //if(/*((length[id_pop] + 1) < length[temp->name]) */ curr_type[temp->name] == 0 || curr_type[temp->name] > 1/*) || curr_type[id_pop] < curr_type[temp->name]*/){
            length[temp->name] = length[id_pop] + 1;
            //printf("length if: %d\n",  length[temp->name]);
            curr_type[temp->name] = temp->type;
            if(in_queue[temp->name] == 0 && graph->visited[temp->name] == 0){
             // printf("visited 1 %d: %d\n", temp->name, graph->visited[temp->name]);
              push_queue(queue, temp->name);
              in_queue[temp->name] = 1;
            }
          //}
        //}
      }
      temp = temp->next;
    }

    temp = graph->a_list_r[id_pop];

    //put popped items adjacent nodes in queue
    //printf("No src do peer: %d\n", id_pop);
    while(temp){
      //printf("Vizinho: %d\n",temp->name);
      //printf("curr_type: %d\n", curr_type[temp->name]);
      if((curr_type[temp->name] == 3 || curr_type[temp->name] == 0) && temp->name != src && (curr_type[id_pop] == -1 || curr_type[id_pop] == 1)){
        //if(curr_type[id_pop] == -1 || curr_type[id_pop] == 1){
          //printf("curr_type pai: %d\n", curr_type[id_pop]);

          //if(/*(((length[id_pop] + 1) < length[temp->name]) && curr_type[temp->name] == 2) */ curr_type[temp->name] == 0 || curr_type[temp->name] == 1 /*&& curr_type[id_pop] < curr_type[temp->name]*/){
            length[temp->name] = length[id_pop] + 1;
            //printf("length if: %d\n",  length[temp->name]);
            curr_type[temp->name] = temp->type;
            if(in_queue[temp->name] == 0 && graph->visited[temp->name] == 0){
             // printf("visited 2 %d: %d\n", temp->name, graph->visited[temp->name]);
              push_queue(queue, temp->name);
              in_queue[temp->name] = 1;
            }
         // }
        //}
      }
      temp = temp->next;
    }

    temp = graph->a_list_c[id_pop];

    //put popped items adjacent nodes in queue
    ////printf("No src do client: %d\n", id_pop);
    while(temp){
      //printf("Vizinho: %d\n",temp->name);
      //printf("curr_type: %d\n", curr_type[temp->name]);
      if(curr_type[temp->name] == 0 && temp->name != src){
         //printf("curr_type pai: %d\n", curr_type[id_pop]);
        //if(/*(((length[id_pop] + 1) < length[temp->name]) && curr_type[temp->name] == 3) */curr_type[temp->name] == 0 || curr_type[temp->name] < 3){ //&& curr_type[id_pop] > curr_type[temp->name]
          length[temp->name] = length[id_pop] + 1;
          //printf("length if: %d\n",  length[temp->name]);
          curr_type[temp->name] = temp->type;
          if(in_queue[temp->name] == 0 && graph->visited[temp->name] == 0){
            //printf("visited 3 %d: %d\n", temp->name, graph->visited[temp->name]);
            push_queue(queue, temp->name);
            in_queue[temp->name] = 1;
          }
      }
      temp = temp->next;
    }
  }

  // printf(" [");
  //   for(int y = 1; y < 12; y++){
  //       printf("%d     ", length[y]);
  //   }
  //   printf("]\n");

  for(int i = 1; i < MAX_NODES ; i++ ){
    fprintf(f1, "%d ", length[i]);
    fprintf(f2, "%d ", curr_type[i]);
    if(graph->a_list[i] != 0){
      length[i] = 1000;
      graph->visited[i] = 0;
      curr_type[i] = 0;
    }
    else{
      length[i] = -2;
    }
    queue->array[i] = 0;
    in_queue[i] = 0;
  }
  fprintf(f1, "\n");
  fprintf(f2, "\n");

  queue->count = 0;
  queue->head = 0;
  queue->tail = 0;

}

/***************************************************************************
 * Function: freeAll()
 *    Input: pointer to graph struct, pointer to queue struct
 *     Task: Free memory allocated for these structures
 *   Output: none
 **************************************************************************/
void freeAll(struct Graph * graph, struct Queue * queue){

  struct node * temp, *temp1, *temp2;

  for (int i = 0; i < MAX_NODES; i++){
    while(graph->a_list_c[i] != NULL){
      temp = graph->a_list_c[i];
      graph->a_list_c[i] = graph->a_list_c[i]->next;
      free(temp);
    }
    while(graph->a_list_p[i] != NULL){
      temp1 = graph->a_list_p[i];
      graph->a_list_p[i] = graph->a_list_p[i]->next;
      free(temp1);
    }
    while(graph->a_list_r[i] != NULL){
      temp2 = graph->a_list_r[i];
      graph->a_list_r[i] = graph->a_list_r[i]->next;
      free(temp2);
    }
  }

  free(graph->visited);
  free(graph->tier1);
  free(graph->a_list_p);
  free(graph->a_list_r);
  free(graph->a_list_c);
  free(graph->a_list);
  free(graph);
  free(queue->array);
  free(queue);
}
