//Binary insertion sort

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bin_search_ins(const int a[], int n, int key)
{
	int pl = 0;			//Search left
	int pr = n - 1;		//Search right
	int pc;				//Search centre

	if(key >= a[pr]){
		return n; //No insertion
	}
	else if(key <= a[pl]){
		return 0; //Insert to [0]
	}

	printf("   |");
	for(int i = 0; i < n; i++) printf("   %d",i);
	printf("\n");
	printf("---+");
	for(int i = 0; i < n; i++) printf("----");
	printf("\n");

	do {
		pc = (pl + pr) / 2;

        //Show progress
        printf("   |");
        for (int j = 0; j < pl; j++) printf("    ");
        printf("  <-");
        for (int j = 0; j < pc - pl - 1; j++) printf("    ");
        printf("   +");
        for (int j = 0; j < pr - pc - 1; j++) printf("    ");
        printf("  ->\n");

        printf("  %d|", pc);
		for (int j = 0; j < n; j++) printf("   %d", a[j]);
		printf("\n");
		printf("   |");
		for (int j = 0; j < n; j++) printf("    ");
		printf("\n");

		if (a[pc] == key){
			if (pc > 0) return pc;
		}
		else if (a[pc] < key)
			pl = pc + 1;
		else
			pr = pc - 1;
	} while (pl <= pr);

	if(pc == pr) return pc + 1;
	else return pc;
}

int insertion(int a[], int n)
{
	int i, k, tmp = 0, target = 0;

	for (i = 1; i < n; i++) {
        //Draw number
		for (k = 0; k < n; k++)	printf(" %d", a[k]);
        putchar('\n');

        //Insert
		tmp = a[i];
		target = bin_search_ins(a, i, tmp);

        if(memmove(&a[target + 1], &a[target], sizeof(int) * (i - target)) == NULL){
            printf("Failed to memmove\n");
            return -1;
        }
		a[target] = tmp;

        // Draw area mark
        for (k = 0; k < n; k++){
            if(k < target) printf("  ");
            else if(k == target) printf("^-");
            else if(k > target && k < i) printf("--");
            else if(k == i) printf("-+");
        }
        putchar('\n');
	}
    return 0;
}

int main(void)
{
	int i, nx;
	int *x;	//Array

	printf("Binary insertion sort\n");
	printf("Num:");
	scanf("%d", &nx);
	x = calloc(nx, sizeof(int));
	if(x == NULL){
		printf("Failed to calloc\n");
		return 0;
	}

	for (i = 0; i < nx; i++) {
		printf("x[%d] : ", i);
		scanf("%d", &x[i]);
	}

	if(insertion(x, nx) < 0){
        printf("Failed to insert sort.\n");
        return 0;
    }

	printf("Sorted.\n");
	for (i = 0; i < nx; i++)
		printf("x[%d] = %d\n", i, x[i]);

	if(x != NULL) free(x);

	return 0;
}
