////////////////////////////////////////////////////////
// Binary insertion sort algorithm
// Created by Hiro Ebisu
////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gettime.h"

// Find the insertion target with binary search
int binary_search(const int array[], const int num_elements, const int target, const int print_process)
{
	int ptr_left = 0;			//Search left
	int ptr_right = num_elements - 1;		//Search right
	int ptr_centre;				//Search centre

	if(target >= array[ptr_right])
		return num_elements; //No insertion
	else if(target <= array[ptr_left])
		return 0; //Insert to [0]

	// Draw progress
	if(print_process){
		printf("   |");
		for(int i = 0; i < num_elements; i++){
			printf("   %d",i);
		}
		printf("\n");
		printf("---+");
		for(int i = 0; i < num_elements; i++){
			printf("----");
		}
		printf("\n");
	}

	do {
		ptr_centre = (ptr_left + ptr_right) / 2;

		// Draw progress
		if(print_process){
	        printf("   |");
	        for (int j = 0; j < ptr_left; j++){
				printf("    ");
			}
	        printf("  <-");
	        for (int j = 0; j < ptr_centre - ptr_left - 1; j++){
				printf("    ");
			}
	        printf("   +");
	        for (int j = 0; j < ptr_right - ptr_centre - 1; j++){
				printf("    ");
			}
	        printf("  ->\n");

	        printf("  %d|", ptr_centre);
			for (int j = 0; j < num_elements; j++){
				printf("   %d", array[j]);
			}
			printf("\n");
			printf("   |");
			for (int j = 0; j < num_elements; j++){
				printf("    ");
			}
			printf("\n");
		}

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
int insertion_sort(int array[], const int num_elements, const int print_process)
{
	int i, j, tmp = 0, target = 0;

	for (i = 1; i < num_elements; i++) {
		//Draw number
		if(print_process){
			for (j = 0; j < num_elements; j++)
				printf(" %d", array[j]);
	        printf("\n");
		}
        //Insert
		tmp = array[i];

		// Find the insertion target with binary search
		target = binary_search(array, i, tmp, print_process);

		// Use memmove for faster process
        if(memmove(&array[target + 1], &array[target], sizeof(int) * (i - target)) == NULL){
            fprintf(stderr, "Failed to memmove\n");
            return -1;
        }
		array[target] = tmp;

        // Draw area mark
		if(print_process){
	        for (j = 0; j < num_elements; j++){
	            if(j < target)
					printf("  ");
	            else if(j == target)
					printf("^-");
	            else if(j > target && j < i)
					printf("--");
	            else if(j == i)
					printf("-+");
        	}
        printf("\n");
		}
	}
    return 0;
}

int main(int argc, char *argv[]){
	int i;
	int *array;
    double start_time;
    double process_time;

	printf("Binary insertion sort\n");
	if (argc != 3) {
		fprintf(stderr, "Usage: %s NUM_OF_ELEMENTS PRINT_SORT_PROCESS(0:no, 1:yes)\n", argv[0]);
		return 0;
	}

	int num_elem = atoi(argv[1]);
	if(num_elem < 2){
		fprintf(stderr, "NUM_OF_ELEMENTS must be larger than 2\n");
		return 0;
	}

	int print_process = atoi(argv[2]);
	if(print_process < 0 || print_process > 1){
		fprintf(stderr, "PRINT_SORT_PROCESS(0:no, 1:yes)\n");
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
        if(print_process) printf("%d, ", array[i]);
    }
    if(print_process) printf("\n-----------------\n");

	start_time = gettime();
	if(insertion_sort(array, num_elem, print_process) < 0){
        printf("Failed to insert sort.\n");
        return 0;
    }
	process_time = (gettime() - start_time) * 1000; // sec to msec

	printf("Sorted.\n");
	printf("Process time:  %8.8f [msec]\n", process_time);

	for (i = 0; i < num_elem; i++)
		printf("array[%d] = %d\n", i, array[i]);

	if(array){
		free(array);
	}

	return 0;
}
