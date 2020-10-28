#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

artPoints(u){/*

    discovered[u] = true;
    time = time +1; 
    d[u] = time;
    l[u] = d[u] ;

    for(each edge uv){
        if (discovered[v] == false){
            if( u is root and v is it second child )
                u is an articulation point 
            pred[v] = u
            artPoints(v)
            if(l[v] >= d[u]) 
                u is an articulation point 
            l[u] = min{l[u], l[v]} 
        }
        else if (v != pred[u]){
            l[u] = min{l[u], d[v]}
        }
    }*/
}

void checkBridges(struct Graph* graph){

  int pred[MAX_NODES];
  int stack[MAX_NODES];
  int curr = 0;
  int cycle = 0;
  int i;

  for(i = 0; i < MAX_NODES; i++){
    pred[i] = 0;
    stack[i] = 0;
  }
  if(graph->tier1[0] != -2)
    findTier1(graph);

  for(i = 1; i < MAX_NODES; i++){
    if(graph->tier1[i] == 1){
      if(graph->visited[i] == 0)

        cycle = DFS_bridge(graph, i, curr, pred, stack);
    }
    graph->visited[i] = 0;
  }
}

int DFS_bridge(struct Graph* graph, int v, int curr, int pred[], int stack[]){
  struct node* temp;
  int cycle = 0, i = 0, j = 0, time=0;

  graph->visited[v] = 1;

  time=time+1;
  stack[curr] = v;
  curr++;

  temp = graph->a_list[v];
  while(temp){

    pred[v]=temp->name; //guarda o predecessor

    if(graph->visited[temp->name] == 0){
      cycle = DFS_cycles(graph, temp->name, curr, pred, stack);
      if(cycle == 1)
        return 1;
    }
    temp = temp->next;
  }


  return cycle;
}




/*int push_queue_LIFO(struct Graph* graph, int new_id ) //quero insirer em cima, na head
{
    graph->queue[graph->head] = new_id;
    graph->count++;
    graph->tail++;
}

int pop_queue_LIFO( struct Graph* graph )//quero tirar de cima, da head
{
  int item = -1;

  item = graph->queue[graph->head];
  graph->head++;
  if(graph->head > graph->tail)
  {
    //reset queue
    graph->head = graph->tail = 0;
  }
  graph->count--;

  return item;
}*/



// A recursive function that finds and prints bridges using 
// DFS traversal 
// u --> The vertex to be visited next 
// visited[] --> keeps tract of visited vertices 
// disc[] --> Stores discovery times of visited vertices 
// parent[] --> Stores parent vertices in DFS tree 
void bridges(struct Graph* graph, int u, int  visited[], int disc[], int l[], int pred[]){ 
    int time = 0;
    struct node* temp; 
  
    // Mark the current node as visited 
    visited[u] = 1; 
  
    // Initialize discovery time and low value 
    time= time+1;
    disc[u]= time;
    l[u]= time; 

    temp=graph->a_list[u];
  
    // Go through all vertices aadjacent to this 
    //for (i = adj[u].begin(); i != adj[u].end(); ++i) 
    while(temp!=NULL)
    { 
        int v = temp->name;  // v is current adjacent of u 
  
        // If v is not visited yet, then recur for it 
        if (visited[v]!=1 && temp->type!=3) 
        { 
            pred[v] = u; 
            bridges(graph, v, visited, disc, l, pred); 
  
            // Check if the subtree rooted with v has a  
            // connection to one of the ancestors of u 
            l[u]  = min(l[u], l[v]); 
  
            // If the lowest vertex reachable from subtree  
            // under v is  below u in DFS tree, then u-v  
            // is a bridge 
            if (l[v] > disc[u]) 
                print("There is a bridge %d-%d|", u,v);
                exit(0); //arranjar outra forma de pôr isto, tipo com uma flag, só para ele parar assim que encontrar 1 ponte
        } 
        else if (v != pred[u])  // Update low value of u for parent function calls. 
            l[u]  = min(l[u], disc[v]); 
        
        temp=temp->next;
    } 
    return ;
} 

  
// DFS based function to find all bridges. It uses recursive  
// function bridgeUtil() 
void find_bridges(struct Graph* graph){ 

    int visited[MAX_NODES]; //graph->num_V , ver se é melhor só criar vetores com este tamanho
    int disc[MAX_NODES]; 
    int l[MAX_NODES]; 
    int pred[MAX_NODES];
    int i=0;

    // Initialize predecessor and visited arrays 
    for (i = 0; i < MAX_NODES; i++){ 
        pred[i] = 0; 
        visited[i] = 0; 
    } 

    /*if(graph->tier1[0] != -2)
        findTier1(graph);*/

    // Call the recursive function to find Bridges 
    // in DFS tree rooted in vertex 'i' 
    for(i = 1; i < MAX_NODES; i++){
        if(graph->visited[i] == 0)
            bridgeUtil(graph, i, visited, disc, l, pred);
        //graph->visited[i] = 0;
    }

} 