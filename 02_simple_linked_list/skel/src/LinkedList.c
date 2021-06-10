#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

linked_list_t*
ll_create(unsigned int data_size)
{
    linked_list_t *list = malloc(sizeof(linked_list_t));

    if (list == NULL) {
        printf("Nu s-a putut aloca memorie pentru lista\n");
        exit(-1);
    }

    list->head = NULL;
    list->size = 0;
    list->data_size = data_size;

    return list;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Daca n >= nr_noduri, noul nod se adauga la finalul listei. Daca
 * n < 0, eroare.
 */
void ll_add_nth_node(linked_list_t* list, unsigned int n, const void* new_data)
{
    if (list == NULL) {
        printf("Nu s-a creat lista\n");
        exit(-1);
    }
    struct ll_node_t *curr = list->head;
    struct ll_node_t *temp = malloc(sizeof(ll_node_t));
    temp->data = malloc(list->data_size);
    if(list->data_size == sizeof(int)) {
        memcpy(&temp->data, new_data, list->data_size);
    } else {
        memcpy(temp->data, new_data, list->data_size);
    }
    temp->next = NULL;

    int m = n;
    if (m < 0) {
        printf("pozitie invalida\n");
        return;
    } else if (n >= list->size) {
        //inserez element la inceput cand lista e goala
        if (curr == NULL) {
            list->head = temp;
            list->head->next = temp->next;
        } else {
            //inserez element la sfarsit
            while(curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = temp;
        }
    } else if (n == 0) {
        //inserez element la inceput
        temp->next = list->head;
        list->head = temp;
    } else {
        //inserez element arbitrar
        while (n != 1) {
            curr = curr->next;
            n--;
        }
        temp->next = curr->next;
        curr->next = temp;
    }
    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Daca n >= nr_noduri - 1, se elimina nodul de
 * la finalul listei. Daca n < 0, eroare. Functia intoarce un pointer spre acest
 * nod proaspat eliminat din lista. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
ll_node_t*
ll_remove_nth_node(linked_list_t* list, unsigned int n)
{
    struct ll_node_t *temp = list->head;
    struct ll_node_t *prev;
    
    if (list == NULL) {
        exit(-1);
    }
    int m = n;
    if (m < 0) {
        printf("pozitie invalida\n");
        exit(-1);
    }
        
    if (n == 0) {
        //sterg element de la inceput
        struct ll_node_t *copy = list->head;
        list->head = temp->next;
        list->size--;
        return copy;
    } else if (n >= list->size) {
        //sterg element de la final
        for (int i = 0; i < list->size -2; i++) {
            temp = temp->next;
        }
        list->size--;
        struct ll_node_t *aux = temp->next;
        temp->next = NULL;
        return aux;
    } else {
        //sterg element arbitar din lista
        for (int i = 0; i < n; i++) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        list->size--;
        return temp;
    }
    
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
ll_get_size(linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista si actualizeaza la
 * NULL valoarea pointerului la care pointeaza argumentul (argumentul este un
 * pointer la un pointer).
 */
void ll_free(linked_list_t** pp_list)
{
    struct ll_node_t *temp = (*pp_list)->head;

    while ((*pp_list)->head != NULL) {
        (*pp_list)->head = (*pp_list)->head->next;

        free(temp);
        temp = (*pp_list)->head;
    }

    free(*pp_list);
    *pp_list = NULL;
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista inlantuita separate printr-un spatiu.
 */
void
ll_print_int(linked_list_t* list)
{
    struct ll_node_t *temp = list->head;
    while(temp != NULL) {
        printf("%d ", (int*)temp->data);
        temp = temp->next;
    }	
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista inlantuita, separate printr-un spatiu.
 */
void
ll_print_string(linked_list_t* list)
{
    struct ll_node_t *temp = list->head;

    while(temp != NULL) {
        printf("%s ", (char *)temp->data);
        temp = temp->next;
    }	
    printf("\n");
}
