#pragma once

typedef struct Node {
    int value;
    struct Node *next;
} Node;

extern Node *head;

void insert_head(int v);
void insert_tail(int v);
void delete_head(void);
void free_list(void);
