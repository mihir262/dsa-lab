#include <stdio.h>
#include <stdlib.h>
#include "sparsematrix.h"

static int findPosition(Sparse s, int r, int c);

int main() {
	Sparse A, B, C;
	int choice;

	while (1) {
		printf("\n===== MENU =====\n");
		printf("1. Create Matrix A\n");
		printf("2. Create Matrix B\n");
		printf("3. Display Matrix\n");
		printf("4. Transpose Matrix\n");
		printf("5. Addition\n");
		printf("6. Multiplication\n");
		printf("7. Update\n");
		printf("8. Delete\n");
		printf("9. Exit\n");

		printf("Enter choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			A = createMatrix();
			break;
		case 2:
			B = createMatrix();
			break;
		case 3: {
			int x;
			printf("Display (1=A,2=B): ");
			scanf("%d", &x);
			if (x == 1) displaySparse(A);
			else displaySparse(B);
			break;
		}

		case 4: {
			int x;
			printf("Transpose (1=A,2=B): ");
			scanf("%d", &x);
			if (x == 1) C = transpose(A);
			else C = transpose(B);
			displaySparse(C);
			break;
		}
		case 5: {
			C = add(A, B);
			displaySparse(C);
			break;
		}
		case 6: {
			C = multiply(A, B);
			displaySparse(C);
			break;
		}
		case 7: {
			int x;
			printf("Update (1=A,2=B): ");
			scanf("%d", &x);
			if (x == 1) update(&A);
			else update(&B);
			break;
		}

		case 8: {
			int x;
			printf("Delete from (1=A,2=B): ");
			scanf("%d", &x);
			if (x == 1) deleteElement(&A);
			else deleteElement(&B);
			break;
		}
		case 9:
			exit(0);
		default:
			printf("Invalid choice\n");
		}
	}
}

static int findPosition(Sparse s, int r, int c) {
	for (int i = 0; i < s.terms; i++) {
		if (s.data[i].row == r && s.data[i].col == c)
			return i;
	}
	return -1;
}

Sparse createMatrix() {
	Sparse s;

	printf("Rows Columns: ");
	scanf("%d %d", &s.rows, &s.cols);

	printf("Number of non-zero elements: ");
	int needed;
	scanf("%d", &needed);

	s.terms = 0;
	int count = 0;

	while (count < needed) {
		int r, c, v;

		printf("Row Column Value: ");
		scanf("%d%d%d", &r, &c, &v);

		if (r < 0 || r >= s.rows || c < 0 || c >= s.cols) {
			printf("Invalid position\n");
			continue;
		}

		if (v == 0) {
			printf("Zero not allowed\n");
			continue;
		}

		if (findPosition(s, r, c) != -1) {
			printf("Duplicate position\n");
			continue;
		}

		s.data[count].row = r;
		s.data[count].col = c;
		s.data[count].val = v;

		count++;
		s.terms = count;
	}

	s.terms = count;

	return s;
}

void displaySparse(Sparse s) {
	printf("\nRows=%d Cols=%d Terms=%d\n", s.rows, s.cols, s.terms);

	if (s.terms == 0) {
		printf("Matrix has no non-zero elements\n");
		return;
	}

	printf("Row Col Value\n");

	for (int i = 0; i < s.terms; i++) printf("%3d %3d %5d\n", s.data[i].row, s.data[i].col, s.data[i].val);
}

Sparse transpose(Sparse s) {
	Sparse t;

	t.rows = s.cols;
	t.cols = s.rows;
	t.terms = s.terms;

	int k = 0;

	for (int c = 0; c < s.cols; c++) {
		for (int i = 0; i < s.terms; i++) {
			if (s.data[i].col == c) {
				t.data[k].row = s.data[i].col;
				t.data[k].col = s.data[i].row;
				t.data[k].val = s.data[i].val;
				k++;
			}
		}
	}

	return t;
}

Sparse add(Sparse a, Sparse b) {
	Sparse c;

	c.terms = 0;

	if (a.rows != b.rows || a.cols != b.cols) {
		printf("Addition not possible\n");
		return c;
	}

	c.rows = a.rows;
	c.cols = a.cols;

	for (int i = 0; i < a.terms; i++)
		c.data[c.terms++] = a.data[i];

	for (int i = 0; i < b.terms; i++) {
		int pos = findPosition(c,
							   b.data[i].row,
							   b.data[i].col);

		if (pos == -1) {
			c.data[c.terms++] = b.data[i];
		} else {
			c.data[pos].val += b.data[i].val;

			if (c.data[pos].val == 0) {
				for (int j = pos; j < c.terms - 1; j++)
					c.data[j] = c.data[j + 1];

				c.terms--;
			}
		}
	}

	return c;
}

Sparse multiply(Sparse a, Sparse b) {
	Sparse c;

	c.rows = a.rows;
	c.cols = b.cols;
	c.terms = 0;

	if (a.cols != b.rows) {
		printf("Multiplication not possible\n");
		return c;
	}

	for (int i = 0; i < a.terms; i++) {
		for (int j = 0; j < b.terms; j++) {
			if (a.data[i].col == b.data[j].row) {
				int r = a.data[i].row;
				int col = b.data[j].col;
				int val = a.data[i].val * b.data[j].val;

				int pos = findPosition(c, r, col);

				if (pos == -1) {
					c.data[c.terms].row = r;
					c.data[c.terms].col = col;
					c.data[c.terms].val = val;
					c.terms++;
				} else {
					c.data[pos].val += val;

					if (c.data[pos].val == 0) {
						for (int k = pos; k < c.terms - 1; k++)
							c.data[k] = c.data[k + 1];

						c.terms--;
					}
				}
			}
		}
	}

	return c;
}

void update(Sparse *s) {
	int r, c, v;

	printf("Row Column NewValue: ");
	scanf("%d%d%d", &r, &c, &v);

	int pos = findPosition(*s, r, c);

	if (pos == -1) {
		printf("Element not found\n");
		return;
	}

	if (v == 0) {
		deleteElement(s);
		return;
	}

	s->data[pos].val = v;
}

void deleteElement(Sparse *s) {
	int r, c;

	printf("Row Column: ");
	scanf("%d%d", &r, &c);

	int pos = findPosition(*s, r, c);

	if (pos == -1) {
		printf("Element not found\n");
		return;
	}

	for (int i = pos; i < s->terms - 1; i++)
		s->data[i] = s->data[i + 1];

	s->terms--;

	printf("Deleted successfully\n");
}
