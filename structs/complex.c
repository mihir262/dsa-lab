#include <stdio.h>
#include "complex.h"

struct Complex addComplex(struct Complex a, struct Complex b) {
	struct Complex result;
	result.real = a.real + b.real;
	result.imag = a.imag + b.imag;
	return result;
}

struct Complex subComplex(struct Complex a, struct Complex b) {
	struct Complex result;
	result.real = a.real - b.real;
	result.imag = a.imag - b.imag;
	return result;
}

struct Complex mulComplex(struct Complex a, struct Complex b) {
	struct Complex result;
	/* (a+bi)(c+di) = (ac - bd) + (ad + bc)i */
	result.real = a.real * b.real - a.imag * b.imag;
	result.imag = a.real * b.imag + a.imag * b.real;
	return result;
}

struct Complex divComplex(struct Complex a, struct Complex b) {
	struct Complex result;
	double denom = b.real * b.real + b.imag * b.imag;

	if (denom == 0) {
		printf("Error: division by zero complex number.\n");
		result.real = 0;
		result.imag = 0;
		return result;
	}

	result.real = (a.real * b.real + a.imag * b.imag) / denom;
	result.imag = (a.imag * b.real - a.real * b.imag) / denom;
	return result;
}

void printComplex(struct Complex z) {
	if (z.imag >= 0)
		printf("%.2f + %.2fi", z.real, z.imag);
	else
		printf("%.2f - %.2fi", z.real, -z.imag);
}
