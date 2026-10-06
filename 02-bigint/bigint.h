#pragma once

typedef struct {
    int *digits;
    int length;
    int sign;
} bigInt;

void printbigInt(bigInt n);
