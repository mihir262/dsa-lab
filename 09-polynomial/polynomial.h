#pragma once

struct Node {
    int coeff;
    int exp;
    struct Node *next;
};

struct Node *createNode(int coeff, int exp);
struct Node *insertTerm(struct Node *head, int coeff, int exp);
struct Node *readPolynomial(void);
void display(struct Node *head);
struct Node *addPolynomial(struct Node *p1, struct Node *p2);
struct Node *subtractPolynomial(struct Node *p1, struct Node *p2);
struct Node *multiplyPolynomial(struct Node *p1, struct Node *p2);
void freePolynomial(struct Node *head);
