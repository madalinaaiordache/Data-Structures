#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include "treap.h"
#define MAX_PRIORITY 1000

// Creeaza structura Treap-ului
Treap_tree* treap_create(int (*cmp)(void*, void*)) {
	srand(time(NULL));
	Treap_tree *tree = malloc(sizeof(Treap_tree));
	tree->compar = cmp;
	if (tree == NULL) {
		return NULL;
	}
	tree->root = NULL;
	return tree;
}
void node_free(Node **node) {

	if (*node == NULL) {
		return;
	}
	node_free(&(*node)->left);
	node_free(&(*node)->right);

	free((*node)->data);
	free(*node);
}

void treap_free(Treap_tree *tree) {
	if (tree->root != NULL) {
		node_free(&tree->root);
	}
	free(tree);
}
/* Creeaza un nod 
 * @param1: Valoarea ce trebuie pusa in nod.
 * @param2: Numarul de octeti pe care scrie valoarea.
 */
Node* node_create(void *value, int data_size) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		return NULL;
	}
	node->data = malloc(data_size);

	// Copiere octet cu octet din value, in nodul curent.
    for (int i = 0; i < data_size; ++i) {
        *(char *)(node->data + i) = *(char *)(value + i);
    }

    // Nodurile frunze au inaltimea 0.
	node->priority = rand() % MAX_PRIORITY;
	node->left = NULL;
	node->right = NULL;

	return node;
}

int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}
// Nodurile NULL au prioritatea -1 pentru a pastra proprietatea de max-heap.
int priority(Node *node) {
	if (node == NULL) {
		return -1;
	}
	return node->priority;
}
/* Rotire dreapta
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *      node  			    lson
 *     /    \			   /    \ 
 *   lson    y    --->    x    node
 *   /  \     		           /   \ 
 *  x   lrson                lrson  y
 */
void rotate_right(Node **node) {
	Node *l = (*node)->left;
	Node *t = (*node)->left->right;

	// executa rotirea
	l->right = (*node);
	(*node)->left = t;
	(*node) = l;
}
/* Rotire stanga
 * Pentru a nu fi nevoie sa mentinem pointer catre nodul parinte,
 * se vor folosi pointeri la noduri
 *
 *     node  			    rson
 *    /    \			   /    \ 
 *   x     rson    --->  node    y
 *         /   \		 /   \
 *       rlson  y       x   rlson
 */	
void rotate_left(Node **node) {
	Node *r = (*node)->right;
	Node *t = (*node)->right->left;

	// executa rotirea
	r->left = (*node);
	(*node)->right = t;
	(*node) = r;

}
/* Inserare in Treap
 * 
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in Treap.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din Treap.
 */
void treap_insert(Node **node, void *value, int data_size, int (*compar)(void*, void*)) {
	
	if ((*node) == NULL){
		// daca nodul este NULL, creez un nou nod si il returnez
		Node *new = node_create(value, data_size);
		(*node) = new;
		return;
	}
	// insereaza element 
	if (compar( (*node)->data, value) > 0){
		treap_insert(&(*node)->left, value, data_size, compar);
		if ((*node)->left!= NULL && ((*node)->left->priority > (*node)->priority)){
			rotate_right(&(*node));
		}
	}
	else {
		treap_insert(&(*node)->right, value, data_size, compar);
		if ((*node)->right!= NULL && ((*node)->right->priority > (*node)->priority)){
			rotate_left(&(*node));
		}
	}
}

/* Stergere din Treap
 *
 * @param1: Nodul radacina al subarborelui din parcurgerea recursiva.
 * @param2: Valoare de adaugat in Treap.
 * @param3: Numarul de octeti pe care se scrie valoarea.
 * @param4: Functia de comparare pentru datele din Treap.
 */
void treap_delete(Node **node, void *value, int data_size, int (*compar)(void*, void*)) {
	// cazul de baza
	if ((*node) == NULL){
		return;
	}
	if (compar(value, (*node)->data) > 0 ){
		treap_delete(&(*node)->right, value, data_size, compar);
	}
	else if (compar(value, (*node)->data) < 0 ){
		treap_delete(&(*node)->left, value, data_size, compar);
	}
	else {
	// nodul de sters nu are copii(este o frunza)
	if ((*node)->left == NULL && (*node)->right == NULL){
		// elibereaza memoria si fa nodul null
		free((*node)->data);
		free(*node);
		*node = NULL;
	}
	// nodul de sters are doi copii
	else if ((*node)->left && (*node)->right){
		if ((*node)->left->priority < (*node)->right->priority){
			// apelez rotate_left pe nodul respectiv
			rotate_left(&(*node));
			treap_delete(&(*node)->left, value, data_size, compar);
		}
		else {
			// apelez rotate_right pe nodul respectiv
			rotate_right(&(*node));
			treap_delete(&(*node)->right, value, data_size, compar);
		}
	}
	else {
		// nodul de sters are un singur copil
		Node* child = (*node)->left ? (*node)->left: (*node)->right;
		Node *temp = *node;
		*node = child;
		free(temp->data);
		free(temp);
	}
}
}

void* get_key(Node *node, void *value, int data_size, int (*compar)(void*, void*)) {
	// TODO: Cautarea unei valori in arbore
	if (node == NULL){
		return NULL;
	}
	if (compar(value, node->data) == 0 ){
		return node->data;
	}
	//cauta valoarea in sub-arborele stang
	if (compar(value, node->data) < 0){
		return get_key(node->left, value, data_size, compar);
	}
	// cauta valoarea in sub-arborele drept
	return get_key(node->right, value, data_size, compar);
}

/* Verifica daca un arbore respecta proprietatile unui treap
 *
 * @param1: Nodul curent in parcurgerea recursiva.
 * @param2: Functia de comparare a datelor din fiecare nod.
 * @return: Daca arborele e Treap, vom returna numarul de noduri al arborelui,
 * 			altfel, vom returna o valoare negativa. 
 */
int check_treap(Node *node, int (*compar)(void*, void*)) {
	if (node == NULL) {
		return 0;
	} else if (node->left == NULL && node->right == NULL) {
		return 1;
	} else if (node->left == NULL) {
		if (priority(node) >= priority(node->right) 
			&& compar(node->data, node->right->data) <= 0) {
			return 1 + check_treap(node->right, compar);
		}
		return INT_MIN;
	} else if (node->right == NULL) {
		if (priority(node) >= priority(node->left) 
			&& compar(node->data, node->left->data) >= 0) {
			return 1 + check_treap(node->left, compar);
		}
		printf("%d %d %d\n", priority(node), priority(node->left), priority(node->right));
		return INT_MIN;
	} else {
		if (priority(node) >= priority(node->left) && priority(node) >= priority(node->right)
			&& compar(node->data, node->left->data) >= 0 
			&& compar(node->data, node->right->data) <= 0) {
			return 1 + check_treap(node->left, compar) + check_treap(node->right, compar);
		}
		printf("%d %d %d\n", priority(node), priority(node->left), priority(node->right));
		return INT_MIN;
	}
}
