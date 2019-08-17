//Hanoi Tower without recursive function

#include <stdio.h>
#include "HanoiStack.h"

void hanoi_tower(HanoiStack* stk)
{
	Hanoi hanoi;		//Hanoi tower struct
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

int main(void)
{
	int n;			//Num of disks
	HanoiStack stk;	//Stack
	Hanoi hanoi;		//Hanoi tower struct
	Initialize(&stk, 100);

	printf("Hanoi Tower\nNum of disk: ");
	scanf("%d", &n);
	hanoi.num = n;
	hanoi.from = 'A';
	hanoi.work = 'B';
	hanoi.dest = 'C';
	Push(&stk, hanoi);

	printf("Disks are moved from %c through %c to %c\n", hanoi.from, hanoi.work, hanoi.dest);
	hanoi_tower(&stk);

	printf("Hanoi Tower move finished.\n");
	Terminate(&stk);
	return 0;
}
