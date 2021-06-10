// IORDACHE MADALINA GABRIELA, 313CA
// C program to merge two sorted linked lists
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
 
struct Node
{
    int data;
    struct Node *next, *prev;
};
 
// pull off the front node of the source and put it in dest
struct Node* SortedMerge(struct Node* a, struct Node* b)
{
    struct Node* result = NULL;

    if (a == NULL)
        return(b);
    else if (b == NULL)
        return(a);

    // Pick a or b and recur
    if (a->data <= b->data) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
    }
 
// Function to take the node from the front of the source and 
// move it to the front of the dest
   
void MoveNode(struct Node** destRef, struct Node** sourceRef)
{
    struct Node* newNode = *sourceRef;  // the front source node
    assert(newNode != NULL);
    *sourceRef = newNode->next;
    newNode->next = *destRef;
    *destRef = newNode; // dest point to the new node
}
 
 
// Function to insert a node at the beg of the list
void add(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}
 
// Function to print nodes in a list
void print(struct Node *node)
{
    while (node!=NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}
 
int main()
{
    // list in empty
    struct Node* merged_list = NULL;
    struct Node* a = NULL;
    struct Node* b = NULL;
 
    // create two sorted linked lists
    // created lists a: 1->2->5->9,  b: 2->3->7->8->10
    add(&a, 9);
    add(&a, 5);
    add(&a, 2);
    add(&a, 1);
 
    add(&b, 10);
    add(&b, 8);
    add(&b, 7);
    add(&b, 3);
    add(&b, 2);
 
    merged_list = SortedMerge(a, b);
 
    printf("Merged linkedlist is:\n");
    print(merged_list);
    printf("\n");
 
    return 0;
}