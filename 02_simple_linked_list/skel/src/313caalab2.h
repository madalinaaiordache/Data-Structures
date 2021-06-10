#ifndef __LINKED_LIST_H_
#define __LINKED_LIST_H_

typedef struct node node;
struct node
{
    int data;
    node* next;
};

typedef struct linkedlist linkedlist;
struct linkedlist
{
    node* head;
    int data_size;
    int size;
};

linkedlist* linkedlist_create();

void linkedlist_add(linkedlist* list, int n, int data);

void split_list(linkedlist *original_list, 
                linkedlist *even_list, 
                linkedlist *odd_list);

void linkedlistl_free(linkedlist** fr_list);

void linkedlist_print(linkedlist* list);

#endif /* __LINKED_LIST_H_ */

