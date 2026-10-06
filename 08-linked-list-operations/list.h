#pragma once

struct Node {
    int data;
    struct Node *next;
};

int countNodes(struct Node *head);
void searchElement(struct Node *head, int key);
void traverseReverse(struct Node *head);
struct Node *deleteBeginning(struct Node *head);
void deleteEnd(struct Node *head);
void deleteNode(struct Node *head, int key);
