#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

#define MAX_NODES 65536

int main(int argc, char **argv) {

    FILE * internet;
    long int lines = 0;
    int type, src, dest = 0;
    int algorithm = 0;
    struct Graph * graph = createGraph(MAX_NODES);
    struct node * temp;

    internet = fopen(argv[1], "r");
    if (internet == NULL)
        exit(EXIT_FAILURE);

    printf("Choose the algorithm you want to run:\n"
           "1. Check if internet is connected\n"
           "2. Check if internet is link-biconnected\n"
           "3. Check if internet is commercially acyclic\n"
           "4. Check if internet is commercially connected\n");
    scanf("%d", &algorithm);

    while (fscanf(internet, "%d %d %d", &src, &dest, &type) == 3){
        if (type == 1 || type == 2)
            addEdge(graph, src, dest, type);
    }

    printGraph(graph);

    if(algorithm == 1){

        int result = 0;

        result = connected(graph, MAX_NODES);

        if(result == 1)
            printf("The internet is connected\n");
        else
            printf("The internet is not connected\n");

    }
    else if(algorithm == 2){
        //algorithm 2
    }
    else if(algorithm == 3){
        printf("nodes %d\n", graph->num_V);
        int result3 = 0;

        result3 = checkCycles(graph);
        if(result3 == 1)
            printf("The internet is not commercially acyclic\n");
        else
            printf("The internet is commercially acyclic\n");
    }
    else if(algorithm == 4){
        int result4 = 1;
        if(graph->tier1[0] != -2)
            findTier1(graph, MAX_NODES);
        result4 = CommerciallyConn(graph, MAX_NODES);

        if(result4 == -1)
            printf("The internet is not commercially connected\n");
        else
            printf("The internet is commercially connected\n");
    }

    fclose(internet);

  return(0);
}