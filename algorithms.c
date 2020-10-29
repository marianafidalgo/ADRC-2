#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int count = 0;
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

// Create vertical array of nodes (size v)
  graph->a_list = (struct node **) malloc(MAX_NODES * sizeof(struct node *));
  graph->visited =(int*) malloc(MAX_NODES * sizeof(int*));
  graph->tier1 = (int*) malloc(MAX_NODES * sizeof(int*));

  for(int i = 0; i < MAX_NODES ; i++ )
  {
    graph->visited[i] = 0;
    graph->a_list[i] = NULL;
    graph->tier1[i] = 0;
  }

  return graph;
}

// Create a queue for BFS algorithm
struct Queue* createQueue() {

  struct Queue* queue = malloc(sizeof(struct Graph));

// Create vertical array of nodes (size v)

  queue->array = (int*) malloc(MAX_NODES * sizeof(int*));

  for(int i = 0; i < MAX_NODES ; ++i )
  {
    queue->array[i] = 0;
  }

  queue->count = 0;
  queue->head = 0;
  queue->tail = 0;

  return queue;
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
  printf("Number of nodes: %d\n", (graph->num_V));
}

struct Graph* BFS(struct Graph* graph_, struct Queue * queue){

  int flag = 0;
  int id_visited = 0;
  //fifo list
  struct Graph* graph = graph_;
  struct node* temp = graph->a_list[0];

  for(int i = 1; i < MAX_NODES; i++)
  {
    if(graph->a_list[i] != NULL){
      push_queue(queue, graph->a_list[i]->name);
      break;
    }
  }

  while (queue->count != 0){
    int id_pop = pop_queue(queue);
    graph->visited[id_pop] = 1;

    temp = graph->a_list[id_pop];

    flag = 0;
    while(temp)
    {
      for(int i = 1; i < MAX_NODES; i++)
      {
        if(temp->name == queue->array[i]){
          flag = -1;
          break;
        }

        if(queue->array[i] == 0)
          break;
      }

      if(flag == 0){
        push_queue(queue, temp->name);
      }
      flag = 0;
      temp = temp->next;
    }
  }

  return graph;
}

