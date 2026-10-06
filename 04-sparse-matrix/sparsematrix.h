#pragma once

#define MAX 100

typedef struct {
	int row;
	int col;
	int val;
} Triplet;

typedef struct {
	int rows;
	int cols;
	int terms;
	Triplet data[MAX];
} Sparse;

Sparse createMatrix(void);
void displaySparse(Sparse s);
Sparse transpose(Sparse s);
Sparse add(Sparse a, Sparse b);
Sparse multiply(Sparse a, Sparse b);
void update(Sparse *s);
void deleteElement(Sparse *s);
