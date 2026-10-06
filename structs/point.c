#include <math.h>
#include "point.h"

double distance(struct Point p1, struct Point p2) {
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	return sqrt(dx * dx + dy * dy);
}

struct Point midpoint(struct Point p1, struct Point p2) {
	struct Point mid;
	mid.x = (p1.x + p2.x) / 2.0;
	mid.y = (p1.y + p2.y) / 2.0;
	return mid;
}

double triangleArea(struct Point a, struct Point b, struct Point c) {
	double area = (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0;
	if (area < 0)
		area = -area;
	return area;
}
