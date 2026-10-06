// Implement conversion of infix expression to postfix expression.

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stackarray.h"

// Operator precedence: higher number means higher precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

void infixToPostfix(const char *infix, char *postfix) {
    int stack[MAX_SIZE];
    int top = -1;
    int k = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isspace(ch)) {
            continue;
        }

        if (isalnum(ch)) {
            postfix[k++] = ch;
        } else if (ch == '(') {
            push(stack, &top, ch);
        } else if (ch == ')') {
            while (!isEmpty(top) && peek(stack, top) != '(') {
                postfix[k++] = (char)pop(stack, &top);
            }
            pop(stack, &top); // Discard '('
        } else if (precedence(ch) > 0) {
            while (!isEmpty(top) && precedence(peek(stack, top)) >= precedence(ch)) {
                if (ch == '^' && peek(stack, top) == '^') break; // Right-associative
                postfix[k++] = (char)pop(stack, &top);
            }
            push(stack, &top, ch);
        }
    }

    while (!isEmpty(top)) {
        postfix[k++] = (char)pop(stack, &top);
    }
    postfix[k] = '\0';
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter infix expression (e.g., (A+B)*(C-D)): ");
    if (fgets(infix, sizeof(infix), stdin)) {
        infix[strcspn(infix, "\n")] = '\0';
    }

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
