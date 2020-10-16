#include <stdio.h>
#include <stdlib.h>


#include "functions.h"

int main() {

    FILE * internet;
    int type, src, dest;
    long int lines =0;

    internet = fopen("int.txt", "r");
    if (internet == NULL)
        exit(EXIT_FAILURE);

    while (EOF != (fscanf(internet, "%*[^\n]"), fscanf(internet,"%*c")))
        ++lines;

    rewind(internet);
    int n_nodes = lines/2;

    struct Graph* graph = createGraph(n_nodes);
    lines = 0;
    int r = fscanf(internet, "%d %d %d\n", &src, &dest, &type);
    while (r != EOF)
    {
        lines++;
        if (type == 1)
            addEdge(graph, src, dest);

        else if (type == 2)
        {
            addEdge(graph, src, dest);
            addEdge(graph, src, dest);
        }

        r = fscanf(internet, "%d %d %d\n", &src, &dest, &type);
    }

    printGraph(graph);


    fclose(internet);


  // function CONNECTED

  return(0);
}