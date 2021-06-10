#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "313caalab2.h"
#include "utils.h"

linkedlist*
linkedlist_create()
{
    linkedlist *list = (linkedlist *)malloc(sizeof(linkedlist));

    if (list == NULL) {
        printf("Nu s-a putut aloca memorie pentru lista\n");
        exit(-1);
    }

    list->head = NULL;
    list->size = 0;

    return list;
}

void linkedlist_add(linkedlist* list, int n, int new_data)
{
    if (list == NULL) {
        printf("Nu s-a creat lista\n");
        exit(-1);
    }
    struct node *curr = list->head;
    struct node *temp = malloc(sizeof(node));
    temp->data = new_data;

    if (n < 0) {
        printf("pozitie invalida\n");
        return;
    } else if (n >= list->size) {
        if (curr == NULL) {
            list->head = temp;
            list->head->next = temp->next;
        } else {
            while(curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = temp;
        }
    } 
    list->size++;
}

void split_list(linkedlist *original_list, 
                linkedlist *even_list, 
                linkedlist *odd_list)
{
    if(original_list->head == NULL) {
        return;
    }
    int n = 2;

    struct node* newNode = original_list->head;
    while (newNode != NULL) {
        
        if (n % 2 == 0) {
            linkedlist_add(odd_list, odd_list->size, newNode->data);
        } else {
            linkedlist_add(even_list, even_list->size, newNode->data);
        }
        newNode = newNode->next;
        n++;
    }
}

void linkedlistl_free(linkedlist** fr_list)
{
    struct node *temp = (*fr_list)->head;

    while ((*fr_list)->head != NULL) {
        temp = (*fr_list)->head;
        (*fr_list)->head = (*fr_list)->head->next;
        free(temp);
        
    }

    free(*fr_list);
}

void linkedlist_print(linkedlist *list)
{
    struct node *temp = list->head;
    printf("List: ");
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }	
    printf("\n");
}