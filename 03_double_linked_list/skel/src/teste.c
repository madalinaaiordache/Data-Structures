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

int length(List *list) {
        Node *current = list->first;
        int no_values = 0;
        
        while (current->next != NULL) {
            current = current->next;
            no_values++;
        }
        no_values++;
        return no_values;
}
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

    Node *current_first = l1->first;
    Node *current_second = l2->first;
    List* list_merged = calloc(1, sizeof(List));
    int first = 0, second = 0;

    if (l1->first == NULL && l2->first == NULL) {
        exit(-1);

    } else if (l1->first == NULL) {
        list_merged->first = l2->first;

    } else if (l2->first == NULL) {
        list_merged->first = l1->first;

    } else {
        
        while (first < length(l1) && second < length(l2)) {
            if (current_first->value <= current_second->value) {
                addLast(list_merged, current_first->value);
                current_first = current_first->next;
                first++;

            } else {
                addLast(list_merged, current_second->value);
                current_second = current_second->next;
                second++;
            }
        }

        if (first == length(l1) && second < length(l2)) {
            while (second < length(l2)) {
                addLast(list_merged, current_second->value);
                current_second = current_second->next;
                second++;
            }

        } else if (second == length(l2) && first < length(l1)) {
            while (first < length(l1)) {
                addLast(list_merged, current_first->value);
                current_first = current_first->next;
                first++;
            }
        }
    }

    return list_merged;
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