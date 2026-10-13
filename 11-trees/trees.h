#pragma once

typedef struct node {
    int data;
    struct node *left, *right;
} node;

node *createNode(int data);

void printLeaves(node *root);
void printNonLeaves(node *root);
void printLevels(node *root, int level);

void inorder(node *root);
void preorder(node *root);
void postorder(node *root);
