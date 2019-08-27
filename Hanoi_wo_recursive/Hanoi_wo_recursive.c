////////////////////////////////////////////////////////
// Hanoi Tower without recursive function
// Created by Hiro Ebisu
////////////////////////////////////////////////////////
#include <stdio.h>
#include "HanoiStack.h"
#include "gettime.h"

#define MAX_DISK 100

void hanoi_tower(HanoiStack* stk)
{
	Hanoi hanoi;	//Hanoi tower struct
	char temp;		//to swap tower
	int cnt = 1;	//Disk move count
//	int loop = 0;

	while(!IsEmpty(stk)){
		// printf("Loop: %d\n", loop++);
		Peek(stk, &hanoi);
		// printf("hanoi.num:%d\n", hanoi.num);
		if(hanoi.num > 2){
			hanoi.num--;
			temp = hanoi.work;
			hanoi.work = hanoi.dest;
			hanoi.dest = temp;
			Push(stk, hanoi); //from, dest, work
		}
		else if(hanoi.num == 2){
			printf("Count:%d Disk is moved from %c through %c to %c\n", cnt++, hanoi.from, hanoi.dest, hanoi.work);
			printf("Count:%d Disk is moved from %c through %c to %c\n", cnt++, hanoi.from, hanoi.work, hanoi.dest);
			printf("Count:%d Disk is moved from %c through %c to %c\n", cnt++, hanoi.work, hanoi.from, hanoi.dest);
			Pop(stk, &hanoi);
			if(!IsEmpty(stk)){
				Peek(stk, &hanoi);
				hanoi.num = 1;
				Push(stk, hanoi); //from, dest, work
			}
		}
		else if(hanoi.num == 1){
			printf("Count:%d Disk is moved from %c through %c to %c\n", cnt++, hanoi.from, hanoi.work, hanoi.dest);
			if(Size(stk) > 1){
				// printf("Size(stk):%d\n", Size(stk));
				Pop(stk, &hanoi);
				Pop(stk, &hanoi);
				hanoi.num--;
				temp = hanoi.from;
				hanoi.from = hanoi.work;
				hanoi.work = temp;
				Push(stk, hanoi); //work, from, dest
			}
			else{
				printf("Clear stack\n");
				Clear(stk);
			}
		}
	}
	printf("Disk move count:%d\n", cnt - 1);
}

int main(int argc, char *argv[])
{
	HanoiStack stk;	//Stack
	Hanoi hanoi;	//Hanoi tower struct
    double start_time;
    double process_time;

	if(Initialize(&stk, MAX_DISK) < 0){
		fprintf(stderr, "Failed to initialize stack.\n");
		return 0;
	}

	if (argc != 2) {
		fprintf(stderr, "Usage: %s NUM_OF_ELEMENTS\n", argv[0]);
		return 0;
	}

	int num_disk = atoi(argv[1]); //Num of disks
	if(num_disk < 1 || MAX_DISK < num_disk){
		fprintf(stderr, "NUM_OF_ELEMENTS must be larger than 1 and smaller than 100\n");
		return 0;
	}

	printf("Hanoi Tower\n");
	hanoi.num = num_disk;
	hanoi.from = 'A';
	hanoi.work = 'B';
	hanoi.dest = 'C';
	Push(&stk, hanoi);

	printf("Disks are moved from %c through %c to %c\n", hanoi.from, hanoi.work, hanoi.dest);
	start_time = gettime();
	hanoi_tower(&stk);
	process_time = (gettime() - start_time) * 1000; // sec to msec
	printf("Process time:  %8.8f [msec]\n", process_time);

	printf("Hanoi Tower move finished.\n");
	Terminate(&stk);
	return 0;
}
