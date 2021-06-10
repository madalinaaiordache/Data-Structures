/**
 * SD, 2020
 * 
 * Lab #9, BST & Heap
 * 
 * Task #2 - Test Heap Implementation
 */

#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

char to_lower(char c)
{
	if ('A' <= c && c <= 'Z')
		return c + 0x20;
	return c;
}

int heap_cmp_str_lexicographically(const char *key1, const char *key2)
{
	int rc, i, len;

	len = strlen(key1) < strlen(key2) ? strlen(key1) : strlen(key2);
	for (i = 0; i < len; ++i) {
		rc = to_lower(key1[i]) - to_lower(key2[i]);

		if (rc == 0)
			continue;
		return rc;
	}

	rc = to_lower(key1[i]) - to_lower(key2[i]);
	return rc;
}

int heap_cmp_teams(const team_t *key1, const team_t *key2)
{
    int score_diff = key2->score - key1->score;

    if (score_diff != 0)
        return score_diff;

    return heap_cmp_str_lexicographically(key1->name, key2->name);
}

int main(void)
{
    heap_t *heap;
    team_t team, tmp_team;
    int N, task;

    heap = heap_create(heap_cmp_teams);
    team.name = malloc(BUFSIZ * sizeof(char));
    if (team.name == NULL)
        perror("team.name malloc");

    scanf("%d\n", &N);

    while (N--) {
        scanf("%d", &task);
    
        switch (task) {
        case 1:
            memset(team.name, 0, BUFSIZ);
            scanf("%s %d", team.name, &team.score);
            heap_insert(heap, &team);
            break;
        case 2:
            if (!heap_empty(heap)) {
                tmp_team = heap_top(heap);
                printf("%s %d\n", tmp_team.name, tmp_team.score);
            }
            break;
        case 3:
            if (!heap_empty(heap)) {
                heap_pop(heap);
            }
            break;
        default:
            perror("Invalid task!");
        }
    }
    //team_t * tmp; 
    // for (int i = 0; i < heap->size; i++){
    //     for (int j = 0 ; j < heap->size; j++)
    //     if (heap_cmp_teams(heap->arr[i], heap->arr[j])){
    //         tmp = heap->arr[i];
    //         heap->arr[i] = heap->arr[j];
    //         heap->arr[j]= tmp;
    //     }
    // }
    //asa merge pentru ca am ordonat in insert
    //vectorul cu elementele
    for (int i = 0; i < heap->size; i++){
        printf("%s %d\n", heap->arr[i]->name, heap->arr[i]->score);
    }
    //daca fac asa nu imi afiseaza calumea si nu stiu daca 
    //este de la heap_pop sau altcv
    // team_t  tmp; 
    // while(heap->size){
    //     tmp = heap_top(heap);
    //      printf("%s %d\n", tmp.name, tmp.score);
    //      heap_pop(heap);
    // }

    free(team.name);
    heap_free(heap);

    return 0;
}
