#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "functions.h"

int main() {

    FILE * internet;
    long int lines =0;
    ssize_t read;
    size_t len = 0;

    internet = fopen("int.txt", "r");
    if (internet == NULL)
        exit(EXIT_FAILURE);

    while (EOF != (fscanf(internet, "%*[^\n]"), fscanf(internet,"%*c")))
        ++lines;

    rewind(internet);
    int n_nodes = lines/2;

    struct Graph* graph = createGraph(n_nodes);

    lines = 0;
    char * line, *src, *dest, *type_  = NULL;
    int type;
    while ((read = getline(&line, &len, internet)) != -1) {
        lines++;
        src = strtok(line, " ");
        dest = strtok(NULL, " ");
        type_ = strtok(NULL, " ");

        type = atoi(type_);

        if (type == 1){
            addEdge(graph, src, dest, n_nodes);

        }
        else if (type == 2)
        {
            addEdge(graph, src, dest,n_nodes);
            addEdge(graph, src, dest,n_nodes);

        }

    }

    printGraph(graph);
    fclose(internet);

    //save last src id for BFS

  // function CONNECTED
    // int result;
    // result = connected(graph, n_nodes);
    // printf("Connected? %d\n", result);

  return(0);
}