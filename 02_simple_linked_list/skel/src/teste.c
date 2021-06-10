
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
}Node;

typedef struct List {
    Node *first;
    Node *last;
}List;

    void addLast(List* list, int value) {
        if (!list->first) {
            list->first = calloc(1, sizeof(Node));
            list->first->value = value;
            list->last = list->first;
        } else {
            Node *temp = calloc(1, sizeof(Node));
            temp->value = value;
            list->last->next = temp;
            list->last = temp;
        }
    }

    void print(List* list) {
        if (!list->first) {
            printf("List is empty\n");
            return;
        }
        Node *temp = list->first;
        while (temp) {
            printf("%d ", temp->value);
            temp = temp->next;
        }
        printf("\n");
    }

List* merge(List *l1, List *l2) {

    //TODO
     List* result = NULL;

    if (l1 == NULL)
        return(l2);
    else if (l2 == NULL)
        return(l1);

    // Pick a or b and recur
    if (l1->value <= l2->value) {
        result = l1;
        result->next = SortedMerge(l1->next, l2);
    }
    else {
        result = l2;
        result->next = SortedMerge(l1, l2->next);
    }
    return(result);
    }

}

int main() {
    List *l1, *l2;
    int m, n;
    int temp;
    
    l1 = calloc(1, sizeof(List));
    l2 = calloc(1, sizeof(List));
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        addLast(l1, temp);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &temp);
        addLast(l2, temp);
    }

    print(merge(l1, l2));

    return 0;
}
