// Ming Yang

#include "quick.h"

void
Quick::sort(int arr[], int size, int& comparisons, int& interchanges) {
	sort(arr, 0, size-1, comparisons, interchanges);
}

void
Quick::sort(int arr[], int start, int end, int& comparisons, int& interchanges) {
	// Choose a pivot point
	int mid = start + (end - start) / 2;
	int pivot = arr[mid];

	int i = start;
	int j = end;

	// Partition the array based upon a pivot point (arr[end])
	comparisons++;
	while (i <= j) {
		// Find an arr[i] that is greater than or equal to the pivot
		comparisons++; // First while check
		while (arr[i] < pivot){
			i++;
			comparisons++; // Each subsequent while check
		}

		// Find an arr[i] that is less than or equal to the pivot
		comparisons++; // First while check
		while (arr[j] > pivot) {
			j--;
			comparisons++; // Each subsequent while check
		}

		// Swap and move i and j past the swapped indexes
		if (i <= j) {
			swap (arr, i, j);
			interchanges++; // Swap was called
			i++;
			j--;
		}

		comparisons++;
	}

	// Recursively sort the two partitions
	if (start < j)
		Quick::sort(arr, start, j, comparisons, interchanges);
	if (i < end)
		Quick::sort(arr, i, end, comparisons, interchanges);
	comparisons += 2; // Check if recursive call is necessary
}

void
Quick::swap(int arr[], int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}