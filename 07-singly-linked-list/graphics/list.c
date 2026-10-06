#include <stdlib.h>
#include "list.h"

Node *head;

void insert_head(int v)
{
    Node *n = malloc(sizeof(Node));
    n->value = v;
    n->next = head;
    head = n;
}

void insert_tail(int v)
{
    Node *n = malloc(sizeof(Node));
    n->value = v;
    n->next = NULL;
    if (!head) { head = n; return; }
    Node *p = head;
    while (p->next) p = p->next;
    p->next = n;
}

void delete_head(void)
{
    if (!head) return;
    Node *n = head;
    head = head->next;
    free(n);
}

void free_list(void)
{
    while (head) delete_head();
}
