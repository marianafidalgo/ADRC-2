#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main(int argc, char **argv) {

    FILE * internet;
    long int lines = 0;
    int type, src, dest = 0;
    int option = 0;
    struct Graph * graph = createGraph();
    struct node * temp;

    internet = fopen(argv[1], "r");
    if (internet == NULL)
        exit(EXIT_FAILURE);

    while (fscanf(internet, "%d %d %d", &src, &dest, &type) == 3){
    if (type == 1 || type == 2)
        addEdge(graph, src, dest, type);
    }

    while(1){

        printf("\nChoose the algorithm you want to run:\n"
            "1. Check if internet is connected\n"
            "2. Check if internet is link-biconnected\n"
            "3. Check if internet is commercially acyclic\n"
            "4. Check if internet is commercially connected\n"
            "5. Print adjacency list\n"
            "6. Exit\n\n");
        scanf("%d", &option);

        if(option == 1){

            int result = 0;

            result = connected(graph);

            if(result == 1)
                printf("The internet is connected\n");
            else
                printf("The internet is not connected\n");

        }
        else if(option == 2){
            //algorithm 2
        }
        else if(option == 3){
            checkCycles(graph);
        }
        else if(option == 4){
            int result4 = 1;
            if(graph->tier1[0] != -2)
                findTier1(graph);
            result4 = CommerciallyConn(graph);

            if(result4 == -1)
                printf("The internet is not commercially connected\n");
            else
                printf("The internet is commercially connected\n");
        }
        else if(option == 5){
            printGraph(graph);
        }
        else if(option == 6){
            fclose(internet);
            freeAll(graph);
            exit(0);
        }

    }

  return(0);
}