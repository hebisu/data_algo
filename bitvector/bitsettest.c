////////////////////////////////////////////////////////
// Integer set calculation with bit vector (test app)
// Created by Hiro Ebisu
////////////////////////////////////////////////////////
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "BitSet.h"

enum { ADD, REMOVE, SEARCH };

// Read data with scanf
int scan_data(int method)
{
	int data;

	switch (method) {
		case ADD:
			printf("Data to add:");
			break;
		case REMOVE:
			printf("Data to remove:");
			break;
		case SEARCH:
			printf("Data to search:");
			break;
	}
	scanf("%d", &data);

	return data;
}

int main(void)
{
	BitSet s1 = BitSetNull;
	BitSet s2 = BitSetNull;

	while (1) {
		int menu, x, idx;

		printf("s1 = ");   PrintLn(s1);
		printf("s2 = ");   PrintLn(s2);
		printf("(1)Add to s1 (2)Remove from s1 (3)Search from s1 (4)s1 <- s2 (5)Logical operations\n"
				"(6)Add to s2 (7)Remove from s2 (8)Search from s2 (9)s2 <- s1 (0)Exit\n"
				"Type command number:");
		scanf("%d", &menu);

		if (menu == 0) break;

		switch (menu) {
		case 1:
			x = scan_data(ADD);
			Add(&s1, x);
			break;

		case 2:
			x = scan_data(REMOVE);
			Remove(&s1, x);
			break;

		case 3:
			x = scan_data(SEARCH);
			idx = IsMember(s1, x);
			printf("%d is %s included in s1.\n", x, idx != 0 ? "" : "not");
			break;

		case 4:
			s1 = s2;
			break;

		case 5:
			printf("s1 == s2 = %s\n", s1 == s2 ? "true" : "false");
			printf("s1 & s2 = ");  PrintLn(s1 & s2);
			printf("s1 | s2 = ");  PrintLn(s1 | s2);
			printf("s1 - s2 = ");  PrintLn(s1 & ~s2);
			printf("s1 ^ s2 = ");  PrintLn(s1 ^ s2);
			break;

		case 6:
			x = scan_data(ADD);
			Add(&s2, x);
			break;

		case 7:
			x = scan_data(REMOVE);
			Remove(&s2, x);
			break;

		case 8:
			x = scan_data(SEARCH);
			idx = IsMember(s2, x);
			printf("%d is %s included in s2.\n", x, idx != 0 ? "" : "not");
			break;

		case 9:
			s2 = s1;
			break;
		} // End of switch(menu)
	} // End of while(1)

	return 0;
}
