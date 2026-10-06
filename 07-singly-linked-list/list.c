#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct Node *head = NULL;

void insertEnd(int val)
{
    struct Node *n = malloc(sizeof(struct Node));
    n->data = val;
    n->next = NULL;

    if (head == NULL) {
        head = n;
        return;
    }

    struct Node *t = head;
    while (t->next) t = t->next;
    t->next = n;
}

void insertAfter(int key, int val)
{
    struct Node *t = head;
    while (t && t->data != key) t = t->next;
    if (t == NULL) {
        insertEnd(val);
        return;
    }

    struct Node *n = malloc(sizeof(struct Node));
    n->data = val;
    n->next = t->next;
    t->next = n;
}

void display(void)
{
    struct Node *t = head;
    while (t) {
        printf("%d -> ", t->data);
        t = t->next;
    }
    printf("NULL\n");
}

void deleteNode(struct Node *prev, struct Node *n)
{
    if (prev == NULL) head = n->next;
    else prev->next = n->next;
    free(n);
}

void deleteLargest(void)
{
    struct Node *t = head, *prev = NULL, *max = head, *maxPrev = NULL;
    while (t) {
        if (t->data > max->data) {
            max = t;
            maxPrev = prev;
        }
        prev = t;
        t = t->next;
    }
    if (max) deleteNode(maxPrev, max);
}

void deleteSmallest(void)
{
    struct Node *t = head, *prev = NULL, *min = head, *minPrev = NULL;
    while (t) {
        if (t->data < min->data) {
            min = t;
            minPrev = prev;
        }
        prev = t;
        t = t->next;
    }
    if (min) deleteNode(minPrev, min);
}

void deleteFirst(void)
{
    if (head) deleteNode(NULL, head);
}

void deleteLast(void)
{
    if (head == NULL)
        return;

    struct Node *t = head, *prev = NULL;
    while (t->next) {
        prev = t;
        t = t->next;
    }
    deleteNode(prev, t);
}

int main(void)
{
    char mis[64];
    int occ[10] = {0};

    printf("Enter MIS No.: ");
    scanf("%s", mis);

    for (int i = 0; mis[i]; i++) {
        int d = mis[i] - '0';
        occ[d]++;
        if (occ[d] == 1)
            insertEnd(d);
        else if (occ[d] == 2)
            insertEnd(d * 10);
        else if (occ[d] == 3)
            insertAfter(d, d * 100);
    }

    printf("\nOriginal list:\n");
    display();

    printf("\nAfter deleting largest:\n");
    deleteLargest();
    display();

    printf("\nAfter deleting smallest:\n");
    deleteSmallest();
    display();

    printf("\nAfter deleting first:\n");
    deleteFirst();
    display();

    printf("\nAfter deleting last:\n");
    deleteLast();
    display();

    return 0;
}
