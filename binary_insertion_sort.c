//Binary insertion sort

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bin_search_ins(const int array[], int num_elements, int key)
{
	int pl = 0;			//Search left
	int pr = num_elements - 1;		//Search right
	int pc;				//Search centre

	if(key >= array[pr]){
		return num_elements; //No insertion
	}
	else if(key <= array[pl]){
		return 0; //Insert to [0]
	}

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

	do {
		pc = (pl + pr) / 2;

        //Show progress
        printf("   |");
        for (int j = 0; j < pl; j++){
			printf("    ");
		}
        printf("  <-");
        for (int j = 0; j < pc - pl - 1; j++){
			printf("    ");
		}
        printf("   +");
        for (int j = 0; j < pr - pc - 1; j++){
			printf("    ");
		}
        printf("  ->\n");

        printf("  %d|", pc);
		for (int j = 0; j < num_elements; j++){
			printf("   %d", array[j]);
		}
		printf("\n");
		printf("   |");
		for (int j = 0; j < num_elements; j++){
			printf("    ");
		}
		printf("\n");

		if (array[pc] == key){
			if (pc > 0) return pc;
		}
		else if (array[pc] < key){
			pl = pc + 1;
		}
		else{
			pr = pc - 1;
		}
	} while (pl <= pr);

	if(pc == pr){
		return pc + 1;
	}
	else{
		return pc;
	}
}

int insertion(int array[], int num_elements)
{
	int i, j, tmp = 0, target = 0;

	for (i = 1; i < num_elements; i++) {
        //Draw number
		for (j = 0; j < num_elements; j++){
			printf(" %d", array[j]);
		}
        putchar('\n');

        //Insert
		tmp = array[i];
		target = bin_search_ins(array, i, tmp);

        if(memmove(&array[target + 1], &array[target], sizeof(int) * (i - target)) == NULL){
            printf("Failed to memmove\n");
            return -1;
        }
		array[target] = tmp;

        // Draw area mark
        for (j = 0; j < num_elements; j++){
            if(j < target){
				printf("  ");
			}
            else if(j == target){
				printf("^-");
			}
            else if(j > target && j < i){
				printf("--");
			}
            else if(j == i){
				printf("-+");
			}
        }
        putchar('\n');
	}
    return 0;
}

int main(void)
{
	int i, num_elements;
	int *array;

	printf("Binary insertion sort\n");
	printf("Num:");
	scanf("%d", &num_elements);
	array = calloc(num_elements, sizeof(int));
	if(array == NULL){
		printf("Failed to calloc\n");
		return 0;
	}

	for (i = 0; i < num_elements; i++) {
		printf("array[%d] : ", i);
		scanf("%d", &array[i]);
	}

	if(insertion(array, num_elements) < 0){
        printf("Failed to insert sort.\n");
        return 0;
    }

	printf("Sorted.\n");
	for (i = 0; i < num_elements; i++){
		printf("array[%d] = %d\n", i, array[i]);
	}

	if(array != NULL){
		free(array);
	}

	return 0;
}
