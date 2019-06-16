#include "../include/graph.h"

graph graph_create(int _num_v)
{
	// on the chosen implementation, we allocate an array of edge*.
	// at position i, we put the head of the list of edges incident to node i

    graph new_graph;
    new_graph.num_v = _num_v;
    new_graph.adj_list = (edge**) malloc(_num_v * sizeof(edge*));

    edge* head;
    int i;
    for (i = 0; i < _num_v; i++)
    {
        head = (edge*) malloc(sizeof(edge));
        new_graph.adj_list[i] = head;
        head->vertex = -1;
        head->next = 0;
    }
    return new_graph;
}

void graph_addEdge(graph *gp, int v, int u)
{
    graph_addSingleEdge(gp, v, u);
    graph_addSingleEdge(gp, u, v);
}

void graph_addSingleEdge(graph *gp, int v, int u)
{
    edge* head = (gp->adj_list)[v];

    edge* ep = (edge*) malloc(sizeof(edge));
    ep->vertex = u;
    ep->next = head->next;
    head->next = ep;
}

void graph_print(graph *gp)
{
    int i;
    for (i = 0; i < gp->num_v; i++)
    {
        edge* temp = ((gp->adj_list)[i])->next;
        printf("edges incident to node %d: ", i);
        while (temp != 0)
        {
            printf("(%d to %d), ", i, temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void graph_deleteGraph(graph* gp)
{
    edge *temp, *temp2;
    int i;
    for (i = 0; i < gp->num_v; i++)
    {
        temp = (gp->adj_list)[i];
        while (temp != 0)
        {
            temp2 = temp;
            temp = temp->next;
            free(temp2);
        }
    }
    free(gp->adj_list);
}

int graph_getMinimumVertexCoverSize(graph *gp)
{
    // OPT(v) -> minimum vertex cover size for <v>
    // (<v> is define as the childre tree of v, that is,
    // the subtree rooted in v)
    int *OPT_v = malloc(sizeof(int));
    int *COPT_v = malloc(sizeof(int));

    graph_recursiveMVC(gp, 0, 0, OPT_v, COPT_v);

    int MVC_size = *OPT_v;

    free(OPT_v);
    free(COPT_v);

    return MVC_size;
}

void graph_recursiveMVC(graph* gp, int v, int parent_v, int* OPT_v, int* COPT_v)
{
    int OPT_covered = 1, OPT_not_covered = 0;
    *COPT_v = 0;

    int *OPT_w = malloc(sizeof(int));
    int *COPT_w = malloc(sizeof(int));

    edge* temp = (gp->adj_list)[v]->next;
    while (temp != 0)
    {
        if (parent_v != temp->vertex)
        {
            graph_recursiveMVC(gp, temp->vertex, v, OPT_w, COPT_w);
            OPT_covered += *OPT_w;
            OPT_not_covered += 1 + *COPT_w;
            *COPT_v += *OPT_w;
        }
        temp = temp->next;
    }
    free(OPT_w);
    free(COPT_w);

    *OPT_v = OPT_covered > OPT_not_covered ? OPT_not_covered : OPT_covered;
}

int* graph_get2Approximation(graph* gp)
{
	int covered[gp->num_v];
	int i;
	int *cover_set = malloc(gp->num_v * sizeof(int));

	for (i = 0; i < gp->num_v; i++)
	{
		cover_set[i] = 0;
		covered[i] = 0;
	}

	edge* temp;
	int opposite_vertex;

	for (i = 0; i < gp->num_v; i++)
	{

		if (covered[i] == 0)
		{
			// searches for an edge not covered
			temp = ((gp->adj_list)[i])->next;
			while (temp != 0 && covered[temp->vertex] == 1)
			{
				temp = temp->next;
			}

			if (temp == 0)
			// all the edges are already covered
			{
				covered[i] = 1;
			}
			else
			{
				opposite_vertex = temp->vertex;
				covered[i] = 1;
				covered[opposite_vertex] = 1;
				cover_set[i] = 1;
				cover_set[opposite_vertex] = 1;
			}

		}
	}
	return cover_set;
}
