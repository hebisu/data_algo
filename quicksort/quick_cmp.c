////////////////////////////////////////////////////////
// Quick sort algorithm utilizing insertion sort, stack,
// binary search and compare function pointer
// Created by Hiro Ebisu
////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "IntStack.h"

#define swap(type, x, y) do { type t = x; x = y; y = t; } while (0)
#define QUICK_OR_INSERT 9

// Integer compare function for q_sort input (ascending)
int int_compare_ascending(const int* a, const int* b){
	if(*a < *b) return -1;
	else if(*a > *b) return 1;
	else return 0; // if(a == b)
}

// Integer compare function for q_sort input (descending)
int int_compare_descending(const int* a, const int* b){
	if(*a < *b) return 1;
	else if(*a > *b) return -1;
	else return 0; // if(a == b)
}

// Sort array[a], array[b], array[c] and return the index of median
int sort3element_cmp(int array[], int a, int b, int c,\
					int (*compar)(const void *, const void *))
{
	if (compar(&array[b], &array[a]) < 0) swap(int, array[b], array[a]);
	if (compar(&array[c], &array[b]) < 0) swap(int, array[c], array[b]);
	if (compar(&array[b], &array[a]) < 0) swap(int, array[b], array[a]);
	return b;
}

// Find the insertion target with binary search
int binary_search_cmp(const int array[], int n, int target,\
					int (*compar)(const void *, const void *))
{
	int ptr_left = 0;			//Search left
	int ptr_right = n - 1;		//Search right
	int ptr_centre;				//Search centre

	// if(target >= array[ptr_right]){
	if(compar(&target, &array[ptr_right]) >= 0){
		return n; //No insertion
	}
	// else if(target <= array[ptr_left]){
	else if(compar(&target, &array[ptr_left]) <= 0){
		return 0; //Insert to [0]
	}

	do {
		ptr_centre = (ptr_left + ptr_right) / 2;

		// if (array[ptr_centre] == target){
		if (compar(&array[ptr_centre], &target) == 0){
			if (ptr_centre > 0) return ptr_centre;
		}
		// else if (array[ptr_centre] < target)
		else if (compar(&array[ptr_centre], &target) < 0)
			ptr_left = ptr_centre + 1;
		else
			ptr_right = ptr_centre - 1;
	} while (ptr_left <= ptr_right);

	if(ptr_centre == ptr_right) return ptr_centre + 1;
	else return ptr_centre;
}

// Insertion sort with binary search
int insertion_sort_cmp(int array[], int n,\
					int (*compar)(const void *, const void *))
{
	int i, k, tmp = 0, target = 0;

	for (i = 1; i < n; i++) {
        //Insert
		tmp = array[i];

		// Find the insertion target with binary search
		target = binary_search_cmp(array, i, tmp, compar);

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

void quick_sort_cmp(void *base, size_t nmemb, size_t size,\
			int (*compar)(const void *, const void *)){
	IntStack lstack; // Stack for left indexes of devided array
	IntStack rstack; // Stack for right indexes of devided array

	int loop_cnt = 0;
    int stack_cnt = 1;
    int max_stack_cnt = 0;
    int bin_search_cnt = 0;
	int left = 0;
	int right = (int)nmemb - 1;
	int *array = (int *)base;

	if(init_stack(&lstack, &rstack, left, right) < 0){
		fprintf(stderr, "Failed to Initialize stack.\n");
		if(array) free(array);
		exit(0);
	}

	printf("-----------------\n");
	while (!IsEmpty(&lstack)) {
		printf("loop No.%d\n", loop_cnt++);
        printf("stack No.%d\n", --stack_cnt);
		int ptr_left = (Pop(&lstack, &left), left); // Left cursur pointer
		int ptr_right = (Pop(&rstack, &right), right); // Right cursur pointer

		// Select pivot element
		int med = sort3element_cmp(array, ptr_left, (ptr_left + ptr_right) / 2, ptr_right, compar);
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
			while (compar(&array[ptr_left], &pivot) < 0) ptr_left++;
			while (compar(&array[ptr_right], &pivot) > 0) ptr_right--;
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
                if(insertion_sort_cmp(&array[left], ptr_right - left + 1, compar) < 0){
                    fprintf(stderr, "Failed to insert sort.\n");
                    exit(0);
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
                if(insertion_sort_cmp(&array[ptr_left], right - ptr_left + 1, compar) < 0){
					fprintf(stderr, "Failed to insert sort.\n");
                    exit(0);
                }
            }
		}
		printf("-----------------\n");
	}

	Terminate(&lstack);
	Terminate(&rstack);
    printf("total loop count:%d, max stack count:%d, binary search count:%d\n",\
			loop_cnt, max_stack_cnt, bin_search_cnt);
}

int main(int argc, char *argv[])
{
	int i, num_elem, cmp_type;
	int *array;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s NUM_OF_ELEMENTS COMPARE_TYPE(0: ascending, 1: descending)\n", argv[0]);
		return 0;
	}

	num_elem = atoi(argv[1]);
	if(num_elem < 2){
		fprintf(stderr, "NUM_OF_ELEMENTS must be larger than 2\n");
		return 0;
	}

	cmp_type = atoi(argv[2]);
	if(cmp_type < 0 || cmp_type > 1){
		fprintf(stderr, "COMPARE_TYPE(0: ascending, 1: descending)\n");
		return 0;
	}

	printf("Array element num:%d\n", num_elem);
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
    printf("\n-----------------\n");

	// Quick sort with stack and compare function pointer
	if(cmp_type == 0){
		printf("Quick sort (ascending) starts.\n");
		quick_sort_cmp((void*)array, (size_t)num_elem, (size_t)sizeof(array[0]),\
						(int(*)(const void *, const void *))int_compare_ascending);
	}
	else if(cmp_type == 1){
		printf("Quick sort (descending) starts.\n");
		quick_sort_cmp((void*)array, (size_t)num_elem, (size_t)sizeof(array[0]),\
						(int(*)(const void *, const void *))int_compare_descending);
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
