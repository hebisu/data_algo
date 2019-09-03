////////////////////////////////////////////////////////
// Counting sort algorithm
// Created by Hiro Ebisu
////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "gettime.h"

#define MIN_MAX_VALUE 1
#define MAX_MAX_VALUE 999999

int fsort(int array[], int num_elem, int max)
{
	int i;
	int *count_buf = calloc(max + 1, sizeof(int)); // Total counting buffer
	if(!count_buf){
		fprintf(stderr, "Failed to calloc\n");
		return -1;
	}

	int *temp_buf = calloc(num_elem, sizeof(int)); // Working buffer
	if(!temp_buf){
		fprintf(stderr, "Failed to calloc\n");
		return -1;
	}

	for (i = 0; i < num_elem; i++) count_buf[array[i]]++;			  // Count up
	for (i = 1; i <= max; i++) count_buf[i] += count_buf[i - 1];	  // Cumulative sum
	for (i = num_elem - 1; i >= 0; i--) temp_buf[--count_buf[array[i]]] = array[i];	  // Sorting
	if(memmove(array, temp_buf, sizeof(int) * num_elem) == NULL){	// Copy temp_buf to array
		fprintf(stderr, "Failed to memmove\n");
		return -1;
	}

	if(temp_buf) free(temp_buf);
	if(count_buf) free(count_buf);

	return 0;
}

int main(int argc, char *argv[])
{
	int i;
	int *array;
    double start_time;
    double process_time;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s NUM_OF_ELEMENTS MAX_VALUE\n", argv[0]);
		return 0;
	}

	int num_elem = atoi(argv[1]);
	if(num_elem < 2){
		fprintf(stderr, "NUM_OF_ELEMENTS must be larger than 2\n");
		return 0;
	}

	int max = atoi(argv[2]);
	if(max < MIN_MAX_VALUE || MAX_MAX_VALUE < max){
		fprintf(stderr, "MAX_VALUE must be from 1 to 999999\n");
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
        array[i] = rand() % max; // 0 - num_elem
        printf("%d, ", array[i]);
    }
    printf("\n-----------------\n");

	start_time = gettime();
	if(fsort(array, num_elem, max) < 0){
		fprintf(stderr, "Failed to fsort\n");
		return 0;
	}
	process_time = (gettime() - start_time) * 1000; // sec to msec

	printf("Sorted.\n");
	printf("Process time:  %8.8f [msec]\n", process_time);

	for (i = 0; i < num_elem; i++)
		printf("x[%d] = %d\n", i, array[i]);

	if(array){
		free(array);
	}

	return 0;
}