void connected(struct Graph* graph, struct Queue * queue) {
  //pick node from graph
  int n_nos = 0;
  int gc = 0;

  graph = BFS(graph, queue);

  for(int i = 1; i < MAX_NODES; i++){
    if(graph->visited[i]==1)
      n_nos++;
    if( n_nos == graph->num_V){
      gc = 1;
      break;
    }
    graph->visited[i]==0;
    queue->array[i] = 0;
  }
  queue->head=0;
  queue->tail=0;

  if(gc == 1)
    printf("The internet is connected\n");
  else
    printf("The internet is not connected\n");

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

void CommerciallyConn(struct Graph * graph)
{
  struct node* temp;
  int flag = 0;
  int peert1 = 0;
  int tier1 = 0;

   if(graph->tier1[0] != -2)
      findTier1(graph);

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

  if(flag == -1)
      printf("The internet is not commercially connected\n");
  else
      printf("The internet is commercially connected\n");

}

int push_queue(struct Queue* queue, int new_id )
{
    queue->array[queue->tail] = new_id;
    queue->count++;
    queue->tail++;
}

int pop_queue( struct Queue* queue )
{
  int item = -1;

  item = queue->array[queue->head];
  queue->head++;
  if(queue->head > queue->tail)
  {
    //reset queue
    queue->head = queue->tail = 0;
  }
  queue->count--;

  return item;
}

int DFS_cycles(struct Graph* graph, int v, int curr, int curr_path[], int stack[]){
  struct node* temp;
  int cycle = 0, i = 0, j = 0;

  graph->visited[v] = 1;
  curr_path[v] = 1;
  stack[curr] = v;
  curr++;

  temp = graph->a_list[v];
  while(temp){
    if(temp->type == 3 && curr_path[temp->name] == 1){
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
    if(graph->visited[temp->name] == 0 && temp->type == 3){
      cycle = DFS_cycles(graph, temp->name, curr, curr_path, stack);
      if(cycle == 1)
        return 1;
    }
    temp = temp->next;
  }

  curr_path[v] = 0;

  return cycle;
}

void checkCycles(struct Graph* graph){

  int curr_path[MAX_NODES];
  int stack[MAX_NODES];
  int curr = 0;
  int cycle = 0;
  int i;

  for(i = 0; i < MAX_NODES; i++){
    curr_path[i] = 0;
    stack[i] = 0;
  }
  if(graph->tier1[0] != -2)
    findTier1(graph);

  for(i = 1; i < MAX_NODES; i++){
    if(graph->tier1[i] == 1){
      if(graph->visited[i] == 0)
        cycle = DFS_cycles(graph, i, curr, curr_path, stack);
    }
    graph->visited[i] = 0;
  }

  if(cycle == 0)
    printf("The internet is commercially acyclic\n");
}

void freeAll(struct Graph* graph, struct Queue * queue){

  struct node * temp;

  for (int i = 0; i < MAX_NODES; i++){
    while(graph->a_list[i] != NULL){
      temp = graph->a_list[i];
      graph->a_list[i] = graph->a_list[i]->next;
      free(temp);
    }
  }

  free(graph->visited);
  free(graph->tier1);
  free(graph->a_list);
  free(graph);
  free(queue->array);
  free(queue);
}



// A recursive function that finds and prints bridges using 
// DFS traversal 
int bridges(struct Graph* graph, int u, int  visited[], int disc[], int l[], int pred[],int* time,int* bi){ 
    
    struct node* temp; 
    //int bi=0;
  
    // Mark the current node as visited 
    visited[u] = 1; 
  
    // Initialize discovery time and low value 
    *time= *time+1;
    disc[u]= *time;
    l[u]= *time; 

    temp=graph->a_list[u];

    // Go through all vertices adjacent nodes
    while(temp!=NULL)
    {   
        
        int v = temp->name;  // v is current adjacent of u 

        // If v is not visited yet, then recur for it 
        if (visited[v]!=1) // && temp->type!=1) 
        { 
            //printf("%d was not visited and is not type 1\n",v);
            pred[v] = u; 
            bridges(graph, v, visited, disc, l, pred, time,bi);            
  
            // Check if the subtree rooted with v has a  
            // connection to one of the ancestors of u 
            l[u]  = min(l[u], l[v]); //i.e., if v can reach a previous node then so can u 
  
            // If the lowest vertex reachable from subtree  
            // under v is  below u in DFS tree, then u-v  
            // is a bridge 

            //se o nó mais antigo a que o v consegue aceder
            //for maior que o disc do u,
            //isso quer dizer que o v fica isolado caso se corte u-v
            //ou seja, temos uma ponte
            if (l[v] > disc[u]){ 
                printf("There is a bridge %d-%d\n", u,v);
                *bi=1;
                return 1; // so it stops once it finds 1 bridge
            }
        } 
        else if (v != pred[u])  // If v is not the predecessor of u
            l[u]  = min(l[u], disc[v]);  //it means u can reach a previous node 
        if(*bi==1){
          break;
        } 
        temp=temp->next;
    } 
    return 0;
}
  
// DFS based function to find all bridges. It uses recursive  
// function bridges()
void find_bridges(struct Graph* graph){ 

    int visited[MAX_NODES]; //stores if a node has already been visited or not
    int disc[MAX_NODES]; //stores the discovery time of each node
    int l[MAX_NODES];  //stores the latest time of a node it can reach
    int pred[MAX_NODES]; //stores the predecessor of each node
    int i=0, time=0 ,bi=0;

    // Initialize predecessor and visited arrays 
    for (i = 0; i < MAX_NODES; i++){ 
        pred[i] = 0; 
        visited[i] = 0; 
        disc[i]=0;
        l[i]=0;
    } 

    // Call the recursive function to find Bridges 
    // in DFS tree rooted in vertex 'i' 
    for(i = 1; i < MAX_NODES; i++){
        if(graph->visited[i] == 0)
            bridges(graph, i, visited, disc, l, pred,&time, &bi);
        //graph->visited[i] = 0;
    }
    if(bi!=1)
      printf("The interned is link-biconnected!\n");

}