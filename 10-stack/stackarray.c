#include <stdio.h>
#include "stackarray.h"

void push(int stack[], int *top, int value) {
    if (*top >= MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++(*top)] = value;
}

int pop(int stack[], int *top) {
    if (*top < 0) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[(*top)--];
}

bool isFull(int top) {
    return top >= MAX_SIZE - 1;
}

bool isEmpty(int top) {
    return top < 0;
}

int peek(int stack[], int top) {
    if (top < 0) {
        printf("Stack is empty\n");
        return -1;
    }
    return stack[top];
}
