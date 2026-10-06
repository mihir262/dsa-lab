#include <stdio.h>
#include <stdlib.h>
#include "stackll.h"

void initStack(Stack *stack) {
    stack->top = NULL;
}

void push(Stack *stack, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack) {
    if (stack->top == NULL) {
        printf("Stack underflow\n");
        return -1;
    }
    Node *temp = stack->top;
    int val = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return val;
}

bool isEmpty(Stack *stack) {
    return stack->top == NULL;
}

bool isFull(void) {
    return false;
}

int peek(Stack *stack) {
    if (stack->top == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack->top->data;
}
