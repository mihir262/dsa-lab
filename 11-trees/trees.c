/* Write code to list leaf nodes, non-leaf nodes and level of all nodes in a given binary tree. Also perform traversals on the tree */

#include <stdio.h>
#include <stdlib.h>
#include "trees.h"

node *createNode(int data){
    node *newNode = (node *) malloc(sizeof(node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void printLeaves(node *root){
    if(root == NULL) return;

    if(root->left == NULL && root->right == NULL){
        printf("%d ", root->data);
        return;
    }

    printLeaves(root->left);
    printLeaves(root->right);
}

void printNonLeaves(node *root){
    if(root == NULL) return;

    if(root->left != NULL || root->right != NULL)
        printf("%d ", root->data);

    printNonLeaves(root->left);
    printNonLeaves(root->right);
}

void printLevels(node *root, int level){
    if(root == NULL) return;

    printf("Node %d is at level %d\n", root->data, level);
    printLevels(root->left, level + 1);
    printLevels(root->right, level + 1);
}

void inorder(node *root){
    if(root == NULL) return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(node *root){
    if(root == NULL) return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(node *root){
    if(root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void freeTree(node *root){
    if(root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

node *buildTree(void){
    int data;
    printf("Enter data (-1 for no node): ");
    if(scanf("%d", &data) != 1 || data == -1) return NULL;

    node *root = createNode(data);
    printf("Enter left child of %d\n", data);
    root->left = buildTree();
    printf("Enter right child of %d\n", data);
    root->right = buildTree();
    return root;
}

int main(){
    node *root = NULL;
    int choice;

    while(1){
        printf("\n1. Create tree\n");
        printf("2. List leaf nodes, non-leaf nodes and levels\n");
        printf("3. Inorder traversal\n");
        printf("4. Preorder traversal\n");
        printf("5. Postorder traversal\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        if(scanf("%d", &choice) != 1) break;

        switch(choice){
            case 1:
                freeTree(root);
                root = buildTree();
                break;
            case 2:
                if(root == NULL){
                    printf("Tree is empty. Create a tree first.\n");
                    break;
                }
                printf("Leaf nodes: ");
                printLeaves(root);
                printf("\nNon-leaf nodes: ");
                printNonLeaves(root);
                printf("\n");
                printLevels(root, 0);
                break;
            case 3:
                if(root == NULL){
                    printf("Tree is empty. Create a tree first.\n");
                    break;
                }
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                if(root == NULL){
                    printf("Tree is empty. Create a tree first.\n");
                    break;
                }
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 5:
                if(root == NULL){
                    printf("Tree is empty. Create a tree first.\n");
                    break;
                }
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 6:
                freeTree(root);
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    freeTree(root);
    return 0;
}
