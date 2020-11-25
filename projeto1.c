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
                "1. Check type of path elected by BGP from a source to a destination\n"
                "2. Check length of path elected by BGP from a source to a destination\n"
                "3. Check length of the shortest path, of the same type as the one computed by BGP, from a source to a destination\n"
                "4. Print adjacency list\n"
                "5. Show statistics of 1st, 2nd options for all source-destination paths\n"
                "6. Show statistics of 3rd option for all source-destination paths\n"
                "7. Exit\n\n");
            //retrieves option chose
            scanf("%d", &option);

            if(option == 1)
            {
                printf("Enter source and destiny node:\n");
                if(scanf("%d %d", &src, &dest) == 2){
                    check_length_type(graph, queue, src, dest, option);
                }
                else
                    printf("Invalid input\n");
            }

            else if(option == 2){
                printf("Enter source and destiny node:\n");
                if(scanf("%d %d", &src, &dest) == 2){
                    check_length_type(graph, queue, src, dest, option);
                }
                else
                    printf("Invalid input\n");
            }

            else if(option == 3){
               //alg3
            }
            else if(option == 4)
                printGraph(graph);

            else if(option == 5){
                check_length_type(graph, queue, 1, 2, option);
            }

            else if(option == 6){
               
            }
            else if(option == 7){
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