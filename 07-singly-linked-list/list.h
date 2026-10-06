#pragma once

struct Node {
    int data;
    struct Node *next;
};

extern struct Node *head;

void insertEnd(int val);
void insertAfter(int key, int val);
void display(void);
void deleteNode(struct Node *prev, struct Node *n);
void deleteLargest(void);
void deleteSmallest(void);
void deleteFirst(void);
void deleteLast(void);
