#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

#define MAX_NODES 65536

int main(int argc, char **argv) {

    FILE * internet;
    long int lines =0;
    int type, src, dest = 0;
    int algorithm = 0;
    int links = MAX_NODES;
    int t2 = 0;
    int nos = 0;
    int nodes;
    ssize_t read;
    size_t len = 0;
    struct Graph * graph = createGraph(links);
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
        if(algorithm == 1){
            addEdge(graph, src, dest, algorithm);
            // function CONNECTED
            int result = 0;

            result = connected(graph, links, nodes);

            if(result == 1)
                printf("The internet is connected\n");
            else
                printf("The internet is not connected\n");
        }
        else if(algorithm == 3)
        {
            if (type == 1)
               addEdge(graph, src, dest, algorithm);

        }
        else if(algorithm == 4){
            if (type == 1)
                addEdge(graph, src, dest, algorithm);
            else if (type == 2)
                addEdge(graph, src, dest, algorithm);
        }
    }

    if(algorithm == 1){
            // function CONNECTED
            int result = 0;

            result = connected(graph, links, nodes);

            if(result == 1)
                printf("The internet is connected\n");
            else
                printf("The internet is not connected\n");
        }
    else if(algorithm == 3){
        printf("nodes %d\n", graph->num_V);
    }
    else if(algorithm == 4){
        //algorithm 4
    }
    //printGraph(graph);
    fclose(internet);

  return(0);
}