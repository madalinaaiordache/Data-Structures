#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"

/*
 * Functie care trebuie apelata pentru alocarea si initializarea unei liste.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
doubly_linked_list_t*
dll_create(unsigned int data_size)
{
    doubly_linked_list_t *list = malloc(sizeof(doubly_linked_list_t));
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
 * Functia intoarce un pointer la nodul de pe pozitia n din lista.
 * Pozitiile din lista sunt indexate incepand cu 0 (i.e. primul nod din lista se
 * afla pe pozitia n=0). Daca n >= nr_noduri, atunci se intoarce nodul de pe
 * pozitia rezultata daca am "cicla" (posibil de mai multe ori) pe lista si am
 * trece de la ultimul nod, inapoi la primul si am continua de acolo. Cum putem
 * afla pozitia dorita fara sa simulam intreaga parcurgere? Daca n < 0, eroare.
 */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    struct dll_node_t *curr = list->head;
    int i = 0, m = n;

    if (m < 0) {
        printf("pozitie invalida\n");
        exit(-1);
    } else if (n >= list->size) {

        int aux = n % list->size;
        while (i != aux) {
            curr = curr->next;
            i++;
        }
    } else {
        while (i != m) {
            curr = curr->next;
            i++;
        }

    }
    return curr;
}

/*
 * Pe baza datelor trimise prin pointerul new_data, se creeaza un nou nod care e
 * adaugat pe pozitia n a listei reprezentata de pointerul list. Pozitiile din
 * lista sunt indexate incepand cu 0 (i.e. primul nod din lista se afla pe
 * pozitia n=0). Cand indexam pozitiile nu "ciclam" pe lista circulara ca la
 * get, ci consideram nodurile in ordinea de la head la ultimul (adica acel nod
 * care pointeaza la head ca nod urmator in lista). Daca n >= nr_noduri, atunci
 * adaugam nodul nou la finalul listei. Daca n < 0, eroare.
 */
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
    if (list == NULL) {
        printf("Nu s-a creat lista\n");
        exit(-1);
    }
    struct dll_node_t *curr = list->head;
    struct dll_node_t *temp = malloc(sizeof(dll_node_t));
    DIE(temp == NULL, "Nu s-a putut aloca memorie");
    temp->data = malloc(list->data_size);
    if(list->data_size == sizeof(int)) {
        memcpy(&temp->data, data, list->data_size);
    } else {
        memcpy(temp->data, data, list->data_size);
    }
    temp->next = NULL;

    int m = n;
    if (m < 0) {
        printf("pozitie invalida\n");
        return;
    } else if (n >= list->size) {
        //inserez element la inceput cand lista e goala
        if (list->head == 0) {

            list->head = temp;
            list->tail = temp;
            temp->prev = list->tail;
            temp->next = list->head;

        } else {

            //inserez element la sfarsit
            temp->prev = list->tail;
            list->tail->next = temp;
            temp->next = list->head;
            list->head->prev = temp;
            list->tail = temp;

        }
    } else if (n == 0) {

        //inserez element la inceput
        temp->next = list->head;
        list->head->prev = temp;
        temp->prev = list->tail;
        list->tail->next = temp;
        list->head = temp;
    } else {
        
        int i = 0;
        //inserez element pe pozitie arbitrara
        while (i != m-1) {
            curr = curr->next;
            i++;
        }
        temp->prev = curr;
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;
    }
    list->size++;
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca
 * parametru. Pozitiile din lista se indexeaza de la 0 (i.e. primul nod din
 * lista se afla pe pozitia n=0). Functia intoarce un pointer spre acest nod
 * proaspat eliminat din lista. Daca n >= nr_noduri - 1, se elimina nodul de la
 * finalul listei. Daca n < 0, eroare. Este responsabilitatea apelantului sa
 * elibereze memoria acestui nod.
 */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
    struct dll_node_t *temp = list->head;
    
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
        list->head = list->head->next;
        list->head->prev = list->tail;
        list->tail->next = list->head;
        list->size--;
        return copy;
    } else if (n >= list->size - 1) {
        //sterg element de la final
        struct dll_node_t *aux = list->tail;

        list->tail = list->tail->prev;
        list->tail->next = list->head;
        list->head->prev = list->tail;
        list->size--;
        return aux;
    } else {
        //sterg element arbitar din lista
        int i = 0;
        while (i < m) {
            temp = temp->next;
            i++;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        list->size--;
        return temp;
    }
}

/*
 * Functia intoarce numarul de noduri din lista al carei pointer este trimis ca
 * parametru.
 */
unsigned int
dll_get_size(doubly_linked_list_t* list)
{
    return list->size;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la
 * sfarsit, elibereaza memoria folosita de structura lista.
 */
void
dll_free(doubly_linked_list_t** pp_list)
{
    dll_node_t *temp = (*pp_list)->head;

    while (temp->next != (*pp_list)->head) {
        temp = (*pp_list)->head;
        (*pp_list)->head = (*pp_list)->head->next;
        free(temp);
    }
    free(*pp_list);
}


/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza toate valorile int stocate in nodurile
 * din lista separate printr-un spatiu, incepand de la primul nod din lista.
 */
void
dll_print_int_list(doubly_linked_list_t* list)
{
    struct dll_node_t *temp = list->head;
    while(temp != list->tail) {
        printf("%d ", (int*)temp->data);
        temp = temp->next;
    }	
    printf("%d ", (int*)temp->data);
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza string-uri. Functia afiseaza toate string-urile stocate in
 * nodurile din lista separate printr-un spatiu, incepand de la primul nod din
 * lista.
 */
void
dll_print_string_list(doubly_linked_list_t* list)
{
    struct dll_node_t *temp = list->head;

    while(temp != list->tail) {
        printf("%s ", (char *)temp->data);
        temp = temp->next;
    }
    printf("%s ", (char *)temp->data);
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la stanga in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_left_circular(dll_node_t* start)
{
    if ((start = 0)) {
        return;
    }
    dll_node_t *temp = start;
    printf("%d ", *(int *)temp->data);
    temp = temp->prev;
    while (temp != start) {
        printf("%d ", *(int *)temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

/*
 * Atentie! Aceasta functie poate fi apelata doar pe liste ale caror noduri STIM
 * ca stocheaza int-uri. Functia afiseaza o singura data toate valorile int
 * stocate in nodurile din lista, separate printr-un spatiu, incepand de la
 * nodul dat ca parametru si continuand la dreapta in lista dublu inlantuita
 * circulara, pana cand sunt afisate valorile tuturor nodurilor.
 */
void
dll_print_ints_right_circular(dll_node_t* start)
{
    if ((start = 0)) {
        return;
    }
    dll_node_t *temp = start;
    printf("%d ", *(int *)temp->data);
    temp = temp->next;
    while (temp != start) {
        printf("%d ", *(int *)temp->data);
        temp = temp->next;
    }
    printf("\n");
}
