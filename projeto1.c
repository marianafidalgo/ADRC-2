#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main(int argc, char **argv) {

    FILE * internet;
    long int lines = 0;
    int type, src, dest = 0;
    int option, len = 0;
    char * fileNameIn;
    struct Graph * graph = createGraph();
    struct Queue * queue = createQueue();

    /* Checks number of arguments */
    if(argc < 2){
        printf("There are arguments missing.You must insert the name of a text file.\n");
        exit(0);
    }

    fileNameIn = argv[1];

    len= strlen(argv[1]);
    /*checks if the extension of the file is correct*/
    if(fileNameIn[len-1] == 't' && fileNameIn[len-2] == 'x' && fileNameIn[len-3]== 't' && fileNameIn[len-4]== '.')
    {

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

            if(option == 1)
                connected(graph, queue);

            else if(option == 2){
                //algorithm 2
            }
            else if(option == 3)
                checkCycles(graph);

            else if(option == 4)
                CommerciallyConn(graph);

            else if(option == 5)
                printGraph(graph);

            else if(option == 6){
                fclose(internet);
                freeAll(graph, queue);
                exit(0);
            }

        }
    }
    else{
        printf("The file must have the extension .txt .\n");
    }
  return(0);
}