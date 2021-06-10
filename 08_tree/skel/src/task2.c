/**
 * SD, 2020
 * 
 * Lab #8, Binary Tree
 * 
 * Task #2 - <resume_or_paste_the_task_here>
 */
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

void level(b_node_t *root, int lvl) {
    if(root == NULL) 
        return; 
    if (lvl == 0) {
        printf ("%d ", *(int *)root->data);
        return; 
    } else { 
        level (root->left, lvl - 1); 
        level (root->right, lvl - 1); 
    }
}

int main(void)
{
    b_tree_t *binary_tree;

    binary_tree = b_tree_create(sizeof(int));

    read_tree(binary_tree);
    int lev;
    scanf("%d", &lev);

    level(binary_tree->root, lev);
}
