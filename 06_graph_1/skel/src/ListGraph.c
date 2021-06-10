#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListGraph.h"
#include "utils.h"

list_graph_t*
lg_create(int nodes)
{
	list_graph_t *graph = calloc(1, sizeof(list_graph_t));
	DIE(!graph, "calloc graph");
	graph->neighbors = (linked_list_t **) calloc(nodes, sizeof(linked_list_t*));
	DIE(!graph->neighbors, "calloc neighbours");
	for (int i = 0; i < nodes; i++)
		graph->neighbors[i] = ll_create(sizeof(int));

	graph->nodes = nodes;
	return graph;
}

void
lg_add_edge(list_graph_t* graph, int src, int dest)
{
	ll_add_nth_node(graph->neighbors[src], graph->neighbors[src]->size, &dest);
}

int
lg_has_edge(list_graph_t* graph, int src, int dest)
{
	linked_list_t *list = graph->neighbors[src];
	ll_node_t *temp = list->head;
	
	while (temp != NULL) {
		if (memcmp(temp->data, &dest, list->data_size) == 0)
			return 1;
		temp = temp->next;
	}
	return 0;
}

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node)
{
	return graph->neighbors[node];
}

void
lg_remove_edge(list_graph_t* graph, int src, int dest)
{	
	int contor = 0;
	linked_list_t *list = graph->neighbors[src];
	ll_node_t *temp = list->head;

	
	while (*(int *)temp != dest) {
		if (memcmp(temp->data, &dest, list->data_size) == 0) {
			break;
		}
		contor++;
		temp = temp->next;
	}
	ll_node_t *aux = ll_remove_nth_node(graph->neighbors[src], contor);
	free(aux);
	free(aux->data);
}

void
lg_free(list_graph_t* graph)
{
	for (int i = 0; i < graph->nodes; i++)
		ll_free(&graph->neighbors[i]);
	free(graph->neighbors);
	free(graph);
}