/* 
Write a program to remove duplicate doubles from an array of doubles. In the program,
write a function which accepts an array of doubles and removes the duplicates from the
array and has return type void.
*/


#include <stdio.h>
#include "duplicates.h"

void removeDuplicates(double arr[], int *size){

	for(int i = 0; i < *size; i++){
		for(int j = i + 1; j < *size; j++){
			if(arr[i] == arr[j]){
				for(int k = j; k < *size - 1; k++){
					arr[k] = arr[k+1];
				}
				(*size)--;
				j--;
			}
		}
	}
}

int main(){
	int n;
	double arr[100];

	printf("Enter the number of elements in the array: \n");
	scanf("%d", &n);

	printf("Enter the elements of the array\n");
	for(int i = 0; i < n; i++){
		scanf("%lf", &arr[i]);
	}

	removeDuplicates(arr, &n);

	printf("\nArray after removing duplicates: ");
	for(int i = 0; i < n; i++){
		printf("%.2f ", arr[i]);
	}
	return 0;
}
