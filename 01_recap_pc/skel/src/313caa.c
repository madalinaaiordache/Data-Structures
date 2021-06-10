#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// print matrix using function
void print_matrix(int **matrix, int m, int n) 
{
    for(int i = 0 ; i < m ; i++) {
        for(int j = 0 ; j < n; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {

    int m, n;
    int a, b;
    int number_of_pairs;

    // read number of lines, columns and the number of pairs (a,b)
    scanf("%d %d", &n, &m);
    scanf("%d", &number_of_pairs);

    // dynamically allocate matrix
    int **matrix = (int **)calloc(m, sizeof(int *)); 
    for (int i = 0; i < m; i++) {                      
        matrix[i] = (int *)calloc(n, sizeof(int));
    }
    DIE(matrix == NULL, "calloc failed");

    for (int i = 0; i < number_of_pairs; i++) {
        scanf("%d %d", &a, &b);
        for (int i = 0; i < a; i++) 
            for (int j = 0; j < b;j++)
                matrix[i][j]++;        // increment matrix elements
    }

    // print matrix after applying increment operations
    print_matrix(matrix, m, n);

    // deallocate memory
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}