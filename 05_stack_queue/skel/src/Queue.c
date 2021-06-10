#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "utils.h"

queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t *q = calloc(1, sizeof(queue_t));
	DIE(!q, "calloc queue");
	q->buff = calloc(max_size, sizeof(void*));
	DIE(!q->buff, "calloc buff");

	for (int i = 0; i < max_size; i++) {
		q->buff[i] = calloc(1, sizeof(data_size));
	}
	q->max_size = max_size;
	q->read_idx = 0;
	q->write_idx = 0;
	q->data_size = data_size;
	q->size = 0;
	return q;
}

unsigned int
q_get_size(queue_t *q)
{
	return q->size;
}

/*
 * Intoarce 1 daca stiva este goala si 0 in caz contrar.
 */
unsigned int
q_is_empty(queue_t *q)
{
	if (q->size == 0) {
		return 1;
	}
	return 0; 	
}

void *
q_front(queue_t *q)
{
	return q->buff[q->read_idx];
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_dequeue(queue_t *q)
{
	if( q->size == 0) {
		return false;
	} else {
		q->read_idx++;
		q->read_idx %= q->max_size;
		q->size--;
		//free(q->buff->read_idx);
		return true;
	}
	
}

/* Functia intoarce true daca operatia s-a efectuat si false in caz contrar */
bool
q_enqueue(queue_t *q, void *new_data)
{
	if (q->size == q->max_size) {
		return false;
	} else {
		memcpy(q->buff[q->write_idx], new_data, sizeof(q->data_size));
		q->write_idx++;
		q->write_idx %= q->max_size;
		q->size++;
		return true;
	}
	
}

void
q_clear(queue_t *q)
{
	while (!q_is_empty) {
		for (int i = 0; i < q->max_size; i++) {
			q_dequeue((q->buff[i]));
			free(q->buff[i]);
		}
	}
}

void
q_free(queue_t *q)
{
	q_clear(q);
	for (int i = 0; i < q->max_size; i++)
		free(q->buff[i]);
	free(q->buff);
	free(q);
}
