#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bigint.h"

void printbigInt(bigInt n) {
    if (n.sign == -1)
        printf("-");

    for (int i = n.length - 1; i >= 0; i--)
        printf("%d", n.digits[i]);

    printf("\n");
}

int main() {
    char str[10000];

    printf("Enter a number: ");
    scanf("%9999s", str);

    bigInt n;

    int start = 0;
    n.sign = 1;

    if (str[0] == '-') {
        n.sign = -1;
        start = 1;
    }

    n.length = strlen(str) - start;
    n.digits = malloc(n.length * sizeof(int));

    int j = 0;
    for (int i = strlen(str) - 1; i >= start; i--) {
        n.digits[j++] = str[i] - '0';
    }

    printbigInt(n);

    free(n.digits);
    return 0;
}