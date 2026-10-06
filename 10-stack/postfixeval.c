// Implement evaluation of postfix expression.

#include <stdio.h>
#include <ctype.h>
#include "stackarray.h"

int evaluatePostfix(const char *expression) {
    int stack[MAX_SIZE];
    int top = -1;

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        if (isspace(ch)) {
            continue;
        }

        if (isdigit(ch)) {
            push(stack, &top, ch - '0');
        } else {
            int b = pop(stack, &top);
            int a = pop(stack, &top);

            switch (ch) {
                case '+': push(stack, &top, a + b); break;
                case '-': push(stack, &top, a - b); break;
                case '*': push(stack, &top, a * b); break;
                case '/': 
                    if (b == 0) {
                        printf("Error: Division by zero\n");
                        return -1;
                    }
                    push(stack, &top, a / b); 
                    break;
                default:
                    printf("Error: Invalid operator '%c'\n", ch);
                    return -1;
            }
        }
    }

    return pop(stack, &top);
}

int main() {
    char expression[MAX_SIZE];
    printf("Enter postfix expression (e.g., 231*+9-): ");
    scanf("%s", expression);

    printf("Result: %d\n", evaluatePostfix(expression));
    return 0;
}
