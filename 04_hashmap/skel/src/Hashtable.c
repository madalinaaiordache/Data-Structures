// Iordache Madalina Gabriela 313CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#include "Hashtable.h"

#define MAX_BUCKET_SIZE 64

/*
 * Functii de comparare a cheilor:
 */
int
compare_function_ints(void *a, void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b) {
		return 0;
	} else if (int_a < int_b) {
		return -1;
	} else {
		return 1;
	}
}

int
compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

/*
 * Functii de hashing:
 */
unsigned int
hash_function_int(void *a)
{
	/*
	 * Credits: https://stackoverflow.com/a/12996028/7883884
	 */
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

unsigned int
hash_function_string(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char*) a;
	unsigned long hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

/*
 * Functie apelata dupa alocarea unui hashtable pentru a-l initializa.
 * Trebuie alocate si initializate si listele inlantuite.
 */
hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*))
{
	hashtable_t *hasht = malloc(sizeof(hashtable_t));

	hasht->hmax = hmax;
	hasht->size = 0;
	hasht->hash_function = hash_function;
	hasht->compare_function = compare_function;

	hasht->buckets = malloc((hasht->hmax)*sizeof(linked_list_t*));

	for (unsigned int i = 0; i < hasht->hmax; i++)
		hasht->buckets[i] = ll_create(sizeof(struct info));

	return hasht;
}

/*
 * Atentie! Desi cheia este trimisa ca un void pointer (deoarece nu se impune tipul ei), in momentul in care
 * se creeaza o noua intrare in hashtable (in cazul in care cheia nu se gaseste deja in ht), trebuie creata o copie
 * a valorii la care pointeaza key si adresa acestei copii trebuie salvata in structura info asociata intrarii din ht.
 * Pentru a sti cati octeti trebuie alocati si copiati, folositi parametrul key_size_bytes.
 *
 * Motivatie:
 * Este nevoie sa copiem valoarea la care pointeaza key deoarece dupa un apel put(ht, key_actual, value_actual),
 * valoarea la care pointeaza key_actual poate fi alterata (de ex: *key_actual++). Daca am folosi direct adresa
 * pointerului key_actual, practic s-ar modifica din afara hashtable-ului cheia unei intrari din hashtable.
 * Nu ne dorim acest lucru, fiindca exista riscul sa ajungem in situatia in care nu mai stim la ce cheie este
 * inregistrata o anumita valoare.
 */
void
ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
	int i;
	i = ht->hash_function(key) % ht->hmax; 
	ll_node_t *temp = ht->buckets[i]->head;

	while (temp) {
		if (ht->compare_function(((struct info *)(temp->data))->key, key) == 0) {
			memcpy(((struct info *)(temp->data))->value, value, value_size);
			return;
		}  
	temp = temp->next;
	}

	struct info pair;

	pair.key = malloc(key_size); 
	pair.value = malloc(value_size);

	memcpy(pair.key, key, key_size);
	memcpy(pair.value, value, value_size);

	ll_add_nth_node(ht->buckets[i], ht->buckets[i]->size, &pair);
	
	ht->size++;

}

void *
ht_get(hashtable_t *ht, void *key)
{
	int i = ht->hash_function(key) % ht->hmax;

	ll_node_t *temp = ht->buckets[i]->head;

	while (temp) {
		if (ht->compare_function(((struct info *)temp->data)->key, key) == 0)
			return ((struct info *)(temp->data))->value;

		temp = temp->next;
	}

	return NULL;
}

/*
 * Functie care intoarce:
 * 1, daca pentru cheia key a fost asociata anterior o valoare in hashtable folosind functia put
 * 0, altfel.
 */
int
ht_has_key(hashtable_t *ht, void *key)
{
	int i = ht->hash_function(key) % ht->hmax;

	ll_node_t *temp = ht->buckets[i]->head;

	while (temp) {
		if (ht->compare_function(((struct info *)(temp->data))->key, key) == 0)
			return 1;

		temp = temp->next;
	}
	return 0;
}

/*
 * Procedura care elimina din hashtable intrarea asociata cheii key.
 * Atentie! Trebuie avuta grija la eliberarea intregii memorii folosite pentru o intrare din hashtable (adica memoria
 * pentru copia lui key --vezi observatia de la procedura put--, pentru structura info si pentru structura Node din
 * lista inlantuita).
 */
void
ht_remove_entry(hashtable_t *ht, void *key)
{
	unsigned int i = ht->hash_function(key) % ht->hmax;
	ll_node_t *temp = ht->buckets[i]->head;
	unsigned int count = 0;

	while (temp) {
		
		if (ht->compare_function(((struct info *)(temp->data))->key, key) == 0) {
			
			temp = ll_remove_nth_node(ht->buckets[i], count);

			free(((struct info *)temp->data)->key);
			free(((struct info *)temp->data)->value);
			free(temp->data);
			free(temp);
	
			ht->size--;
			return;
		}
		
		count++;
		temp = temp->next;
	}
}

/*
 * Procedura care elibereaza memoria folosita de toate intrarile din hashtable, dupa care elibereaza si memoria folosita
 * pentru a stoca structura hashtable.
 */
void
ht_free(hashtable_t *ht)
{
	ll_node_t *temp;

	for (unsigned int i = 0; i < ht->hmax; i++) {
			temp = ht->buckets[i]->head;
			while (temp) {
				free(((struct info *)(temp->data))->key);
				free(((struct info *)(temp->data))->value);
				temp = temp->next;
			}
		ll_free(&ht->buckets[i]);
	}
	free(ht->buckets);
	free(ht);
}

unsigned int
ht_get_size(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->size;
}

unsigned int
ht_get_hmax(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->hmax;
}
