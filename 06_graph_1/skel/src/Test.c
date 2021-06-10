#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Queue.h"
#include "Stack.h"

#define MAX_NODES 10


void
print_matrix_graph(matrix_graph_t* mg)
{
	for (int i = 0; i < mg->nodes; i++) {
		for(int j = 0; j < mg->nodes; j++) {
			printf("%d ", mg->matrix[i][j]);
		}
		printf("\n");
	}
}

void
print_list_graph(list_graph_t* lg)
{
	for (int i = 0; i < lg->nodes; i++) {
		linked_list_t *list = lg->neighbors[i];
		ll_node_t *temp = list->head;
		while (temp != NULL) {
			printf("%d ", *(int *)temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}

void
dfs_list_graph(list_graph_t* lg,
				int node,
				int* visited,
				int* t_desc,
				int* t_tin)
{
	int contor = 0;
	stack_t *stack = st_create(sizeof(int));
	visited[node] = 1;
	st_push(stack, &node);
	while (st_is_empty(stack) != 0) {
		int nod_top = st_peek(stack);
		linked_list_t *list = lg->neighbors[nod_top];
		ll_node_t *temp = list->head;

		int find = 0;
		while (temp != NULL) {
			if (visited[*(int*)temp->data] == 0) {
				contor++;
				t_desc[*(int*)temp->data] = contor;
				visited[*(int*)temp->data] = 1;
				printf("%d ", *(int*)temp->data);
				st_push(stack, *(int*)temp->data);
				find = 1;
				break;
			}
			temp = temp->next;
		}

		if (find == 0) {
			contor++;
			t_tin[nod_top] = contor;
			visited[nod_top] = 1;
			st_pop(stack);
		}
	}
}

void
dfs_matrix_graph(matrix_graph_t* mg,
				 int node,
				 int* visited,
				 int* t_desc,
		 		 int* t_tin)
{
	int contor = 0;
	stack_t *stack = st_create(sizeof(int));
	visited[node] = 1;
	st_push(stack, &node);
	while (st_is_empty(stack) != 0) {
		int nod_top = st_peek(stack);
		int *neigh = mg->matrix[nod_top];

		int find = 0;
		for (int i = 0; i < mg->nodes; i++) {
			if (visited[neigh[i]] == 0) {
				contor++;
				t_desc[neigh[i]] = contor;
				visited[neigh[i]] = 1;
				printf("%d ", neigh[i]);
				st_push(stack, neigh[i]);
				find = 1;
				break;
			}
		}
		if (find == 0) {
			contor++;
			t_tin[nod_top] = contor;
			visited[nod_top] = 1;
			st_pop(stack);
		}
	}
}

void
bfs_list_graph(list_graph_t* lg, int node, int* color, int* parent)
{
	queue_t *Q = q_create(sizeof(int), lg->nodes);

	q_enqueue(Q, &node);
	while (q_is_empty(Q) != 0) {
		linked_list_t *list = lg->neighbors[node];

		ll_node_t *temp = list->head;
		while (temp != NULL) {
			if (color[*(int*)temp->data] == 0) {
				color[*(int*)temp->data] = 1;
				parent[*(int*)temp->data] = node;
				q_enqueue(Q, (int*)temp->data);
			}
			temp = temp->next;
		}
		color[node] = 1;
		printf("%d ", node);
	}
}

void
bfs_matrix_graph(matrix_graph_t* mg, int node, int* color, int* parent)
{
	queue_t *Q = q_create(sizeof(int), mg->nodes);

	q_enqueue(Q, &node);
	while (q_is_empty(Q) != 0) {
		int *neigh = mg->matrix[node];

		for (int i = 0; i < mg->nodes; i++) {
			if (color[neigh[i]] == 0) {
				color[neigh[i]] = 1;
				parent[neigh[i]] = node;
				q_enqueue(Q, neigh[i]);
			}
		}
		color[node] = 1;
		printf("%d ", node);
	}
}

void
floyd_warshall(matrix_graph_t* mg)
{
	int i, j, k;
	for (int i = 0; i < mg->nodes; i++) {
		for(int j = 0; j < mg->nodes; j++) {
			mg->matrix[i][j] = mg;
		}
	}

	for (int k = 0; k < mg->nodes; i++) {
		for (int i = 0; i < mg->nodes; i++) {
			for (int j = 0; j < mg->nodes; i++) {
				if (mg->matrix[i][k] + mg->matrix[k][j] < mg->matrix[i][j])
					mg->matrix[i][j] = mg->matrix[i][k] + mg->matrix[k][j];
			}
		}
	}
	print_matrix_graph(mg);
}

int
main()
{
	int nodes, edges;
	int x[MAX_NODES], y[MAX_NODES];
	int visited[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
	list_graph_t* lg = lg_create(MAX_NODES);
	matrix_graph_t* mg = mg_create(MAX_NODES);

	int numbers[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	printf("-------------------------------- Test ListGraph "
		"--------------------------------\n");
	/* Test add_edge_list_graph has_edge_list_graph */

	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[2], numbers[4]));

	/* Test remove_edge_list_graph */
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[0], numbers[4]);

	linked_list_t* l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("Output asteptat: 1 2 3 4\n");

	printf("-------------------------------- Test MatrixGraph "
		"--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		mg_has_edge(mg, numbers[0], numbers[1]));

	lg_free(lg);
	mg_free(mg);
	return 0;
}
