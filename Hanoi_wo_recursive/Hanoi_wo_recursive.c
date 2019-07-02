//Hanoi Tower without recursive function

#include <stdio.h>
#include "HanoiStack.h"

void hanoi(HanoiStack* stk)
{
	Hanoi x;		//Hanoi tower struct
	char temp;		//to swap tower
	int cnt = 1;	//Disk move count
//	int loop = 0;

	while(!IsEmpty(stk)){
		// printf("Loop: %d\n", loop++);
		Peek(stk, &x);
		// printf("x.num:%d\n", x.num);
		if(x.num > 2){
			x.num--;
			temp = x.work;
			x.work = x.dest;
			x.dest = temp;
			Push(stk, x); //from, dest, work
		}
		else if(x.num == 2){
			printf("Count:%d Disk is moved from %c through %c to %c\n", cnt++, x.from, x.dest, x.work);
			printf("Count:%d Disk is moved from %c through %c to %c\n", cnt++, x.from, x.work, x.dest);
			printf("Count:%d Disk is moved from %c through %c to %c\n", cnt++, x.work, x.from, x.dest);
			Pop(stk, &x);
			if(!IsEmpty(stk)){
				Peek(stk, &x);
				x.num = 1;
				Push(stk, x); //from, dest, work
			}
		}
		else if(x.num == 1){
			printf("Count:%d Disk is moved from %c through %c to %c\n", cnt++, x.from, x.work, x.dest);
			if(Size(stk) > 1){
				// printf("Size(stk):%d\n", Size(stk));
				Pop(stk, &x);
				Pop(stk, &x);
				x.num--;
				temp = x.from;
				x.from = x.work;
				x.work = temp;
				Push(stk, x); //work, from, dest
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
	Hanoi x;		//Hanoi tower struct
	Initialize(&stk, 100);

	printf("Hanoi Tower\nNum of disk: ");
	scanf("%d", &n);
	x.num = n;
	x.from = 'A';
	x.work = 'B';
	x.dest = 'C';
	Push(&stk, x);

	printf("Disks are moved from %c through %c to %c\n", x.from, x.work, x.dest);
	hanoi(&stk);

	printf("Hanoi Tower move finished.\n");
	Terminate(&stk);
	return 0;
}
