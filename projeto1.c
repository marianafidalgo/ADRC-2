#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main() {

    FILE * internet;
    long int lines =0;
    int type;
    ssize_t read;
    size_t len = 0;
    char * line = NULL;
    char *src = NULL;
    char *dest = NULL;
    char *type_  = NULL;

    internet = fopen("int.txt", "r");
    if (internet == NULL)
        exit(EXIT_FAILURE);

    while (EOF != (fscanf(internet, "%*[^\n]"), fscanf(internet,"%*c")))
        ++lines;

    rewind(internet);
    int n_nodes = lines/2;

    struct Graph* graph = createGraph(n_nodes);
    struct node * temp;

    lines = 0;

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

        }
    }

    printGraph(graph);
    fclose(internet);


    // function CONNECTED
    int result;
    result = connected(graph, n_nodes);
    if(result == 1)
        printf("The internet is connected\n");
    else
        printf("The internet is not connected\n");

    free(line);

    for (int i = 0; i <= graph->it; i++){
      while(graph->a_list[i] != NULL)
      {
          temp = graph->a_list[i];
          graph->a_list[i]=graph->a_list[i]->next;
          free(temp->name);
          free(temp);
      }
    }
    free(graph->visited);
    free(graph->a_list);
    free(graph);

  return(0);
}