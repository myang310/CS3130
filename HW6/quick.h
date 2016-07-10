// Ming Yang

class Quick {
	public:
		void static sort(int arr[], int size, int& comparisons, int& interchanges);
	private:
		void static sort(int arr[], int start, int end, int& comparisons, int& interchanges);
		void static swap(int arr[], int a, int b);
};