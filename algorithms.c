
#include "functions.h"

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

  graph->bgp_clients = (struct node **)malloc(MAX_NODES * sizeof(struct node *));

  graph->a_list= (int*)calloc(MAX_NODES, sizeof(int*));

  //initializes the vectors
  for(int i = 0; i < MAX_NODES ; i++ ){
    graph->a_list_c[i] = NULL;
    graph->a_list_r[i] = NULL;
    graph->a_list_p[i] = NULL;
    graph->bgp_clients[i] = NULL;
  }

  return graph;
}

// Create a FIFO
struct Queue* createQueue() {

  struct Queue* queue = malloc(sizeof(struct Graph));

  // Create vertical array of nodes (size MAX_NODES)
  queue->array = (int*) calloc(MAX_NODES, sizeof(int));

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
    //first time seeing a node increments number of nodes
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
    desti = createNode(dest, 2);
    temp = graph->a_list_r[src];
    temp2 = graph->a_list_r[dest];
    //first time seeing a node increments number of nodes
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
    //prints node's i clients
    temp = graph->a_list_c[i];
    if(temp != NULL){
      printf("%d Clients ->", i); //print the node
      while(temp){
        printf(" %d,%d -> ", temp->name, temp->type); //print node's adjacents
        temp = temp->next;
      }
      printf("\n");
    }
    //prints node's i peers
    temp = graph->a_list_r[i];
    if(temp != NULL){
      printf("%d Peers ->", i); //print the node
      while(temp){
        printf(" %d,%d -> ", temp->name, temp->type); //print node's adjacents
        temp = temp->next;
      }
      printf("\n");
    }
    //prints node's i providers
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

/******************************************************************************
 * Function: check_length_type()
 *    Input: graph struct, queue struct, input source node, input destination
 *           node, and the menu selection (either statistics (5), specific
 *           length (2) or specific type (1)
 *     Task: If the question is either (1) or (2), it calls the BGP algorithm
 *           for the destination given and prints the asked type or asked length
 *           respectively. If the question is (5), it calls the BGP for all
 *           nodes, and prints all the statistics.
 *   Output: none
 *****************************************************************************/
void check_length_type(struct Graph * graph, struct Queue * queue, int src, int dest, int question){
  struct node* temp;
  //array that stores length of each node to the destination
  int *length = (int*)malloc(MAX_NODES*sizeof(int));
  //array that stores current path type of each node to the destination
  int *curr_type = (int*)malloc(MAX_NODES*sizeof(int));
  //array that stores the number of paths with a specific length
  int *final_length = (int*)malloc(16*sizeof(int));
   //array that stores the number of paths of a specific type
  int *final_type = (int*)malloc(4*sizeof(int));

  int ans = 0, ans_ = 0;

  //initialization of the length and type vectors
  for(int i = 0; i < MAX_NODES; i++){
    if(graph->a_list[i] != 0){
      length[i] = MAX_NODES;
      curr_type[i] = 0;
    }
    else{
      length[i] = -2;
      curr_type[i] = -2;
    }
    if(i < 11){
      final_length[i] = 0;
      if(i < 4)
        final_type[i] = 0;
    }
  }

  //if the menu selection was 5, call BGP function to all nodes
  if(question == 5){
    int n = 0;
    for(int i = 1; i < MAX_NODES; i++){
      if(n == graph->num_V)
        break;
      if(graph->a_list[i] != 0){
        BGP(graph, queue, i, length, curr_type, final_length, final_type, src, dest, question);
        n++;
      }
    }
  }
  //if the menu selection was 1 or 2, call BGP function to the given source and destination node
  else{
    ans = BGP(graph, queue, dest, length, curr_type, final_length, final_type, src, dest, question);
  }
  //print the asked type
  if(question == 1){
    if(ans == 0)
      printf("There is no path from %d to %d\n",src, dest);
    else if(ans == 1)
      printf("The path from %d to %d is a customer path\n",src, dest);
    else if(ans == 2)
      printf("The path from %d to %d is a peer path\n",src, dest);
    else if(ans == 3)
      printf("The path from %d to %d is a provider path\n",src, dest);
  }
  //print the asked length
  else if(question == 2){
    if (ans == MAX_NODES)
      printf("There is no commercial path from %d to %d\n", src, dest);
    else
      printf("The length of the path from %d to %d is %d\n", src, dest, ans);


  }
  //print all statistics
  else if(question == 5){
    printf("Types statistics:\n"
            "The number of invalid paths is %d\n"
            "The number of customer paths is %d\n"
            "The number of peer paths is %d\n"
            "The number of provider paths is %d\n\n\n",
            final_type[0], final_type[1], final_type[2], final_type[3]);

    printf("Lengths statistics :\n"
            "The number of paths with length 0 is %d\n"
            "The number of paths with length 1 is %d\n"
            "The number of paths with length 2 is %d\n"
            "The number of paths with length 3 is %d\n"
            "The number of paths with length 4 is %d\n"
            "The number of paths with length 5 is %d\n"
            "The number of paths with length 6 is %d\n"
            "The number of paths with length 7 is %d\n"
            "The number of paths with length 8 is %d\n"
            "The number of paths with length 9 is %d\n"
            "The number of paths with length 10 is %d\n"
            "The number of paths with length 11 is %d\n"
            "The number of paths with length 12 is %d\n"
            "The number of paths with length 13 is %d\n"
            "The number of paths with length 14 is %d\n"
            "The number of paths with length 15+ is %d\n",
            final_length[0], final_length[1], final_length[2], final_length[3], final_length[4], final_length[5],
            final_length[6], final_length[7], final_length[8], final_length[9], final_length[10], final_length[11],
            final_length[12], final_length[13], final_length[14], final_length[15]);
  }

  //free arrays
  free(length);
  free(curr_type);
  free(final_length);
  free(final_type);

}

/***************************************************************************
 * Function: BGP()
 *    Input: graph struct, queue struct, destination node, length array,
 *           type array, final length array (for stats), final type array
 *           (for stats), input source node, input destination node, input
 *           menu selection
 *     Task: Function that gets a destination node and finds the types and
 *           lengths of the BGP paths from every other node to that node
 *   Output: returns either the type or the length of the path from the
 *           source node to the destination node introduced by the user
 **************************************************************************/
int BGP(struct Graph * graph, struct Queue * queue, int dest, int * length, int * curr_type, int * final_length, int* final_type, int source, int destination, int question){

  struct node* temp, *node ,*bgp_temp, *bgp_temp_free;
  int asked_len = 0;
  int asked_type = 0;
  int a = 0;
  int id_pop = 0;

  //put destination node in queue so it's the first one to be visited
  push_queue(queue, dest);
  //set the type of the destination node to -1
  curr_type[dest] = -1;
  //set the length of the destination node to 0
  length[dest] = 0;

  while (queue->count != 0){
    //sees next node in queue
    id_pop = pop_queue(queue);

    //loops through the providers of id_pop
    temp = graph->a_list_p[id_pop];
    while(temp){
      //checks if the commercial rules are met and if the best path according to BGP is found
      if(temp->name != dest && (curr_type[id_pop] == -1 || curr_type[id_pop] == 1) && (curr_type[temp->name] == 0 || curr_type[temp->name] > 1)){
        length[temp->name] = length[id_pop] + 1;
        curr_type[temp->name] = temp->type;
        push_queue(queue, temp->name);
      }
      temp = temp->next;
    }

    //loops through the peers of id_pop
    temp = graph->a_list_r[id_pop];
    while(temp){
      //checks if the commercial rules are met and if the best path according to BGP is found
      if(curr_type[temp->name] == 0 && temp->name != dest && (curr_type[id_pop] == -1 || curr_type[id_pop] == 1)){
        length[temp->name] = length[id_pop] + 1;
        curr_type[temp->name] = temp->type;
        push_queue(queue, temp->name);
      }
      temp = temp->next;
    }
  }

  //loops through the nodes that are in the queue
  for(int i = 0; i < MAX_NODES; i++){
    if(queue->array[i] == 0)
        break;
    else{
      //sees their immediate customers
      temp = graph->a_list_c[queue->array[i]];
      while(temp){
        //checks if the node has been visited
        if(temp->name != dest && length[temp->name] == MAX_NODES){
          //if not, creates a node and stores it in bgp_clients array
          node = createNode(temp->name, 3);
          a = length[queue->array[i]] + 1;
          if(graph->bgp_clients[a] == NULL)
             graph->bgp_clients[a] = node;
          else{
            node->next = (graph->bgp_clients[a])->next;
            (graph->bgp_clients[a])->next = node;
          }
        }
        temp = temp->next;
      }
    }
  }

  //loops through bgp_clients array
  for (int i = 1; i < MAX_NODES; i++){
    //loops through array list
    bgp_temp = graph->bgp_clients[i];
    while(bgp_temp){
      //checks if the node has been visited
      if(length[bgp_temp->name] == MAX_NODES){
        //if not, changes its length to the length of bgp_clients
        length[bgp_temp->name] = i;
        //type is always 3 because we are only seeing customers
        curr_type[bgp_temp->name] = 3;
        //loops through the customers of the node
        temp = graph->a_list_c[bgp_temp->name];
        while(temp){
          //checks if the node has been visited
          if(temp->name != dest && length[temp->name] == MAX_NODES){
            //if not, adds it to bgp_clients
            node = createNode(temp->name, 3);
            a = length[bgp_temp->name] + 1;
            if(graph->bgp_clients[a] == NULL)
              graph->bgp_clients[a] = node;
            else{
              node->next = (graph->bgp_clients[a])->next;
              (graph->bgp_clients[a])->next = node;
            }
          }
          temp = temp->next;
        }
      }
      //frees nodes that have been visited and have their length already in the length array
      bgp_temp_free = graph->bgp_clients[i];
      graph->bgp_clients[i] = bgp_temp_free->next;
      free(bgp_temp_free);
      bgp_temp = graph->bgp_clients[i];
    }
  }

  for(int i = 1; i < MAX_NODES ; i++ ){
    //statistics
    if(question == 5){
      //counts the number of times each type appears (0 are invalid paths)
      if(curr_type[i] >= 0){
        a = curr_type[i];
        final_type[a] = final_type[a] + 1;
      }
      //counts the number of times each length appears (10+ is one category)
      if(length[i] > 14 && length[i] != MAX_NODES)
        final_length[15] = final_length[15] + 1;
      else if(length[i] < 15 && length[i] != MAX_NODES && length[i] != -2){
        a = length[i];
        final_length[a] = final_length[a] + 1;
      }
    }
    //checks if this is the source-destination pair introduced by the user and if it is stores the length and type
    if(dest == destination && i == source){
      asked_len = length[i];
      asked_type = curr_type[i];
    }
    //initialise variables
    if(graph->a_list[i] != 0){
      length[i] = MAX_NODES;
      curr_type[i] = 0;
    }
    else{
      length[i] = -2;
      curr_type[i] = -2;
    }
    queue->array[i] = 0;
  }

  //initialise variables
  queue->count = 0;
  queue->head = 0;
  queue->tail = 0;

  //checks if the user asked for the type or the length and returns the one solicited
  if(question == 1)
    return asked_type;
  else if(question == 2)
    return asked_len;
}

/******************************************************************************
 * Function: check_length_type()
 *    Input: graph struct, queue struct, input source node, input destination
 *           node, and the menu selection (either statistics (6), specific
 *           length (3)
 *     Task: If the question is (3), it calls the BGP_shortest algorithm
 *           for the destination given and prints the asked length. If the question
 *           is (6), it calls the BGP_shortest for all nodes, and prints all
 *           the statistics.
 *   Output: none
 *****************************************************************************/
void check_length_shortest (struct Graph * graph, struct Queue * queue, int src, int dest, int question){
  struct node* temp;
  //array that stores the length of each node to the destination
  int *length = (int*)malloc(MAX_NODES*sizeof(int));
  //array that stores the length of each node from a customer-provider link to the destination
  int *length_p = (int*)malloc(MAX_NODES* sizeof(int));
  //array that stores the length of each node from a peer-to-peer link to the destination
  int *length_r = (int*)malloc(MAX_NODES* sizeof(int));
  //array that stores the length of each node from a provider-customer link to the destination
  int *length_c = (int*)malloc(MAX_NODES* sizeof(int));
  //array that stores current path type of each node to the destination
  int *curr_type = (int*)malloc(MAX_NODES*sizeof(int));

  //array that stores the number of paths with a specific length
  int *final_length = (int*)calloc(16,sizeof(int));
  //array that stores the number of paths of a specific type
  int *final_type = (int*)calloc(4,sizeof(int));

  int ans = 0, ans_ = 0;

  //initialization of all length vectors and current type vector
  for(int i = 0; i < MAX_NODES; i++){
    if(graph->a_list[i] != 0){
      length[i] = MAX_NODES;
      length_p[i] = MAX_NODES;
      length_r[i] = MAX_NODES;
      length_c[i] = MAX_NODES;
      curr_type[i] = 0;
    }
    else{
      length[i] = -2;
      length_p[i] = -2;
      length_r[i] = -2;
      length_c[i] = -2;
      curr_type[i] = -2;
    }
  }
  //if the menu selection was 6, call BGP_shortest function to all nodes
  if(question == 6){
    int n = 0;
    for(int i = 1; i < MAX_NODES; i++){
      if(n == graph->num_V)
        break;
      if(graph->a_list[i] != 0){
        BGP_shortest(graph, queue, i, length, length_p, length_r, length_c, curr_type, final_length, final_type, src, dest, question);
        n++;
      }
    }
  }
  //if the menu selection was 3, call BGP_shortest function to the given source and destination node
  else{
    ans = BGP_shortest(graph, queue, dest, length, length_p, length_r, length_c, curr_type, final_length, final_type, src, dest, question);
  }
  //print the asked length
  if(question == 3){
    if (ans == MAX_NODES)
      printf("There is no commercial path from %d to %d\n", src, dest);
    else
      printf("The length of the path from %d to %d is %d\n", src, dest, ans);
  }
  //print all the statistics
  else if(question == 6){
    printf("Lengths statistics :\n"
            "The number of paths with length 0 is %d\n"
            "The number of paths with length 1 is %d\n"
            "The number of paths with length 2 is %d\n"
            "The number of paths with length 3 is %d\n"
            "The number of paths with length 4 is %d\n"
            "The number of paths with length 5 is %d\n"
            "The number of paths with length 6 is %d\n"
            "The number of paths with length 7 is %d\n"
            "The number of paths with length 8 is %d\n"
            "The number of paths with length 9 is %d\n"
            "The number of paths with length 10 is %d\n"
            "The number of paths with length 11 is %d\n"
            "The number of paths with length 12 is %d\n"
            "The number of paths with length 13 is %d\n"
            "The number of paths with length 14 is %d\n"
            "The number of paths with length 15+ is %d\n",
            final_length[0], final_length[1], final_length[2], final_length[3], final_length[4], final_length[5],
            final_length[6], final_length[7], final_length[8], final_length[9], final_length[10], final_length[11],
            final_length[12], final_length[13], final_length[14], final_length[15]);

    printf("Types statistics: %d %d %d %d\n", final_type[0], final_type[1], final_type[2], final_type[3]);
  }

  //free arrays
  free(length);
  free(length_p);
  free(length_r);
  free(length_c);
  free(curr_type);
  free(final_length);
  free(final_type);
  exit(0);

}

/***************************************************************************
 * Function: BGP_shortest()
 *    Input: graph struct, queue struct, destination node, length array,
 *           provider's length array, peer's length array, customer's length
 *           array, type array, final length array (for stats), final type
 *           array (for stats), input source node, input destination node,
 *           input menu selection
 *     Task: Function that gets a destination node and finds the lengths of
 *           the shortest BGP paths from every other node to that node
 *   Output: returns the length of the path from the source node to the
 *           destination node introduced by the user
 **************************************************************************/
int BGP_shortest(struct Graph * graph, struct Queue * queue, int dest, int * length, int * length_p, int * length_r, int * length_c,
                  int * curr_type, int * final_length, int * final_type, int source, int destination, int question){

  struct node* temp, *node, *bgp_temp, *bgp_temp_free;
  int asked_len = 0;
  int asked_type = 0;
  int a = 0;
  int id_pop = 0;

  //put destination node in queue so it's the first one to be visited
  push_queue(queue, dest);
  //set the type of the destination node to -1
  curr_type[dest] = -1;
  //set the length of the destination node to 0 on all arrays
  length_p[dest] = 0;
  length_r[dest] = 0;
  length_c[dest] = 0;
  length[dest] = 0;

  while (queue->count != 0){
    //sees next node in queue
    id_pop = pop_queue(queue);

    //loops through the providers of id_pop
    temp = graph->a_list_p[id_pop];
    while(temp){
      //checks if the commercial rules are met and if the best path according to BGP is found
      if(temp->name != dest && (curr_type[id_pop] == -1 || curr_type[id_pop] == 1) && (curr_type[temp->name] == 0 || curr_type[temp->name] > 1)){
        length_p[temp->name] = length_p[id_pop] + 1;
        curr_type[temp->name] =  temp->type;
        push_queue(queue, temp->name);
      }
      temp = temp->next;
    }

    //loops through the peers of id_pop
    temp = graph->a_list_r[id_pop];
    while(temp){
      //checks if the commercial rules are met and if the best path according to BGP is found
      if(curr_type[temp->name] == 0 && temp->name != dest && (curr_type[id_pop] == -1 || curr_type[id_pop] == 1)){
        length_r[temp->name] = length_p[id_pop] + 1;
        curr_type[temp->name] = temp->type;
        push_queue(queue, temp->name);
      }
      temp = temp->next;
    }
  }

  //loops through the nodes that are in the queue
  for(int i = 0; i < MAX_NODES; i++){
    if(queue->array[i] == 0)
        break;
    else{
      //sees their immediate customers
      temp = graph->a_list_c[queue->array[i]];
      while(temp){
        //checks if the node has been visited by provider path and peer path
        if((length_p[queue->array[i]] != MAX_NODES && length_r[queue->array[i]] != MAX_NODES)){
          //if yes, it puts the immediate clientes of the one with the shortest length in the bgp_client list array
          node = createNode(temp->name, 3);
          if(length_p[queue->array[i]] < length_r[queue->array[i]])
            a = length_p[queue->array[i]] + 1;
          else
            a = length_r[queue->array[i]] + 1;

          if(graph->bgp_clients[a] == NULL)
            graph->bgp_clients[a] = node;
          else{
            node->next = (graph->bgp_clients[a])->next;
            (graph->bgp_clients[a])->next = node;
          }
        }
        //if it was only visited by a provider or a peer, and if the new length is either
        //shorter than the one seen before or never seen
        else{
          //it creates a node, and stores it in bgp_clients array
          node = createNode(temp->name, 3);
          if((length_p[queue->array[i]] + 1 < length_p[temp->name]))
            a = length_p[queue->array[i]] + 1;
          else if(length_r[queue->array[i]] + 1 < length_r[temp->name])
            a = length_r[queue->array[i]] + 1;

          if(graph->bgp_clients[a] == NULL)
            graph->bgp_clients[a] = node;
          else{
            node->next = (graph->bgp_clients[a])->next;
            (graph->bgp_clients[a])->next = node;
          }
        }
        temp = temp->next;
      }
    }
  }

  //loops through bgp_clients array
  for (int i = 1; i < MAX_NODES; i++){
    //loops through array list
    bgp_temp = graph->bgp_clients[i];
    while(bgp_temp){
      //checks if the node has been visited with a bigger path, or not visited at all
      if(length_c[bgp_temp->name] > i){
        //if yes, it changes its length to the length of bgp_clients
        length_c[bgp_temp->name] = i;
        //loops through the customers of the node
        temp = graph->a_list_c[bgp_temp->name];
        while(temp){
          //checks if its customers have been visited with a bigger path, or not visited at all
          if((length_c[bgp_temp->name] + 1) < length_c[temp->name]){
            //if yes, adds it to bgp_clients
            node = createNode(temp->name, 3);
            a = length_c[bgp_temp->name] + 1;
            if(graph->bgp_clients[a] == NULL)
              graph->bgp_clients[a] = node;
            else{
              node->next = (graph->bgp_clients[a])->next;
              (graph->bgp_clients[a])->next = node;
            }
          }
          temp = temp->next;
        }
      }
      //frees nodes that have been visited and have their length already in the length array
      bgp_temp_free = graph->bgp_clients[i];
      graph->bgp_clients[i] = bgp_temp_free->next;
      free(bgp_temp_free);
      bgp_temp = graph->bgp_clients[i];
    }
  }


  // for(int i = 1; i < MAX_NODES; i ++){
  //   if(length_p[i] != MAX_NODES && length_p[i] != -2){
  //     length[i] = length_p[i];
  //     if(length[i] != 0)
  //       curr_type[i] = 1;
  //   }
  //   else if( length_r[i] != MAX_NODES && length_r[i] != -2){
  //     length[i] = length_r[i];
  //     curr_type[i] = 2;
  //   }
  //   else if( length_c[i] != MAX_NODES && length_c[i] != -2){
  //     length[i] = length_c[i];
  //     curr_type[i] = 3;
  //   }
  // }


    // printf(" [");
    // for(int y = 1; y < 12; y++){
    //     printf("%d     ", length_p[y]);
    // }
    // printf("]\n");

    // printf("\n");

    // printf(" [");
    // for(int y = 1; y < 12; y++){
    //     printf("%d     ", length_r[y]);
    // }
    // printf("]\n");

    // printf("\n");

    // printf(" [");
    // for(int y = 1; y < 12; y++){
    //     printf("%d     ", length_c[y]);
    // }
    // printf("]\n");

    //  printf(" [");
    // for(int y = 1; y < 14; y++){
    //     printf("%d     ", length[y]);
    // }
    // printf("]\n");

    // printf("\n");
    // printf("\n");
    // printf("\n");

  for(int i = 1; i < MAX_NODES ; i++ ){
    //saves lengths by order of BGP preferences
    if(length_p[i] != MAX_NODES && length_p[i] != -2){
    length[i] = length_p[i];
    if(length[i] != 0)
      curr_type[i] = 1;
    }
    else if( length_r[i] != MAX_NODES && length_r[i] != -2){
      length[i] = length_r[i];
      curr_type[i] = 2;
    }
    else if( length_c[i] != MAX_NODES && length_c[i] != -2){
      length[i] = length_c[i];
      curr_type[i] = 3;
    }
    //statistics
    if(question == 6){
      //counts the number of times each type appears (0 are invalid paths)
      if(curr_type[i] >= 0){
        a = curr_type[i];
        final_type[a] = final_type[a] + 1;
      }
      //counts the number of times each length appears (10+ is one category)
      if(length[i] > 14 && length[i] != MAX_NODES)
        final_length[15] = final_length[15] + 1;
      else if(length[i] < 15 && length[i] != MAX_NODES && length[i] != -2){
        a = length[i];
        final_length[a] = final_length[a] + 1;
      }
    }
    //checks if this is the source-destination pair introduced by the user and if it is stores the length and type
    if(dest == destination && i == source){
      asked_len = length[i];
      asked_type = curr_type[i];
    }
    //initialise variables
    if(graph->a_list[i] != 0){
      length[i] = MAX_NODES;
      length_p[i] = MAX_NODES;
      length_r[i] = MAX_NODES;
      length_c[i] = MAX_NODES;
      curr_type[i] = 0;
    }
    else{
      length[i] = -2;
      length_p[i] = -2;
      length_r[i] = -2;
      length_c[i] = -2;
      curr_type[i] = -2;
    }
    queue->array[i] = 0;
  }
  //initialise variables
  queue->count = 0;
  queue->head = 0;
  queue->tail = 0;

  return asked_len;
}

/***************************************************************************
 * Function: freeAll()
 *    Input: pointer to graph struct, pointer to queue struct
 *     Task: Free memory allocated for these structures
 *   Output: none
 **************************************************************************/
void freeAll(struct Graph * graph, struct Queue * queue){

  struct node * temp, *temp1, *temp2;

  //loop through all the adjacency lists and free all elfs
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

  free(graph->a_list_p);
  free(graph->a_list_r);
  free(graph->a_list_c);
  free(graph->a_list);
  free(graph->bgp_clients);
  free(graph);
  free(queue->array);
  free(queue);
}
