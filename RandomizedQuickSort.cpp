//Randomized Quicksort
// Time Complexity: O(nlogn) (average), O(n^2) (worst case)

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to swap two elements
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

// Function to generate a random pivot index
int generateRandomPivot(int low, int high) {
	srand(time(NULL));
	return low + rand() % (high - low + 1);
}

// Function to perform QuickSort
void quickSort(int arr[], int low, int high) {
	if (low < high) {
		int pivotIndex = generateRandomPivot(low, high);
		int pivotValue = arr[pivotIndex];

		// Swap the pivot element with the last element
		swap(&arr[pivotIndex], &arr[high]);

		int i = low - 1;

		for (int j = low; j < high; j++) {
			if (arr[j] < pivotValue) {
				i++;
				swap(&arr[i], &arr[j]);
			}
		}

		// Swap the pivot element back to its final position
		swap(&arr[i+1], &arr[high]);

		// Recursively sort the left and right subarrays
		quickSort(arr, low, i);
		quickSort(arr, i+2, high);
	}
}

int main() {
	int arr[] = {5, 2, 7, 3, 1, 6, 4, 8};
	int n = sizeof(arr)/sizeof(arr[0]);

	cout << "Original array: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	quickSort(arr, 0, n-1);

	cout << "\nSorted array: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}
