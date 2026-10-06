/*
Implement a Menu-driven Singly Linked List for the following operations
1. Delete the element
a. At the beginning
b. At the end
c. Specific element
2. Count the number of elements in a list
3. Search an element in list
4. Traverse the element in reverse order.
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int countNodes(struct Node *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

void searchElement(struct Node *head, int key) {
    while (head != NULL) {
        if (head->data == key) {
            printf("Found element\n");
            return;
        }
        head = head->next;
    }
    printf("Element not found\n");
}

void traverseReverse(struct Node *head) {
    if (head == NULL) return;
    traverseReverse(head->next);
    printf("%d ", head->data);
}

struct Node* deleteBeginning(struct Node *head) {
    if (head == NULL) return NULL;
    struct Node *temp = head;
    head = head->next;
    free(temp);
    return head;
}

void deleteEnd(struct Node *head) {
    if (head == NULL) return;
    if (head->next == NULL) {
        free(head);
        return;
    }
    struct Node *temp = head;
    while (temp->next->next != NULL) temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}

void deleteNode(struct Node *head, int key) {
    if (head == NULL) return;
    if (head->data == key) {
        printf("Delete beginning for first element\n");
        return;
    }
    struct Node *temp = head;
    while (temp->next != NULL) {
        if (temp->next->data == key) {
            struct Node *del = temp->next;
            temp->next = temp->next->next;
            free(del);
            return;
        }
        temp = temp->next;
    }
    printf("Element not found\n");
}

int main() {
    struct Node *head = malloc(sizeof(struct Node));
    head->data = 1;

    head->next = malloc(sizeof(struct Node));
    head->next->data = 2;

    head->next->next = malloc(sizeof(struct Node));
    head->next->next->data = 3;

    head->next->next->next = NULL;

    int choice, key;

    while (1) {
        printf("\n1. Delete element\n");
        printf("2. Count elements\n");
        printf("3. Search element\n");
        printf("4. Reverse traversal\n");
        printf("5. Exit\n");

        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("1. Beginning\n");
                printf("2. End\n");
                printf("3. Specific element\n");

                int ch;
                scanf("%d", &ch);

                if (ch == 1) {
                    head = deleteBeginning(head);
                }
                else if (ch == 2) {
                    deleteEnd(head);
                }
                else if (ch == 3) {
                    scanf("%d", &key);
                    deleteNode(head, key);
                }
                break;

            case 2:
                printf("Count = %d\n", countNodes(head));
                break;

            case 3:
                printf("Enter element: ");
                scanf("%d", &key);
                searchElement(head, key);
                break;

            case 4:
                traverseReverse(head);
                printf("\n");
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}