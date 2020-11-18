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

    //Checks number of arguments
    if(argc < 2){
        printf("There are arguments missing.You must insert the name of a text file.\n");
        exit(0);
    }

    fileNameIn = argv[1];

    len= strlen(argv[1]);
    //Checks if the extension of the file is correct
    if(fileNameIn[len-1] == 't' && fileNameIn[len-2] == 'x' && fileNameIn[len-3]== 't' && fileNameIn[len-4]== '.')
    {
        //open file
        internet = fopen(argv[1], "r");
        if (internet == NULL){
            printf("File not found in this directory\n");
            exit(EXIT_FAILURE);
        }
        //retrieves the data from each line
        while (fscanf(internet, "%d %d %d", &src, &dest, &type) == 3){
            if (type == 1 || type == 2)
                addEdge(graph, src, dest, type);
        }

        while(1){

            printf("\nChoose the algorithm you want to run:\n"
                "1. Check types\n"
                "2. Check length\n"
                "3. 3\n"
                "4. Print adjacency list\n"
                "5. Exit\n\n");
            //retrieves option chose
            scanf("%d", &option);

            if(option == 1){
                //alg1
            }

            else if(option == 2){
                if(graph->tier1[0] != -2)
                    findTier1(graph);
                //if(graph->n_tier1 > 0)
                check_length(graph, queue);
                // else
                //     NoTier1_CommerciallyConn(graph);
            }

            else if(option == 3){
               //alg4
            }
            else if(option == 4)
                printGraph(graph);

            else if(option == 5){
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