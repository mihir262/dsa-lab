#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "filesort.h"

char **recs = NULL;
char **sorted = NULL;
int nrecs = 0;
int nfields = 0;

int is_blank(char *s) {
	while (*s && isspace((unsigned char)*s))
		s++;
	return *s == '\0';
}

int count_fields(char *s) {
	int n = 0;
	int in_field = 0;

	for (; *s; s++) {
		if (!isspace((unsigned char)*s)) {
			if (!in_field) {
				n++;
				in_field = 1;
			}
		} else {
			in_field = 0;
		}
	}
	return n;
}

void get_field(char *line, int col, char *out) {
	int i = 0;
	int n = 0;

	while (*line && isspace((unsigned char)*line))
		line++;

	while (*line && i < col) {
		while (*line && !isspace((unsigned char)*line))
			line++;
		while (*line && isspace((unsigned char)*line))
			line++;
		i++;
	}

	while (line[n] && !isspace((unsigned char)line[n]))
		n++;
	if (n > 255)
		n = 255;

	strncpy(out, line, n);
	out[n] = '\0';
}

int is_numeric(char *s) {
	char *end;

	if (*s == '\0')
		return 0;
	strtod(s, &end);
	return end != s && *end == '\0';
}

int cmp_records(char *a, char *b, int col, int type) {
	char fa[256], fb[256];
	char *sa, *sb;
	int c;

	if (col < 0) {
		sa = a;
		sb = b;
	} else {
		get_field(a, col, fa);
		get_field(b, col, fb);
		sa = fa;
		sb = fb;
	}

	if (type <= 2)
		c = strcmp(sa, sb);
	else {
		double da = atof(sa);
		double db = atof(sb);
		c = (da > db) - (da < db);
	}

	if (type == 2 || type == 4)
		c = -c;
	return c;
}

void bubble_sort(char **a, int n, int col, int type) {
	int i, j;
	char *tmp;

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (cmp_records(a[j], a[j + 1], col, type) > 0) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}

void insertion_sort(char **a, int n, int col, int type) {
	int i, j;
	char *key;

	for (i = 1; i < n; i++) {
		key = a[i];
		j = i - 1;
		while (j >= 0 && cmp_records(a[j], key, col, type) > 0) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

void display(char **a, int n) {
	int i;

	if (n == 0) {
		printf("No records\n");
		return;
	}
	for (i = 0; i < n; i++)
		printf("%d. %s\n", i + 1, a[i]);
}

int load_file(char *fname) {
	FILE *fp;
	char *line = NULL;
	size_t linecap = 0;
	ssize_t len;
	int capacity = 4;

	fp = fopen(fname, "r");
	if (fp == NULL)
		return 0;

	recs = malloc(capacity * sizeof(char *));
	if (recs == NULL) {
		fclose(fp);
		return 0;
	}

	while ((len = getline(&line, &linecap, fp)) != -1) {
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
			line[--len] = '\0';

		if (is_blank(line))
			continue;

		if (nrecs >= capacity) {
			capacity *= 2;
			recs = realloc(recs, capacity * sizeof(char *));
		}

		recs[nrecs] = malloc(strlen(line) + 1);
		strcpy(recs[nrecs], line);
		nrecs++;
	}

	free(line);
	fclose(fp);

	nfields = (nrecs > 0) ? count_fields(recs[0]) : 0;
	sorted = malloc((nrecs > 0 ? nrecs : 1) * sizeof(char *));
	return 1;
}

void cleanup(void) {
	int i;

	if (recs != NULL) {
		for (i = 0; i < nrecs; i++)
			free(recs[i]);
		free(recs);
	}
	free(sorted);
}

int main(void) {
	char fname[256];
	int choice, col, type, alg, i;
	int sorted_ready = 0;

	printf("Enter input filename: ");
	scanf("%s", fname);

	if (!load_file(fname)) {
		printf("File not found\n");
		return 1;
	}

	if (nrecs == 0)
		printf("File is empty\n");
	else
		printf("Records: %d   Fields: %d\n", nrecs, nfields);

	while (1) {
		printf("\n===== MENU =====\n");
		printf("1. Display File Contents\n");
		printf("2. Sort Complete Records Alphabetically\n");
		printf("3. Sort by a Selected Column\n");
		printf("4. Display Sorted Output\n");
		printf("5. Save Sorted Data\n");
		printf("6. Exit\n");
		printf("Enter choice: ");
		scanf("%d", &choice);

		if (choice == 1) {
			display(recs, nrecs);
		} else if (choice == 2 || choice == 3) {
			if (nrecs == 0) {
				printf("No records to sort\n");
				continue;
			}

			col = -1;
			type = 1;

			if (choice == 3) {
				printf("Enter column number (1-%d): ", nfields);
				scanf("%d", &col);
				while (col < 1 || col > nfields) {
					printf("Invalid column. Enter again (1-%d): ", nfields);
					scanf("%d", &col);
				}
				col--;

				printf("1. Alphabetical ascending\n");
				printf("2. Alphabetical descending\n");
				printf("3. Numeric ascending\n");
				printf("4. Numeric descending\n");
				printf("Type: ");
				scanf("%d", &type);

				if (type == 3 || type == 4) {
					char f[256];
					int ok = 1;

					for (i = 0; i < nrecs; i++) {
						get_field(recs[i], col, f);
						if (!is_numeric(f)) {
							printf("Invalid numeric data: %s\n", f);
							ok = 0;
							break;
						}
					}
					if (!ok)
						continue;
				}
			}

			printf("1. Bubble Sort\n");
			printf("2. Insertion Sort\n");
			printf("Algorithm: ");
			scanf("%d", &alg);

			for (i = 0; i < nrecs; i++)
				sorted[i] = recs[i];

			if (alg == 1)
				bubble_sort(sorted, nrecs, col, type);
			else
				insertion_sort(sorted, nrecs, col, type);

			sorted_ready = 1;
			printf("\nSorted result:\n");
			display(sorted, nrecs);
		} else if (choice == 4) {
			if (!sorted_ready)
				printf("Sort first\n");
			else
				display(sorted, nrecs);
		} else if (choice == 5) {
			FILE *fp;

			if (!sorted_ready) {
				printf("Sort first\n");
				continue;
			}

			printf("Output filename: ");
			scanf("%s", fname);

			fp = fopen(fname, "w");
			if (fp == NULL) {
				printf("Cannot write file\n");
				continue;
			}

			for (i = 0; i < nrecs; i++)
				fprintf(fp, "%s\n", sorted[i]);
			fclose(fp);
			printf("Saved\n");
		} else if (choice == 6) {
			cleanup();
			break;
		} else {
			printf("Invalid choice\n");
		}
	}

	return 0;
}
