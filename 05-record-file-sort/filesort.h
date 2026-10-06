#pragma once

extern char **recs;
extern char **sorted;
extern int nrecs;
extern int nfields;

void get_field(char *line, int col, char *out);
int is_numeric(char *s);
void bubble_sort(char **a, int n, int col, int type);
void insertion_sort(char **a, int n, int col, int type);
void display(char **a, int n);
int load_file(char *fname);
void cleanup(void);
