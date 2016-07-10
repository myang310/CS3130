// Ming Yang

#include "bubble.h"

void
Bubble::sort(int arr[], int n, int& comparisons, int& interchanges) {
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j+1]) {
				swap(arr, j, j+1);
				interchanges++; // Swap was called
			}
			comparisons++; // Each if statement
		}
	}
}

void
Bubble::swap(int arr[], int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}