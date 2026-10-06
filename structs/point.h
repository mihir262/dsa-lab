#pragma once

struct Point {
	double x;
	double y;
};

double distance(struct Point p1, struct Point p2);
struct Point midpoint(struct Point p1, struct Point p2);
double triangleArea(struct Point a, struct Point b, struct Point c);
