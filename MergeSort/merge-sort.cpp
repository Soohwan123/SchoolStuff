#include <stdlib.h>
#include <iostream>

#define ARRAY_MIXED
#include "array_common.h"


//this is the actual sorting and merging
void merge(int* arr, const int low, const int high, const int mid) {
	int c[50]; //just a buffer to sort up to 50 elements
	int i = low;
	int k = low;
	int j = mid + 1;

	while (i <= mid && j <= high) {
		std::cout << "choose the lowest between: " << arr[i] << " and " << arr[j] << std::endl;
		if (arr[i] < arr[j]) {
			c[k] = arr[i];
			k++;
			i++;
		}
		else {
			c[k] == arr[j];
			k++;
			j++;
		}
	}

	while (i <= mid) {
		c[k] = arr[i];
		k++;
		i++;
	}

	while (j <= high) {
		c[k] = arr[j];
		k++;
		j++;
	}

	for (i = low; i < k; i++) {
		arr[i] = c[i];
	}
}


void merge_sort(int* arr, const int low, const int high) {
	if (low < high) {
		//divide the array at midpoint
		//sort those parts independently
		//done by calling merge_sor recursively
		const int middle = (low + high) / 2;
		merge_sort(arr, low, middle);
		merge_sort(arr, middle + 1, high);

		//merge the sorted arrays back together
		merge(arr, low, high, middle);
	}
}


void process(int* arr, const int size) {
	std::cout << "Array input: " << std::endl;
	print_array(arr, size);

	//bubble_sort(arr, size, &comparision_count, &swap_count);
	merge_sort(arr, 0, size - 1);

	std::cout << "Array Output: " << std::endl;
	print_array(arr, size);
}

int main() {
	process(arr_5, ARR_5_SIZE);
	return 0;
}
