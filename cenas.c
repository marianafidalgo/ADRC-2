while (queue->count != 0){
    //pops first item in queue, marks as visiteda and see it's adjacent nodes
    int id_pop = pop_queue(queue);
    graph->visited[id_pop] = 1;

    temp = graph->a_list[id_pop];

    //put popped items adjacent nodes in queue
    printf("No src: %d\n", id_pop);
    while(temp)
    {
      printf("Vizinho: %d\n",temp->name);
      //if it's not visited we put the adjacent node in queue
      if(graph->visited[temp->name] == 0){
        if(length[src][temp->name] == 0){
          curr_type[temp->name] = temp->type;
          if(curr_type[id_pop] == -1 || curr_type[id_pop] == 1 || ((curr_type[id_pop] == 2 || curr_type[id_pop] == 3) && curr_type[temp->name] == 3)){
            printf("length: %d\n", graph->l[id_pop]);
            graph->visited[temp->name] = 1;
            length[src][temp->name] = graph->l[id_pop] + 1;
            graph->l[temp->name] = length[src][temp->name];
            push_queue(queue, temp->name);
          }
        }
      }
      temp = temp->next;
    }
  }