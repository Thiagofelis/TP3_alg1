#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "auxfunc.h"

typedef struct edge
{
    int vertex;
    struct edge* next;
} edge;

typedef struct graph
{
    int num_v;
    edge** adj_list;
} graph;

graph graph_create(int _num_v);

void graph_addEdge(graph *gp, int v, int u);

void graph_addSingleEdge(graph *gp, int v, int u);

void graph_print(graph *gp);

void graph_deleteGraph(graph* gp);

int* graph_get2Approximation(graph* gp);

int graph_getMinimumVertexCoverSize(graph *gp);

void graph_recursiveMVC(graph* gp, int v, int parent_v, int* OPT_v, int* COPT_v);

#endif // GRAPH_H_INCLUDED
