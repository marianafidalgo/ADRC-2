#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

int count = 0;//count for adjlist place for vertices

struct AdjListNode
{
    char name[10];//lecture name
    struct AdjListNode* next;
    int id;//id for place of vertex in array of graph
};
struct AdjListNode *desti, *source, *newNode, *temp, *pCrawl; 

struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
struct AdjList *array;

struct Graph
{
    int it;
    int V;
    struct AdjList* array;
};
struct Graph *graph;

struct AdjListNode* newAdjListNode(char name[10])
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    memcpy(newNode->name, name, sizeof newNode->name);
    newNode->id = count;
    newNode->next = NULL;


    return newNode;
}

struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->it = 0;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

void addEdge(struct Graph* graph, char src[10], char dest[10])
{;
    //i create destination vertex and source vertex
    struct AdjListNode* desti = newAdjListNode(dest);//
    struct AdjListNode* source = newAdjListNode(src);
    struct AdjListNode * temp=graph->array[0].head;
    //i try to connect them 
    graph->array[0].head=source;
    graph->array[0].head->next=desti;
    ++(graph->it);

    if(temp)
    desti->next=temp->next;
}

void printGraph(struct Graph* graph)
{
    int v;
    struct AdjListNode* pCrawl = graph->array[0].head;
    for (v = 0; v <= graph->it; ++v)
    {

        printf("name: %s   ", pCrawl->name);
        pCrawl=pCrawl->next;
}
        printf("\n");
}
int main()
{
    // create the graph given in above fugure
    int V = 5;
    struct Graph* graph = createGraph(V);
    //newAdjListNode("BS11");
    //newAdjListNode("CS10");
    //newAdjListNode("MATH10"); 
    addEdge(graph, "CS10", "MATH10");

    addEdge(graph, "BS11", "CS10");

    printGraph(graph);
    return 0;
}