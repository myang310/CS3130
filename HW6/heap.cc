// Ming Yang

#include "heap.h"
#include <iostream>

void
Heap::sort(int arr[], int n, int& comparisons, int& interchanges) {
	build_heap(arr, n, comparisons, interchanges);

	int heapsize = n - 1;

	// Continuously swap the largest element out of the heap
	// and to the end of the array
	for (int i = heapsize; i >= 0; i--) {
		swap(arr, 0, heapsize);
		interchanges++;
		heapsize--;
		// Find the new largest element out of the heap while
		// maintaining a max heap tree
		satisfy_heap(arr, 0, heapsize, comparisons, interchanges);
	}
}

void
Heap::build_heap(int arr[], int n, int& comparisons, int& interchanges) {
	// Set up the property of a max heap tree
	int heapsize = n - 1;

	for (int i = n/2; i >= 0; i--)
		satisfy_heap(arr, i, heapsize, comparisons, interchanges);
}

void
Heap::satisfy_heap(int arr[], int parent, int heapsize, int& comparisons, int& interchanges) {
	// The two children of the parent node
	int left = parent * 2 + 1;
	int right = parent * 2 + 2;

	// Find the index of largest of the three nodes
	int largest = parent;

	comparisons++; // The first if statement
	if (left <= heapsize) {
		comparisons++; // The second if statement
		if (arr[left] > arr[largest]) 
			largest = left;
	}

	comparisons++; // The first if statement
	if (right <= heapsize) {
		comparisons++; // The second if statement
		if (arr[right] > arr[largest])
			largest = right;
	}

	// Swap if there is a child larger than the parent
	if (largest != parent) {
		swap(arr, largest, parent);
		interchanges++;

		// Traverse down to the recently swapped child node
		// and recursively satisfy the heap property
		satisfy_heap(arr, largest, heapsize, comparisons, interchanges);
	}
}

void
Heap::swap(int arr[], int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}