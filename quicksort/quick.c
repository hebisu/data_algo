////////////////////////////////////////////////////////
// Quick sort algorithm utilizing insertion sort, stack
// and binary search
// Created by Hiro Ebisu
////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "IntStack.h"

#define swap(type, x, y) do { type t = x; x = y; y = t; } while (0)
#define QUICK_OR_INSERT 9

// Sort array[a], array[b], array[c] and return the index of median
int sort3element(int array[], int a, int b, int c)
{
	if (array[b] < array[a]) swap(int, array[b], array[a]);
	if (array[c] < array[b]) swap(int, array[c], array[b]);
	if (array[b] < array[a]) swap(int, array[b], array[a]);
	return b;
}

// Find the insertion target with binary search
int binary_search(const int array[], int n, int target)
{
	int ptr_left = 0;			//Search left
	int ptr_right = n - 1;		//Search right
	int ptr_centre;				//Search centre

	if(target >= array[ptr_right]){
		return n; //No insertion
	}
	else if(target <= array[ptr_left]){
		return 0; //Insert to [0]
	}

	do {
		ptr_centre = (ptr_left + ptr_right) / 2;

		if (array[ptr_centre] == target){
			if (ptr_centre > 0) return ptr_centre;
		}
		else if (array[ptr_centre] < target)
			ptr_left = ptr_centre + 1;
		else
			ptr_right = ptr_centre - 1;
	} while (ptr_left <= ptr_right);

	if(ptr_centre == ptr_right) return ptr_centre + 1;
	else return ptr_centre;
}

// Insertion sort with binary search
int insertion_sort(int array[], int n)
{
	int i, k, tmp = 0, target = 0;

	for (i = 1; i < n; i++) {
        //Insert
		tmp = array[i];

		// Find the insertion target with binary search
		target = binary_search(array, i, tmp);

		// Use memmove for faster process
        if(memmove(&array[target + 1], &array[target], sizeof(int) * (i - target)) == NULL){
            printf("Failed to memmove\n");
            return -1;
        }
		array[target] = tmp;
	}
    return 0;
}

// Initialize stack
int init_stack(IntStack *lstack, IntStack *rstack, int left, int right){
	if(Initialize(lstack, right - left + 1) < 0){
		fprintf(stderr, "Failed to Initialize lstack.\n");
		return -1;
	}
	if(Initialize(rstack, right - left + 1) < 0){
		fprintf(stderr, "Failed to Initialize rstack.\n");
		return -1;
	}

	if(Push(lstack, left) < 0){
		fprintf(stderr, "Failed to Push lstack.\n");
		return -1;
	}
	if(Push(rstack, right)){
		fprintf(stderr, "Failed to Push rstack.\n");
		return -1;
	}
	return 0;
}

// Quick sort with stack (no recursive function)
int quick_stk(int array[], int left, int right)
{
	IntStack lstack; // Stack for left indexes of devided array
	IntStack rstack; // Stack for right indexes of devided array

	if(init_stack(&lstack, &rstack, left, right) < 0){
		fprintf(stderr, "Failed to Initialize stack.\n");
		return -1;
	}

	int loop_cnt = 0;
    int stack_cnt = 1;
    int max_stack_cnt = 0;
    int bin_search_cnt = 0;

	printf("-----------------\n");
	while (!IsEmpty(&lstack)) {
		printf("loop No.%d\n", loop_cnt++);
        printf("stack No.%d\n", --stack_cnt);
		int ptr_left = (Pop(&lstack, &left), left); // Left cursur pointer
		int ptr_right = (Pop(&rstack, &right), right); // Right cursur pointer

		// Select pivot element
        int med = sort3element(array, ptr_left, (ptr_left + ptr_right) / 2, ptr_right);
        swap(int, array[med], array[ptr_right - 1]);
        int pivot = array[ptr_right - 1];
        ptr_left += 1;
        ptr_right -= 2;

		printf("ptr_left:%d, ptr_right:%d, pivot:%d\n", ptr_left, ptr_right, pivot);
		printf("array[%d] ~ array[%d]: ", ptr_left, ptr_right);
		for(int i = ptr_left; i <= ptr_right; i++){
			printf("%d, ", array[i]);
		}
		printf("\n");

		// Progress pointers and swap elements
		do {
			while (array[ptr_left] < pivot) ptr_left++;
			while (array[ptr_right] > pivot) ptr_right--;
			if (ptr_left <= ptr_right) {
				swap(int, array[ptr_left], array[ptr_right]);
				ptr_left++;
				ptr_right--;
			}
		} while (ptr_left <= ptr_right);

        // Push larger side first in order to reduce stack capacity
	    if (ptr_right - left < right - ptr_left) {
		    swap(int, ptr_left, left);
	    	swap(int, ptr_right, right);
    	}

		// Use insertion_sort instead of quick sort if num of elements is less than QUICK_OR_INSERT
    	if (left < ptr_right) {
            if(ptr_right - left + 1 > QUICK_OR_INSERT){
    	    	Push(&lstack, left); // Push 2 indexes of left group
	    	   	Push(&rstack, ptr_right);
                stack_cnt++;
                if(max_stack_cnt < stack_cnt) max_stack_cnt = stack_cnt;
            }
            else{
                bin_search_cnt++;
                if(insertion_sort(&array[left], ptr_right - left + 1) < 0){
                    fprintf(stderr, "Failed to insert sort.\n");
                    return -1;
                }
            }
        }
		if (ptr_left < right) {
            if(right - ptr_left + 1 > QUICK_OR_INSERT){
		        Push(&lstack, ptr_left); // Push 2 indexes of right group
		        Push(&rstack, right);
                stack_cnt++;
                if(max_stack_cnt < stack_cnt) max_stack_cnt = stack_cnt;
            }
            else{
                bin_search_cnt++;
                if(insertion_sort(&array[ptr_left], right - ptr_left + 1) < 0){
					fprintf(stderr, "Failed to insert sort.\n");
                    return -1;
                }
            }
		}
		printf("-----------------\n");
	}
	Terminate(&lstack);
	Terminate(&rstack);
    printf("total loop count:%d, max stack count:%d, binary search count:%d\n",\
			loop_cnt, max_stack_cnt, bin_search_cnt);
	return 0;
}

int main(int argc, char *argv[])
{
	int i, num_elem;
	int *array;

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
    printf("-----------------\n");

	// Quick sort with stack
	printf("Quick sort (stack version) starts.\n");
	if(quick_stk(array, 0, num_elem - 1) < 0){
		printf("Quick sort failed.\n");
		free(array);
		return 0;
	}

	printf("Quick sort finished.\n");
	for (i = 0; i < num_elem; i++){
		printf("array[%d] = %d\n", i, array[i]);
	}

	if(array){
		printf("Free array.\n");
		free(array);
	}

	return 0;
}
