#include <stdio.h>
#include "complex.h"
#include "point.h"

int main(void) {
	struct Complex z1, z2, result;

	printf("=== Complex Number Operations ===\n");
	printf("Enter first complex number (real imag): ");
	scanf("%lf %lf", &z1.real, &z1.imag);

	printf("Enter second complex number (real imag): ");
	scanf("%lf %lf", &z2.real, &z2.imag);

	printf("\n");
	printf("z1 = ");
	printComplex(z1);
	printf("\nz2 = ");
	printComplex(z2);
	printf("\n\n");

	result = addComplex(z1, z2);
	printf("z1 + z2 = ");
	printComplex(result);
	printf("\n");

	result = subComplex(z1, z2);
	printf("z1 - z2 = ");
	printComplex(result);
	printf("\n");

	result = mulComplex(z1, z2);
	printf("z1 * z2 = ");
	printComplex(result);
	printf("\n");

	result = divComplex(z1, z2);
	printf("z1 / z2 = ");
	printComplex(result);
	printf("\n");

	struct Point p1, p2, p3, mid;

	printf("\n=== Point Operations ===\n");
	printf("Enter coordinates of point P1 (x y): ");
	scanf("%lf %lf", &p1.x, &p1.y);

	printf("Enter coordinates of point P2 (x y): ");
	scanf("%lf %lf", &p2.x, &p2.y);

	printf("\nDistance between P1 and P2 = %.4f\n", distance(p1, p2));

	mid = midpoint(p1, p2);
	printf("Midpoint of P1P2 = (%.4f, %.4f)\n", mid.x, mid.y);

	printf("\nEnter coordinates of third vertex P3 (x y) for triangle: ");
	scanf("%lf %lf", &p3.x, &p3.y);

	printf("Area of triangle P1P2P3 = %.4f\n", triangleArea(p1, p2, p3));

	return 0;
}
