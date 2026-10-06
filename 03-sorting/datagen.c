#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fp = fopen("input.txt", "w");

    int n = 10000;

    srand(time(NULL));

    fprintf(fp, "%d\n", n);

    for(int i = 0; i < n; i++)
        fprintf(fp, "%d ", rand());

    fclose(fp);
    return 0;
}