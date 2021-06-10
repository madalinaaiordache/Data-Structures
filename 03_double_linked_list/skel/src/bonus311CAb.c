// IORDACHE MADALINA GABRIELA 313CA - problema bonus 311CAb
// Program to reverse a dll
#include <stdio.h>
#include <stdlib.h>
 
struct Node
{
  int data;
  struct Node *next, *prev;
};
 
// Function to reverse dll
void reverse(struct Node **headRef)
{
     struct Node *temp = NULL; 
     struct Node *current = *headRef;
      
     // swap next and prev for all nodes
     while (current !=  NULL)
     {
       temp = current->prev;
       current->prev = current->next;
       current->next = temp;             
       current = current->prev;
     }     
      
     if(temp != NULL )
        *headRef = temp->prev;
}    
 
// Function to insert a node at the beg
void add(struct Node** headRef, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

    new_node->data  = new_data;
    new_node->prev = NULL;
    new_node->next = (*headRef);   
 
    // change prev of head node to new node
    if((*headRef) !=  NULL)
      (*headRef)->prev = new_node ;   
    (*headRef) = new_node;
}
 
 // Function to print dll
void print(struct Node *node)
{
  while(node!=NULL)
  {
   printf("%d ", node->data);
   node = node->next;
  }
}
 
int main()
{
  // empty list
  struct Node* head = NULL;
  
  // create a sorted linked list 1->2->3
  add(&head, 3);
  add(&head, 2);
  add(&head, 1);
  
  printf("First list:\n");
  print(head);
  printf("\n");
  
  // Reverse list
  reverse(&head);
  
  printf("Reversed list:\n");
  print(head);          
  printf("\n");

  return 0;
}