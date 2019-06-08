#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/auxfunc.h"
#include "include/graph.h"


int main(int argc, char** argv)
{
    FILE* fp = fopen(argv[2], "r");
    if(fp == 0)
    {
        printf("arquivo nao foi carregado");
    }

    char buffer[20];
    read(fp, buffer);
    int num_nodes = atoi(buffer);

    read(fp, buffer);
    int num_edges = atoi(buffer);

    graph *new_graph = (graph*) malloc(sizeof(graph));
    *new_graph = graph_create(num_nodes);

    int i, node_a, node_b;
    for (i = 0; i < num_edges; i++)
    {
        read(fp, buffer);
        node_a = atoi(buffer);
        read(fp, buffer);
        node_b = atoi(buffer);

        graph_addEdge(new_graph, node_a, node_b);
    }

	if (strcmp(argv[1], "tarefa1") == 0)
	{
        printf("%d", graph_getMinimumVertexCoverSize(new_graph));
	}
	if (strcmp(argv[1], "tarefa2") == 0)
	{
		int* cover_set = graph_get2Approximation(new_graph);

		for (i = 0; i < num_nodes; i++)
		{
			if (cover_set[i] == 1)
			{
				printf("%d\n", i);
			}
		}
		free(cover_set);
	}

  graph_deleteGraph(new_graph);
	free(new_graph);

	fclose(fp);

	return 0;
}
