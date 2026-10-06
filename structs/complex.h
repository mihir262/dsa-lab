#pragma once

struct Complex {
	double real;
	double imag;
};

struct Complex addComplex(struct Complex a, struct Complex b);
struct Complex subComplex(struct Complex a, struct Complex b);
struct Complex mulComplex(struct Complex a, struct Complex b);
struct Complex divComplex(struct Complex a, struct Complex b);
void printComplex(struct Complex z);
