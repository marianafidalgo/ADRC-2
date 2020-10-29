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

  // Create vertical array of nodes (size MAX_NODES)
  graph->a_list = (struct node **) malloc(MAX_NODES * sizeof(struct node *));
  graph->visited =(int*) malloc(MAX_NODES * sizeof(int*));
  graph->tier1 = (int*) malloc(MAX_NODES * sizeof(int*));

  //initializes the vectors
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

  // Create vertical array of nodes (size MAX_NODES)
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

    //provider-customer relationship (src - type 1, dest - type 3)
    if(type == 1){
      source = createNode(src, 1);
      desti = createNode(dest, 3);
    }
    //peer-to-peer relationship (src - type 2, dest - type 2)
    else{
      source = createNode(src, 2);
      desti = createNode(dest, 2);
    }

    temp = graph->a_list[src];
    //first node on the source list
    if(temp == NULL){
      //put dest node on the 1st position of src adjacencies
      graph->a_list[src] = desti;
      (graph->num_V)++; //increments number of nodes
      //checks if the destination list has nodes already
      if(graph->a_list[dest] == NULL && type != 2){
        graph->a_list[dest] = source;
        (graph->num_V)++;
      }
      else if(type != 2){
        source->next = graph->a_list[dest]->next;
        graph->a_list[dest]->next = source;
      }
    }
    //if it is not the first node in the source list
    else{
      desti->next = graph->a_list[src]->next;
      graph->a_list[src]->next = desti;
      //checks if the destination list has nodes already
      if(graph->a_list[dest] == NULL && type != 2){
          graph->a_list[dest] = source;
          (graph->num_V)++;
      }
      else if(type != 2){
        source->next = graph->a_list[dest]->next;
        graph->a_list[dest]->next = source;
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
    temp = graph->a_list[i];
    if(temp != NULL){
      printf("%d ->", i); //print the node
      while(temp){
        printf(" %d,%d -> ", temp->name, temp->type); //print node's adjacents
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

/***************************************************************************
 * Function: DFS_cycles()
 *    Input: pointer to graph struct, node being analysed, incremental int, 
 *           vector that stores the current path, vector that stores the 
 *           names of the visited nodes in order od visitation   
 *     Task: Recursive function that checks all the clients of the node 
 *           received and marks them as visited. When it finds a node that
 *           was already visited in that path declares there is a cycle
 *   Output: flag that is 0 if there are no cycles and 1 if there is at 
 *           least one cycle
 **************************************************************************/
int DFS_cycles(struct Graph * graph, int v, int curr, int curr_path[], int stack[]){
  struct node* temp;
  int cycle = 0, i = 0, j = 0;

  //marks the node as visited
  graph->visited[v] = 1;
  //puts the node in the current path
  curr_path[v] = 1;
  //saves the node name in the stack
  stack[curr] = v;
  curr++;

  //visits all the node's adjacencies
  temp = graph->a_list[v];
  while(temp){
    //if the node is a client and is in the current path then there is a cycle
    if(temp->type == 3 && curr_path[temp->name] == 1){
      printf("The internet is not commercially acyclic\nCycle: ");
      //find the node that was visited again in the stack
      for(i = 0; i < MAX_NODES; i++){
        if(stack[i] == temp->name)
          break;
      }
      //print the cycle
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
    //if the node is a client and was not visited, run a DFS on it
    if(graph->visited[temp->name] == 0 && temp->type == 3){
      cycle = DFS_cycles(graph, temp->name, curr, curr_path, stack);
      if(cycle == 1)
        return 1;
    }
    temp = temp->next;
  }

  //when the node does not have more clients takes it from the path
  curr_path[v] = 0;

  return cycle;
}

/***************************************************************************
 * Function: checkCycles()
 *    Input: pointer to graph struct
 *     Task: Checks if there are any tier 1 nodes. If there are calls the
 *           DFS_cycles function for each of them. If not calls that same 
 *           function for the first node and for all the nodes after, that
 *           were not visited in a previous path
 *   Output: none
 **************************************************************************/
void checkCycles(struct Graph * graph){

  int curr_path[MAX_NODES]; //stores nodes in the current path
  int stack[MAX_NODES]; //stores names of nodes in order of visitation
  int curr = 0;
  int cycle = 0;
  int i;

  for(i = 0; i < MAX_NODES; i++){
    curr_path[i] = 0;
    stack[i] = 0;
  }

  //checks if the function that finds tier 1 was already run in another algorithm
  if(graph->tier1[0] != -2)
    findTier1(graph);

  //if there are tier 1 nodes runs the DFS from those nodes
  if(graph->n_tier1 != 0){
    for(i = 1; i < MAX_NODES; i++){
      if(graph->tier1[i] == 1){
        if(graph->visited[i] == 0)
          cycle = DFS_cycles(graph, i, curr, curr_path, stack);
          if(cycle == 1)
            break;
      }
    }
  }
  //if not runs the DFS from the first node and all unvisited nodes after that
  else{
    for(i = 1; i < MAX_NODES; i++){ 
      if(graph->visited[i] == 0)
        cycle = DFS_cycles(graph, i, curr, curr_path, stack);
        if(cycle == 1)
          break;
    }
    graph->visited[i] = 0;
  }

  //cycle = 0 means there are no cycles
  if(cycle == 0)
    printf("The internet is commercially acyclic\n");
}

/***************************************************************************
 * Function: DFSbridges()
 *    Input: pointer to graph struct, node being analysed, vector that stores
 *           the discovery time of each node, vector that stores the latest 
 *           time that the node in each index can reach, vector that stores 
 *           predecessor of each node, integer of the current time and the
 *           integer that is a flag to stop the search for bridges onde it
 *           finds one.  
 *     Task: Recursive function that finds one bridge in a given graph,
 *           when it's found, the bridge is printed and then returns 1 
 *   Output: none
 **************************************************************************/
void DFSbridges(struct Graph* graph, int u, int disc[], int l[], int pred[],int* time,int* bi){ 
    
    struct node* temp; 
  
    // Mark the current node as visited 
    graph->visited[u] = 1; 
  
    // Initialize discovery time and low value 
    *time = *time+1;
    disc[u] = *time;
    l[u] = *time; 

    temp = graph->a_list[u];

    // Go through all vertices adjacent nodes
    while(temp != NULL){   
        
        int v = temp->name;  // v is current adjacent of u 

        // If v is not visited yet, then recur for it 
        if (graph->visited[v]!=1){

            pred[v] = u; 
            DFSbridges(graph, v, disc, l, pred, time,bi);            
  
            // Check if the subtree rooted with v has a  
            // connection to one of the predecessor of u 
            l[u] = min(l[u], l[v]); //i.e., if v can reach a previous node then so can u 
  
            // If the lowest vertex reachable from subtree  
            // under v is  below u in DFS tree, then u-v  
            // is a bridge 

            //se o nó mais antigo a que o v consegue aceder
            //for maior que o disc do u,
            //isso quer dizer que o v fica isolado caso se corte u-v
            //ou seja, temos uma ponte
            if (l[v] > disc[u]){ 
                if(*bi==1)
                  return ; // so it stops once it finds 1 bridge
                else{
                  printf("There is a bridge %d-%d\n", u,v);
                  *bi = 1;
                }
            }
        } 
        else if (v != pred[u])  // If v is not the predecessor of u
            l[u]  = min(l[u], disc[v]);  //it means u can reach a previous node 
        if(*bi == 1)
          break;
        
        temp = temp->next;
    } 
    return ;
}
  
/***************************************************************************
 * Function: find_bridges()
 *    Input: pointer to graph struct
 *     Task: Clears the vectors necessary for the recursive function DFSbridges() 
 *           that finds bridges, once it finds 1, the bridge is printed. If no
 *           bridge is found then the internet is link-biconnected.
 *   Output: none
 **************************************************************************/
void find_bridges(struct Graph * graph){ 

    //int visited[MAX_NODES]; //stores if a node has already been visited or not
    int disc[MAX_NODES]; //stores the discovery time of each node
    int l[MAX_NODES];  //stores the latest time of a node it can reach
    int pred[MAX_NODES]; //stores the predecessor of each node
    int i = 0, time = 0 , bi = 0;

    // Initialize predecessor and visited arrays 
    for (i = 0; i < MAX_NODES; i++){ 
        pred[i] = 0; 
        graph->visited[i] = 0; 
        disc[i]=0;
        l[i]=0;
    } 

    // Call the recursive function to find bridges 
    // using DFS in a tree with root 'i' 
    for(i = 1; i < MAX_NODES; i++){
        if(graph->visited[i] == 0)
            DFSbridges(graph, i, disc, l, pred,&time, &bi);
        graph->visited[i] = 0; //to clear the vector of visited nodes
    }
    if(bi!= 1)
      printf("The interned is link-biconnected!\n");
}

/***************************************************************************
 * Function: freeAll()
 *    Input: pointer to graph struct, pointer to queue struct
 *     Task: Free memory allocated for these structures
 *   Output: none
 **************************************************************************/
void freeAll(struct Graph * graph, struct Queue * queue){

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