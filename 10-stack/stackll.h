#pragma once

#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

void initStack(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
bool isEmpty(Stack *stack);
bool isFull(void);
int peek(Stack *stack);
