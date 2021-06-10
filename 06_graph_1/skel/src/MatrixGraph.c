#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "MatrixGraph.h"

/**
 * Initializeaza graful cu numarul de noduri primit ca parametru si aloca
 * memorie pentru matricea de adiacenta a grafului.
 */
matrix_graph_t*
mg_create(int nodes)
{
	matrix_graph_t *graph = NULL;
	graph = calloc(1, sizeof(matrix_graph_t));
	DIE(!graph, "calloc graph");
	graph->matrix = (int **) calloc(nodes, sizeof(int*));
	DIE(!graph->matrix, "calloc matrix");
	for (int i = 0; i < nodes; i++)
		graph->matrix[i] = (int *)calloc(nodes, sizeof(int));

	graph->nodes = nodes;
	return graph;
}

/* Adauga o muchie intre nodurile sursa si destinatie */
void
mg_add_edge(matrix_graph_t* graph, int src, int dest)
{
	graph->matrix[src][dest] = 1;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int
mg_has_edge(matrix_graph_t* graph, int src, int dest)
{
	if (graph->matrix[src][dest] == 1)
		return 1;
	return 0;
}

/* Elimina muchia dintre nodurile sursa si destinatie */
void
mg_remove_edge(matrix_graph_t* graph, int src, int dest)
{
	graph->matrix[src][dest] = 0;
}

/* Elibereaza memoria folosita de matricea de adiacenta a grafului */
void
mg_free(matrix_graph_t* graph)
{
	for (int i = 0; i < graph->nodes; i++) {
		free(graph->matrix[i]);
	}
	free(graph->matrix);
	free(graph);
}