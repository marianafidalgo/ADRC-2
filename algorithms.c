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

//Create a SCC structure
struct StrongCC * createSCC(){

  struct StrongCC* struct_scc = malloc(sizeof(struct StrongCC));

  // Create vertical array of nodes (size MAX_NODES)
  struct_scc->array = (int*) malloc(MAX_NODES * sizeof(int));

  for(int i = 0; i < MAX_NODES ; ++i )
  {
    struct_scc->array[i] = 0;
  }
  struct_scc->id = 0;
  struct_scc->next = NULL;

  return struct_scc;
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

 /***************************************************************************
 * Function: BFS()
 *    Input: pointer to graph struct, pointer to queue struct
 *     Task: Function that checks if a graph is connected, by implementing
 *           the BFS algorithm. It runs a BFS only starting in one single
 *           node, since if it can't reach all it won't be connected.
 *   Output: none
 **************************************************************************/
void BFS(struct Graph* graph_, struct Queue * queue){

  int flag = 0;
  int id_visited = 0;
  struct Graph* graph = graph_;
  struct node* temp = graph->a_list[0];

  //first node in the adjacency list gets pushed
  for(int i = 1; i < MAX_NODES; i++)
  {
    if(graph->a_list[i] != NULL){
      push_queue(queue, graph->a_list[i]->name);
      break;
    }
  }

  while (queue->count != 0){
    //pops first item in queue, marks as visiteda and see it's adjacent nodes
    int id_pop = pop_queue(queue);
    graph->visited[id_pop] = 1;

    temp = graph->a_list[id_pop];

    //put popped items adjacent nodes in queue
    while(temp)
    {
      //if it's not visited we put the adjacent node in queue
      if(graph->visited[temp->name] == 0){
        graph->visited[temp->name] = 1;
        push_queue(queue, temp->name);
      }

      temp = temp->next;
    }
  }
}

/***************************************************************************
 * Function: connected()
 *    Input: pointer to graph struct, pointer to queue struct
 *     Task: Function that goes through the vector of visited nodes, changed
 *           by the BFS algorithm function and checks if all nodes are
 *           visited. If yes, it prints a connected string, if not it prints
 *           a not connected string.
 *   Output: none
 **************************************************************************/
void connected(struct Graph* graph, struct Queue * queue) {

  int n_nos = 0;
  int gc = 0;

  for(int i = 1; i < MAX_NODES; i++){
    graph->visited[i] = 0;
  }
  //run BFS algorithm to get visited nodes
  BFS(graph, queue);

  //if all nodes are marked visited by one run of BFS, the graph is connected
  for(int i = 1; i < MAX_NODES; i++){
    if(graph->visited[i] == 1)
      n_nos++;
    if( n_nos == graph->num_V){
      gc = 1;
      break;
    }
    queue->array[i] = 0;
  }
  queue->head = 0;
  queue->tail = 0;

  if(gc == 1)
    printf("The internet is connected\n");
  else
    printf("The internet is not connected\n");

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
    if(graph->a_list[i] == NULL){
      continue;
    }
    temp = graph->a_list[i];
    //if we don't know if it's tier1, we assume it is
    if(graph->tier1[i] == -1){
      graph->tier1[i] = 1;
      (graph->n_tier1)++;
    }
    while(temp)
    {
      //if a node has customers (type 3 link), it is not tier 1
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
void DFSbridges(struct Graph* graph, int u, int disc[], int l[], int pred[], int* time, int* bi){

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

        if (graph->visited[v] != 1){
            pred[v] = u;
            DFSbridges(graph, v, disc, l, pred, time,bi);

            // Check if the subtree rooted in v has a
            // link to one of the predecessors of u
            l[u] = min(l[u], l[v]); //i.e., if v can reach a previous node then so can u

            // If the lowest vertex that v can reach from its subtree is under u,
            //then u-v is going to be a bridge
            if (l[v] > disc[u]){
                if(*bi==1){
                  return ; // so it stops once it finds 1 bridge
                }
                else{
                  printf("There is a bridge between nodes %d-%d\n", u, v);
                  *bi = 1;
                }
            }
        }
        else if (v != pred[u])  // If v is not the predecessor of u
            l[u] = min(l[u], disc[v]);  //it means u can reach a previous node
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

    int disc[MAX_NODES]; //stores the discovery time of each node
    int l[MAX_NODES];  //stores the latest time of a node it can reach
    int pred[MAX_NODES]; //stores the predecessor of each node
    int i = 0, time = 0 , bi = 0;

    // Initialize predecessor and visited arrays
    for (i = 0; i < MAX_NODES; i++){
      graph->visited[i] = 0;
      pred[i] = 0;
      disc[i] = 0;
      l[i] = 0;
    }
    // Call the recursive function to find bridges
    // using DFS in a tree with root 'i'
    for(i = 1; i < MAX_NODES; i++){
        if(graph->visited[i] == 0 && graph->a_list[i] != NULL)
            DFSbridges(graph, i, disc, l, pred, &time, &bi);
    }
    if(bi!= 1)
      printf("The interned is link-biconnected\n");
}

/***************************************************************************
 * Function: DFS_cycles()
 *    Input: pointer to graph struct, node being analysed, incremental int,
 *           vector that stores the current path, vector that stores the
 *           names of the visited nodes in order of visitation
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
        printf("%d ", stack[j]);
        if(stack[j] == v){
          break;
        }
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
 *     Task: Calls the DFS function for the first node and for all the nodes 
 *           after, that were not visited in a previous path
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
    graph->visited[i] = 0;
  }

  //checks if the function that finds tier 1 was already run in another algorithm
  if(graph->tier1[0] != -2)
    findTier1(graph);

  for(i = 1; i < MAX_NODES; i++){
    if(graph->visited[i] == 0 && graph->a_list[i] != NULL){
      cycle = DFS_cycles(graph, i, curr, curr_path, stack);
      if(cycle == 1)
        break;
    }
  }

  //cycle = 0 means there are no cycles
  if(cycle == 0)
    printf("The internet is commercially acyclic\n");
}

/***************************************************************************
 * Function: DFS_normal()
 *    Input: pointer to graph struct, node being analysed, incremental int,
 *           vector that stores the current path, vector that stores the
 *           names of the visited nodes in order of visitation, vector
 *           that store the order of termination of the nodes
 *     Task: Recursive function that runs a DFS that checks all the clients 
 *           of the node received, marks them as visited and stores their 
 *           termination time
 *   Output: returns the index of the last occupied position in vector last
 **************************************************************************/
int DFS_normal(struct Graph * graph, int v, int curr, int curr_path[], int stack[], int *last){
  struct node* temp;
  int i = 0, j = 0, flag = 0;

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
      //save last node before cycle
      last[curr_last] = v;
      curr_last++;
      for(i = 0; i < MAX_NODES; i++){
        if(stack[i] == temp->name)
          break;
      }
    }
    //if the node is a client and was not visited, run a DFS on it
    if(graph->visited[temp->name] == 0 && temp->type == 3){
      DFS_normal(graph, temp->name, curr, curr_path, stack, last);
    }
    temp = temp->next;
  }
  //when the node does not have more clients takes it from the path
  curr_path[v] = 0;
  for(int i = 0; i < MAX_NODES; i++)
  {
    //check if item is already in the last array
    if(v == last[i]){
      flag = -1;
      break;
    }
    //checks if there are more elements in last array
    if(last[i] == 0)
      break;
  }
  if(flag == 0){
    last[curr_last] = v;
    curr_last++;
  }
  flag = 0;

  return curr_last;
}

/***************************************************************************
 * Function: DFS_inversed()
 *    Input: pointer to graph struct, node being analysed, vector that stores 
 *           the current path, 
 *     Task: Recursive function that checks all the clients of the node
 *           received (in order of last termination time to first) and marks 
 *           them as visited. 
 *   Output: flag that is 0 if there are no cycles and 1 if there is at
 *           least one cycle
 **************************************************************************/
void DFS_inversed(struct Graph * graph, int v, int * curr_path){
  struct node* temp;
  int i = 0, j = 0, flag = 0;

  //marks the node as visited
  graph->visited[v] = 1;
  //puts the node in the current path
  curr_path[v] = 1;

  //visits all the node's adjacencies
  temp = graph->a_list[v];
  while(temp){
    //use relationship type 1 to simulate the inversion of the graph
    if(temp->type == 1){
      //if the node is a client and was not visited, run a DFS on it
      if(graph->visited[temp->name] == 0){
        DFS_inversed(graph, temp->name, curr_path);
      }
    }
    temp = temp->next;
  }
}

/***************************************************************************
 * Function: NoTier1_CommerciallyConn()
 *    Input: pointer to graph struct
 *     Task: Function that checks if a graph without tier 1s is commercially
 *           connected 
 *   Output: none
 **************************************************************************/
void NoTier1_CommerciallyConn(struct Graph * graph){

  int curr_path[MAX_NODES]; //stores nodes in the current path
  int stack[MAX_NODES]; //stores names of nodes in order of visitation
  int last[MAX_NODES]; //stores last visited for inverse DFS
  int curr = 0;
  int i = 0;
  int scc_group = 1;
  int found_g = 0;
  int same_id = 0;
  //stores the scc's that already have a peer-to-peer relationship
  int ** peer_matrix = calloc(MAX_NODES,sizeof(int *)); 

  struct StrongCC * scc_list  = createSCC();

  struct Graph * scc_graph = createGraph();
  struct node * temp;

  for(i = 0; i < MAX_NODES; i++){
    graph->visited[i] = 0;
    curr_path[i] = 0;
    stack[i] = 0;
    last[i] = 0;
    peer_matrix[i] = calloc(MAX_NODES,sizeof(int));
  }

  //run DFS in every unvisited not
  for(i = 1; i < MAX_NODES; i++){
    if(graph->visited[i] == 0 && graph->a_list[i] != NULL){
      DFS_normal(graph, i, curr, curr_path, stack, last);
    }
    graph->visited[i] = 0;
    curr_path[i] = 0;
    stack[i] = 0;
  }

  //run "inverted" DFS in every node
  for(i = curr_last-1; i >= 0; i--){
    if(graph->visited[last[i]] == 0 && graph->a_list[last[i]] != NULL){
      DFS_inversed(graph, last[i], curr_path);
      scc_i = 0;
      //stores all the visited nodes in this path in a list as a strongly connected component
      //first node of the list
      if(scc_list->array[0] == 0){
        for(i = 1; i < MAX_NODES; i++){
          if(curr_path[i] == 1){
            scc_list->array[scc_i] = i;
            scc_i++;
            curr_path[i] = 0;
          }
        }
      }
      //not first node of the list
      else{
        struct StrongCC * new = createSCC();
        new->next=scc_list;
        scc_list = new;
        for(i = 1; i < MAX_NODES; i++){
          if(curr_path[i] == 1){
            scc_list->array[scc_i] = i;
            scc_i++;
            curr_path[i] = 0;
          }
        }
      }
      scc_list->id = scc_group; //stores the name of the scc node
      scc_group++;
    }
  }

  struct StrongCC * temp1 = scc_list;
  struct StrongCC * temp2 = scc_list;

  //create adjacency list of the strongly connected components
  //goes through scc list
  while(temp1){
    //goes through nodes in a scc
    for(i = 0; i < MAX_NODES; i++){
      if(temp1->array[i] == 0)
        break;
      temp = graph->a_list[(temp1->array[i])];
      //goes through adjacency list of the node in question
      while(temp){
        if(temp->type != 1){
          //goes through another copy of scc list to see if it finds the adjacency in a different group
          while(temp2){
            for(i = 0; i < MAX_NODES; i++){
              //checks if there are still nodes of that
              if(temp2->array[i] == 0)
                break;
              if(temp1->id == temp2->id){
                same_id = 1;
                break;
              }
              //finds adjacency in different group and puts flag to 1 to add edge
              if(temp2->array[i] == temp->name){
                found_g = 1;
                break;
              }
            }
            if(same_id == 1){
              same_id = 0;
              break;
            }
            //add edge
            if(found_g == 1){
              if(temp->type == 3)
                addEdge(scc_graph, temp1->id, temp2->id, 1);
              if(temp->type == 2){
                addEdge(scc_graph, temp1->id, temp2->id, 2);
                addEdge(scc_graph, temp2->id, temp1->id, 2);
                peer_matrix[temp1->id][temp2->id] = 1;
                peer_matrix[temp2->id][temp1->id] = 1;
              }
              found_g = 0;
              break;
            }
            temp2=temp2->next;
          }
          temp2 = scc_list;
        }
        temp = temp->next;
      }
    }
    temp1 = temp1->next;
  }

  CommerciallyConn(scc_graph);
}

/***************************************************************************
 * Function: CommerciallyConn()
 *    Input: pointer to graph struct
 *     Task: Function that checks if every tier 1 node is peer of every other
 *           tier 1 node
 *   Output: none
 **************************************************************************/
void CommerciallyConn(struct Graph * graph)
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
      temp = graph->a_list[i];
      while(temp){
        if(temp->type == 2 && graph->tier1[temp->name] == 1){
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