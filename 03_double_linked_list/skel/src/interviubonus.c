// IORDACHE MADALINA GABRIELA 313CA - problema bonus Interviu(1)
// Implementați o funcție de ștergere a duplicatelor dintr-o listă dublu înlănțuită sortată.
#include <stdio.h>
#include <stdlib.h>
 
struct Node
{
  int data;
  struct Node *next, *prev;
};

//Function to delete a node
void deleteNode(struct Node** head_ref, struct Node* temp)
{
    if (*head_ref == NULL || temp == NULL)
        return;
    // delete head node
    if (*head_ref == temp)
        *head_ref = temp->next;
  
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
  
    if (temp->prev != NULL)
        temp->prev->next = temp->next;
    free(temp);
}
  
// Function to remove duplicates 
void removeDuplicates(struct Node** head_ref)
{
    // empty list
    if ((*head_ref) == NULL)
        return;
  
    struct Node* current = *head_ref;
    struct Node* next;
  
    // traverse the list till the last node
    while (current->next != NULL) {
  
        // Compare current with next
        if (current->data == current->next->data)
            deleteNode(head_ref, current->next);
        else
            current = current->next;
    }
}
  
// Function to insert a node at beg
void add(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  
    new_node->data = new_data;
    new_node->prev = NULL;
    new_node->next = (*head_ref);
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;
    (*head_ref) = new_node;
}
  
// Function to print list
void print(struct Node* temp)
{
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
  
int main()
{
    struct Node* temp = NULL;
  
    // Create list: 1 2 2 3 5 5 9
    add(&temp, 9);
    add(&temp, 5);
    add(&temp, 5);
    add(&temp, 5);
    add(&temp, 3);
    add(&temp, 2);
    add(&temp, 2);
    add(&temp, 1);

    printf("Original list\n");
    print(temp);
    printf("\n");
    // remove duplicate nodes
    removeDuplicates(&temp);
    printf("List after removing duplicates\n");
    print(temp);
    printf("\n");
    return 0;
}
