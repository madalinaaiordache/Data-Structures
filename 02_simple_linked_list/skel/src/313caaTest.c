#include "313caalab2.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n, k;
    linkedlist *original_list = linkedlist_create();
    linkedlist *odd_list = linkedlist_create();
    linkedlist *even_list = linkedlist_create();
    scanf("%d", &n);
    for(int i =0; i < n; i++) {
        scanf("%d", &k);
        linkedlist_add(original_list, original_list->size, k);
    }
    split_list(original_list, even_list, odd_list);
    //print lists
    linkedlist_print(original_list);

    printf("Odd positions list is :\n");
    linkedlist_print(odd_list);
    
    printf("Even positions list is :\n");
    linkedlist_print(even_list);

    linkedlistl_free(&original_list);
    linkedlistl_free(&odd_list);
    linkedlistl_free(&even_list);
    return 0;
}