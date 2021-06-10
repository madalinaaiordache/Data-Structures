#include <stdlib.h>
#include "Stack.h"
#include "utils.h"
#include "LinkedList.c"

stack_t *
st_create(unsigned int data_size)
{
	
	stack_t *st = calloc(1, sizeof(linked_list_t));
	DIE(!st, "calloc stack");
	st->list = ll_create(data_size);
	st->list->head = NULL;
	return st;
}


unsigned int
st_get_size(stack_t *st)
{
	return st->list->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
st_is_empty(stack_t *st)
{
	if (st->list->head == NULL)
		return 1;
	else
		return 0;
}

void *
st_peek(stack_t *st)
{
	 if (st == NULL || st->list == NULL || !st->list->head) {
        return NULL;
    }
	struct ll_node_t *tmp = st->list->head;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
    return tmp->data;
}

void
st_pop(stack_t *st)
{
	struct ll_node_t *tmp;
	if (st == NULL && st->list == NULL) {
		return;
	}
	tmp = ll_remove_nth_node(st->list, st->list->size - 1);
	free(tmp->data);
	free(tmp);
}

void
st_push(stack_t *st, void *new_data)
{
	ll_add_nth_node(st->list, st->list->size, new_data);
}


void
st_clear(stack_t *st)
{
	int data = st->list->data_size;
	ll_free(&(st->list));
	st->list = ll_create(data);
}

void
st_free(stack_t *st)
{
	ll_free(&(st->list));
	free(st);
}
