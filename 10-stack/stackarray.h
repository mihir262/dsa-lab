#pragma once

#include <stdbool.h>

#define MAX_SIZE 100

void push(int stack[], int *top, int value);
int pop(int stack[], int *top);
bool isFull(int top);
bool isEmpty(int top);
int peek(int stack[], int top);
