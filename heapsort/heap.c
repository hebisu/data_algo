////////////////////////////////////////
// heap sort algorithm
// Created by Hiro Ebisu
////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gettime.h"

#define swap(type, x, y)  do { type t = x; x = y; y = t; } while (0)

// Make a[left] - a[right] heap
static void downheap(int array[], int left, int right)
{
	int temp = array[left];	 // root node (smallest value)
	int child;
	int parent;

	for (parent = left; parent < (right + 1) / 2; parent = child) {
		int child_l = parent * 2 + 1;   // Left child
		int child_r = child_l + 1;		// Right child
		child = (child_r <= right && array[child_r] > array[child_l]) ? child_r : child_l; // select larger child
		if (temp >= array[child]){ // If child node value is smaller than root (smallest value)
            break;
        }
		array[parent] = array[child]; // root node (smallest value) goes one step deeper
	}
	array[parent] = temp; // Copy root node(smallest value) to bottom node
}

// Heap sort
void heapsort(int array[], int n)
{
	int i;

    // Make array heap from bottom branch to root tree
	for (i = (n - 1) / 2; i >= 0; i--)
		downheap(array, i, n - 1);

	for (i = n - 1; i > 0; i--) {
		swap(int, array[0], array[i]); // Swap root node and last leaf node
		downheap(array, 0, i - 1);      // Make unsorted array heap
	}
}

int main(int argc, char *argv[])
{
	int i, num_elem;
	int *array;
    double start_time;
    double process_time;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s NUM_OF_ELEMENTS\n", argv[0]);
		return 0;
	}

	num_elem = atoi(argv[1]);
	if(num_elem < 2){
		fprintf(stderr, "NUM_OF_ELEMENTS must be larger than 2\n");
		return 0;
	}

	printf("Num:%d\n", num_elem);
	array = calloc(num_elem, sizeof(int));
	if(!array){
		fprintf(stderr, "Failed to calloc\n");
		return 0;
	}

    srand((unsigned)time(NULL)); // Set random base
    printf("RAND_MAX=%d\n",RAND_MAX);
    for(i = 0; i < num_elem; i++){
        array[i] = rand() % num_elem; // 0 - num_elem
        printf("%d, ", array[i]);
    }

    printf("\nHeap sort start\n");
    start_time = gettime();
	heapsort(array, num_elem);
    process_time = (gettime() - start_time) * 1000; // sec to msec
	printf("heap sort finished.\n");

	for (i = 0; i < num_elem; i++){
		printf("array[%d] = %d\n", i, array[i]);
	}

    printf("Process time:  %8.8f [msec]\n", process_time);

	if(array){
		free(array);
	}

	return 0;
}
