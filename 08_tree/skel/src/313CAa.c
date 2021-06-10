#include <stdlib.h>
#include <stdio.h>

#include "binary_tree.h"

void read_tree(b_tree_t *b_tree)
{
    int i, N, data;
    scanf("%d\n", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d ", &data);
        b_tree_insert(b_tree, &data);
    }
}

void nivel(b_node_t *root, int niv) {
    if(root == NULL) 
        return; 
    if (niv == 0) {
        printf ("%d ", *(int *)root->data);
        return; 
    } 
    else { 
        nivel (root->left, niv - 1); 
        nivel (root->right, niv - 1); 
    }
}

int main(void)
{
    b_tree_t *binary_tree;
    binary_tree = b_tree_create(sizeof(int));
    read_tree(binary_tree);
    int lev;
    scanf("%d ", &lev);

    nivel(binary_tree->root, lev);
}