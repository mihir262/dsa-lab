#include <stdio.h>
#include <stdlib.h>
#include "stackarray.h"

int main(void) {
    int stack[MAX_SIZE];
    int top = -1;

    while (1) {
        printf("Enter 1 to push,\n 2 to pop,\n 3 to peek,\n 4 to check if full,\n 5 to check if empty,\n 6 to exit: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int value;
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(stack, &top, value);
                break;
            }
            case 2:
                pop(stack, &top);
                break;
            case 3:
                printf("Top value: %d\n", peek(stack, top));
                break;
            case 4:
                printf("Is stack full? %s\n", isFull(top) ? "Yes" : "No");
                break;
            case 5:
                printf("Is stack empty? %s\n", isEmpty(top) ? "Yes" : "No");
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
