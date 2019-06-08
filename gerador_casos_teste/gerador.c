#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char** argv)
{
  int n = atoi(argv[2]);
  int m = atoi(argv[3]);
  srand(atoi(argv[4]) * time(0));

  FILE *fp = fopen(argv[5], "w");

  if (strcmp(argv[1], "tarefa1") == 0)
	{
    fprintf(fp, "%d %d\n", n, n-1);
    int i, node_a, master_node, num_nodes_in_graph;
    int was_inserted[n];
    int nodes_in_graph[n];
    for (i = 0; i < n; i++)
    {
      was_inserted[i] = 0;
    }
    master_node = rand() % n;
    was_inserted[master_node] = 1;
    nodes_in_graph[0] = master_node;
    num_nodes_in_graph = 1;

    for(i = 0; i < n - 1; i++)
    {
      do {
        node_a = rand() % n;
      } while(was_inserted[node_a] == 1);

      fprintf(fp, "%d %d\n", node_a, nodes_in_graph[rand() % num_nodes_in_graph]);

      was_inserted[node_a] = 1;
      nodes_in_graph[num_nodes_in_graph] = node_a;
      num_nodes_in_graph++;
    }

	}
	if (strcmp(argv[1], "tarefa2") == 0)
	{
    fprintf(fp, "%d %d\n", n, m);
    int i, j, node_a, node_b;
    int was_inserted[n][n];
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
      {
        was_inserted[i][j] = 0;
      }
    }
    for(i = 0; i < m; i++)
    {
      do {
        node_a = rand() % n;
        node_b = rand() % n;
      } while(node_a == node_b || was_inserted[node_a][node_b] == 1);

      was_inserted[node_a][node_b] = 1;
      was_inserted[node_b][node_a] = 1;

      fprintf(fp, "%d %d\n", node_a, node_b);
    }
  }
  fclose(fp);
  return 0;
}
