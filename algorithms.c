#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


// Create a new node
struct node* createNode(int id_node) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->id = id_node;
  newNode->next = NULL;
  return newNode;
}

// Create a graph of V vertices
struct Graph* createGraph(int v) {
  struct Graph* graph = malloc(sizeof(struct Graph));

  graph->num_V = v;

// Create vertical array of nodes (size v)
  graph->array = (struct A_List*) malloc(v * sizeof(struct A_List));

  for (int i = 0; i < v; i++)
    graph->array[i].head = NULL;

  return graph;
}

/* Adds an edge to a graph*/
void addEdge(struct Graph* graph, int src, int dest)
{
    /* Add an edge from src to dst in the adjacency list*/
    struct node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    graph->array[src].n++;

    // if(graph->type == UNDIRECTED)
    // {
    //     /* Add an edge from dest to src also*/
    //     newNode = createNode(src);
    //     newNode->next = graph->adjListArr[dest].head;
    //     graph->adjListArr[dest].head = newNode;
    //     graph->adjListArr[dest].num_members++;
    // }
}

// Print the graph
void printGraph(struct Graph* graph) {
  int v;

  for (v = 0; v < graph->num_V; v++) {
    struct node* temp = graph->array[v].head;
    printf("\n Vertex %d\n: ", v);
    while (temp) {
      printf("%d -> ", temp->id);
      temp = temp->next;
    }
    printf("\n");
  }
}


// int Connected(G)
// {

//     return (0);
// }