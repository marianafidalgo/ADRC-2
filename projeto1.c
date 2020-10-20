#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

#define MAX_NODES 65536

int main() {

    FILE * internet;
    long int lines =0;
    int type, src, dest = 0;
    ssize_t read;
    size_t len = 0;

    internet = fopen("LargeNetwork.txt", "r");
    if (internet == NULL)
        exit(EXIT_FAILURE);

    long int links = 65535;

    struct Graph * graph = createGraph(links);
    struct node * temp;

    int t2=0;
    int nos = 0;
    int nodes;

    while (fscanf(internet, "%d %d %d", &src, &dest, &type) == 3){

        // if (type == 1){
        //     addEdge(graph, src, dest, type);
        // }
        // else if (type == 2)
        // {
        //     addEdge(graph, src, dest, type);
        // }

        addEdge(graph, src, dest, type);
    }

    //printGraph(graph);
    fclose(internet);


    // function CONNECTED
    int result = 0;

    result = connected(graph, links, nodes);

    if(result == 1)
        printf("The internet is connected\n");
    else
        printf("The internet is not connected\n");


  return(0);
}