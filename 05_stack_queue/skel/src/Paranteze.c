#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Stack.c"

// Return 1 if expression has balanced Brackets
int balanced_brackets(char brackets[])
{
    stack_t *st = st_create(sizeof(char));
    // Traverse the given expression to check matching brackets
    int i = 0;
    while (brackets[i]) {
        // If the brackets[i] is a starting bracket then push it
        if (brackets[i] == '(')
            st_push(st, &brackets[i]);
        else if (brackets[i] == '{')
            st_push(st, &brackets[i]);
        else if (brackets[i] == '[')
            st_push(st, &brackets[i]);
        else {
            if (st_is_empty(st) == 1) {
                st_free(st);
                return 0;
            }

            // Pop the top element from stack, if it is not a pair bracket of 
            // character then there is a mismatch
            if (*(char*)st_peek(st) == '(' && brackets[i] == ')')
                st_pop(st);
            else if (*(char*)st_peek(st) == '{' && brackets[i] == '}')
                st_pop(st);
            else if (*(char*)st_peek(st) == '[' && brackets[i] == ']')
                st_pop(st);
            else {
                st_free(st);
                return 0;
            }
        }
        i++;
    }

    // If there is something left in expression then there
    // is a starting bracket without a closing bracket
    if(st_is_empty(st) == 0) {
        st_free(st);
        return 0;
    }

    st_free(st);
    return 1;
}

 int main()
 {
    char brackets[100] = "([{)]}";  // not balanced
    // char brackets[100] = "{[()]}";  // balanced

    // Function call
    if (balanced_brackets(brackets) == 1)
        printf("Balanced\n");
    else
        printf("Not Balanced\n");
    return 0;
 }
