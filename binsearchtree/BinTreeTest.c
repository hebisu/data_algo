////////////////////////////////////////////////////////
// Binary search tree algorithm tesp app
////////////////////////////////////////////////////////

#include <stdio.h>
#include "Member.h"
#include "BinTree.h"

// Menu
typedef enum {
	TERMINATE, ADD, REMOVE, SEARCH, MIN, MAX, PRINT, PRINTR
} Menu;

Menu SelectMenu(void)
{
	int menu;

	do {
		printf("\n(1)Insert (2)Remove (3)Search (4)Min (5)Max (6)Print (7)PrintR (0)Exit: ");
		scanf("%d", &menu);
	} while (menu < TERMINATE || menu > PRINTR);
	return (Menu)menu;
}

int main(void)
{
	Menu    menu;
	BinNode *root = NULL; // Root pointer to binary search tree

	do {
		Member x;
		BinNode *temp;

		switch (menu = SelectMenu()) {

		case ADD:
			x = ScanMember("Insert", MEMBER_NO | MEMBER_NAME);
			root = Add(root, &x);
			if(!root)
				fprintf(stderr, "Failed to Add\n");
			break;

		case REMOVE:
			x = ScanMember("Remove", MEMBER_NO);
			if(Remove(&root, &x) < 0)
				fprintf(stderr, "Failed to Remove\n");
			break;

		case SEARCH:
			x = ScanMember("Search", MEMBER_NO);
			if ((temp = Search(root, &x)) != NULL)
				PrintLnMember(&temp->data);
			break;

		case MIN:
			puts("Minimum node");
			temp = GetMinNode(root);
			PrintLnMember(&temp->data);
			break;

		case MAX:
			puts("Maximum node");
			temp = GetMaxNode(root);
			PrintLnMember(&temp->data);
			break;

		case PRINT:
			puts("Node list");
			PrintTree(root);
			break;

		case PRINTR:
			puts("Node list (reverse)");
			PrintTreeReverse(root);
			break;
		}
	} while (menu != TERMINATE);

	FreeTree(root);

	return 0;
}
