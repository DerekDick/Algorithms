#include <stdio.h>
#include <stdlib.h> //For random()
#include <time.h> //For time()

void bubbleSort(int arr[], int begin, int end);
void quicksort(int arr[], int begin, int end);

int main(int argc, char* argv[]) {
	int numbers[1000] = { 0 };
	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		numbers[i] = rand()%10000;
	}
	
	//Output initial array
	printf("The initial status:\n");
	for (int i = 0; i < 1000; i++) {
		printf("numbers[%d] = %d\n", i, numbers[i]);
	}

	//Sorting...
	//bubbleSort(numbers, 0, 999);
	quicksort(numbers, 0, 999);

	//Output the sorted array
	printf("The sorted array:\n");
	for (int i = 0; i < 1000; i++) {
		printf("numbers[%d] = %d\n", i, numbers[i]);
	}

	return 0;
}

void bubbleSort(int arr[], int begin, int end) {
	for (int i = end; i > begin; i--) {
		for (int j = begin; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	return;
}

void quicksort(int arr[], int begin, int end) {
	//Set the pivot
	int pivot = arr[end];

	//Partition
	int i = begin, j = end;
	while (i < j) {
		while (arr[i] < pivot) {
			i++;
		}
		while (pivot < arr[j]) {
			j--;
		}
		if (i < j) {
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
		else if (i == j) {
			i++;
			j--;
		}
	}

	//Recursion
	if (begin < j) {
		quicksort(arr, begin, j);
	}
	if (i < end) {
		quicksort(arr, i, end);
	}

	return;
}
