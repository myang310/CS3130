// Ming Yang

class Heap {
	public:
		void static sort(int arr[], int n, int& comparisons, int& interchanges);
	private:
		void static build_heap(int arr[], int n, int& comparisons, int& interchanges);
		void static satisfy_heap(int arr[], int parent, int heapsize, int& comparisons, int& interchanges);
		void static swap(int arr[], int a, int b);

};