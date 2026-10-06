#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorting.h"

void bubbleSort(int arr[], int n) {
    int temp;

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    int minIndex, temp;

    for(int i = 0; i < n - 1; i++) {
        minIndex = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }
        if(minIndex != i) {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

int main() {
    FILE *fp = fopen("input.txt", "r");
    if(fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    int n;
    fscanf(fp, "%d", &n);

    int *arr = malloc(n * sizeof(int));
    int *bubble = malloc(n * sizeof(int));
    int *selection = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);

    // Create copies
    for(int i = 0; i < n; i++) {
        bubble[i] = arr[i];
        selection[i] = arr[i];
    }

    clock_t start, end;

    // Bubble Sort timing
    start = clock();
    bubbleSort(bubble, n);
    end = clock();

    double bubbleTime = (double)(end - start) / CLOCKS_PER_SEC;
    
    // Selection Sort timing
    start = clock();
    selectionSort(selection, n);
    end = clock();
    double selectionTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Number of elements: %d\n", n);
    printf("Bubble Sort Time    : %.6f seconds\n", bubbleTime);
    printf("Selection Sort Time : %.6f seconds\n", selectionTime);

    free(arr);
    free(bubble);
    free(selection);
    return 0;
}