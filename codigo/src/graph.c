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

graph graph_duplicateGraph(graph *gp)
{
    graph new_graph = graph_create(gp->num_v);

    int i;
    for (i = 0; i < gp->num_v; i++)
    {
        edge* temp = ((gp->adj_list)[i])->next;
        while (temp != 0)
        {
            graph_addSingleEdge(&new_graph, i, temp->vertex);
            temp = temp->next;
        }
    }
    return new_graph;
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
    int *OPT = malloc(gp->num_v * sizeof(int));
    int i;
    for (i = 0; i < gp->num_v; i++)
    {
        OPT[i] = -1;
    }

    // COPT(v) -> minimum vertex cover size for <w_1, ..., w_n>,
    // with w_1, ..., w_n in v*
    // (v* is define as the set of the children nodes of v)
    int *COPT = malloc(gp->num_v * sizeof(int));
    int *parent = malloc(gp->num_v * sizeof(int));

    // node 0 has no parent
    parent[0] = -1;

    graph_recursiveMVC(gp, 0, parent, OPT, COPT);


    int MVCsize = OPT[0];

    free(parent);
    free(OPT);
    free(COPT);

    return MVCsize;
}

void graph_recursiveMVC(graph* gp, int node, int* parent, int* OPT, int* COPT)
{
    if (OPT[node] != -1)
    // than we don't need to calculate it again
    {
        return;
    }

    int iscovered = 1, isnotcovered = 0, flag = 0;

    COPT[node] = 0;
    edge* temp = (gp->adj_list)[node]->next;
    while (temp != 0)
    {   // i won't comment the following code, it can be easily
        // understood from the documentation
        if (parent[node] != temp->vertex)
        {
            parent[temp->vertex] = node;
            graph_recursiveMVC(gp, temp->vertex, parent, OPT, COPT);

            iscovered += OPT[temp->vertex];
            isnotcovered += 1 + COPT[temp->vertex];
            COPT[node] += OPT[temp->vertex];
            flag = 1;
        }
        temp = temp->next;
    }

    if (flag == 0)
    // childless node
    {
        COPT[node] = 0;
        OPT[node] = 0;
    }
    else
    {
        OPT[node] = iscovered > isnotcovered ? isnotcovered : iscovered;
    }
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
