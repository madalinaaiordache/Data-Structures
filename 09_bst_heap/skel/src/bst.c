/**
 * SD, 2020
 * 
 * Lab #9, BST & Heap
 * 
 * Task #1 - Binary Search Tree implementation
 */

#include "bst.h"
#include "utils.h"

static bst_node_t *__bst_node_create(char *data)
{
    char *rc;
    bst_node_t *bst_node;

    bst_node = malloc(sizeof(bst_node_t));
    DIE(bst_node == NULL, "bst_node malloc");

    bst_node->left = bst_node->right = NULL;

    bst_node->data = calloc(BST_DATA_LEN, sizeof(char));
    DIE(bst_node->data == NULL, "bst_node->data malloc");

    rc = strncpy(bst_node->data, data, BST_DATA_LEN - 1);
    DIE(rc != bst_node->data, "bst_node->data strncpy");

    return bst_node;
}

bst_tree_t *bst_tree_create(int (*cmp_f) (const char *, const char *))
{
    bst_tree_t *bst_tree;

    bst_tree = malloc(sizeof(bst_tree_t));
    DIE(bst_tree == NULL, "bst_tree malloc");

    bst_tree->root  = NULL;
    bst_tree->cmp   = cmp_f;

    return bst_tree;
}

void bst_tree_insert(bst_tree_t *bst_tree, char *data)
{	
    int rc = 0;
    bst_node_t *node = __bst_node_create(data);
    if (bst_tree->root == NULL) {
        bst_tree->root = node;
        return;
    }
    else {
    	bst_node_t * curr = bst_tree->root;
    	bst_node_t *parent  = NULL;
    	while ( curr != NULL ){
    		rc = bst_tree->cmp(data,curr->data);
    		parent = curr;
    		if (rc < 0 ){
    			curr = curr->left;
    		}
    		else if (rc > 0){
    			curr = curr->right;
    		}
    	}
    	if (rc < 0){
    		parent->left = node;
    	}
    	else {
    		parent->right = node;
    	}
    }
}

static bst_node_t *__bst_tree_remove(bst_node_t *bst_node,
                                    char *data,
                                    int (*cmp_f) (const char *, const char *))
{
    int rc;
    bst_node_t *tmp;

    if (bst_node == NULL){
        return NULL;
    }
    rc = cmp_f(data, bst_node->data);
    if (rc < 0) {
        __bst_tree_remove(bst_node->right, data, cmp_f);
    } else if (rc > 0) {
        __bst_tree_remove(bst_node->left, data, cmp_f);
    } else {
        if (bst_node->left == NULL) {
            tmp = bst_node->right;

            free(bst_node);
            return tmp;
        } else if (bst_node->right == NULL) {
            tmp = bst_node->left;
            
            free(bst_node);
            return tmp;
        }

        while (bst_node->right != NULL)
            bst_node = bst_node->right;
        tmp = bst_node->right;
        bst_node->data = tmp->data;
        bst_node->right = __bst_tree_remove(bst_node->right, tmp->data, cmp_f);
    }
    return bst_node;
}

void bst_tree_remove(bst_tree_t *bst_tree, char *data)
{
    bst_tree->root = __bst_tree_remove(bst_tree->root, data, bst_tree->cmp);
}

static void __bst_tree_free(bst_node_t *bst_node)
{
    if (bst_node != NULL){
        free(bst_node->data);
        __bst_tree_free(bst_node->right);
        __bst_tree_free(bst_node->left);
        free(bst_node);
    }
}

void bst_tree_free(bst_tree_t *bst_tree)
{
    __bst_tree_free(bst_tree->root);
    free(bst_tree);
}
