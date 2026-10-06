#include <stdio.h>
#include <stdlib.h>
#include "polynomial.h"

/* Create a new node */
struct Node* createNode(int coeff, int exp) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    return newNode;
}

/* Insert a term in descending order of exponent */
struct Node* insertTerm(struct Node *head, int coeff, int exp) {
    if (coeff == 0)
        return head;

    struct Node *newNode = createNode(coeff, exp);

    /* Empty list or highest exponent */
    if (head == NULL || exp > head->exp) {
        newNode->next = head;
        return newNode;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;

    /* Find position */
    while (temp != NULL && temp->exp > exp) {
        prev = temp;
        temp = temp->next;
    }

    /* Same exponent: combine coefficients */
    if (temp != NULL && temp->exp == exp) {
        temp->coeff += coeff;
        free(newNode);

        /* Remove node if coefficient becomes zero */
        if (temp->coeff == 0) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;

            free(temp);
        }

        return head;
    }

    /* Insert between prev and temp */
    newNode->next = temp;
    prev->next = newNode;

    return head;
}

/* Read a polynomial */
struct Node* readPolynomial() {
    struct Node *head = NULL;
    int n, coeff, exp;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    printf("Enter coefficient and exponent for each term:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coeff, &exp);
        head = insertTerm(head, coeff, exp);
    }

    return head;
}

/* Display polynomial */
void display(struct Node *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }

    struct Node *temp = head;

    while (temp != NULL) {
        if (temp != head && temp->coeff > 0)
            printf(" + ");

        if (temp->coeff < 0)
            printf(" - ");

        int coeff = abs(temp->coeff);

        if (temp->exp == 0)
            printf("%d", coeff);
        else if (temp->exp == 1)
            printf("%dx", coeff);
        else
            printf("%dx^%d", coeff, temp->exp);

        temp = temp->next;
    }

    printf("\n");
}

/* Add two polynomials */
struct Node* addPolynomial(struct Node *p1, struct Node *p2) {
    struct Node *result = NULL;

    while (p1 != NULL) {
        result = insertTerm(result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        result = insertTerm(result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

/* Subtract p2 from p1 */
struct Node* subtractPolynomial(struct Node *p1, struct Node *p2) {
    struct Node *result = NULL;

    while (p1 != NULL) {
        result = insertTerm(result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        result = insertTerm(result, -p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

/* Multiply two polynomials */
struct Node* multiplyPolynomial(struct Node *p1, struct Node *p2) {
    struct Node *result = NULL;

    for (struct Node *a = p1; a != NULL; a = a->next) {
        for (struct Node *b = p2; b != NULL; b = b->next) {
            int coeff = a->coeff * b->coeff;
            int exp = a->exp + b->exp;

            result = insertTerm(result, coeff, exp);
        }
    }

    return result;
}

/* Free linked list */
void freePolynomial(struct Node *head) {
    struct Node *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void printMenu() {
    printf("\n----- Polynomial Menu -----\n");
    printf("1. Enter first polynomial\n");
    printf("2. Enter second polynomial\n");
    printf("3. Display polynomials\n");
    printf("4. Add\n");
    printf("5. Subtract (P1 - P2)\n");
    printf("6. Multiply\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node *p1 = NULL;
    struct Node *p2 = NULL;
    struct Node *result = NULL;
    int choice;

    while (1) {
        printMenu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                freePolynomial(p1);
                printf("Enter first polynomial:\n");
                p1 = readPolynomial();
                printf("First polynomial: ");
                display(p1);
                break;

            case 2:
                freePolynomial(p2);
                printf("Enter second polynomial:\n");
                p2 = readPolynomial();
                printf("Second polynomial: ");
                display(p2);
                break;

            case 3:
                printf("First polynomial: ");
                display(p1);
                printf("Second polynomial: ");
                display(p2);
                break;

            case 4:
                freePolynomial(result);
                result = addPolynomial(p1, p2);
                printf("Addition: ");
                display(result);
                break;

            case 5:
                freePolynomial(result);
                result = subtractPolynomial(p1, p2);
                printf("Subtraction (P1 - P2): ");
                display(result);
                break;

            case 6:
                freePolynomial(result);
                result = multiplyPolynomial(p1, p2);
                printf("Multiplication: ");
                display(result);
                break;

            case 7:
                freePolynomial(p1);
                freePolynomial(p2);
                freePolynomial(result);
                printf("Exiting.\n");
                return 0;

            default:
                printf("Invalid choice. Enter a number from 1 to 7.\n");
        }
    }

    freePolynomial(p1);
    freePolynomial(p2);
    freePolynomial(result);
    return 0;
}

