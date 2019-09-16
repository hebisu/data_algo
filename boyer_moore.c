////////////////////////////////////////////////////////
// String matching by Boyer-Moore algorithm
// Created by Hiro Ebisu
////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int init_skiptable(int *skip_table, const char pattern[], const int pattern_len, const int print_process){
    if(!skip_table){
        fprintf(stderr, "skip_table NULL\n");
		return -1;
    }
    if(!pattern){
        fprintf(stderr, "pattern NULL\n");
		return -1;
    }

	for (int i = 0; i <= UCHAR_MAX; i++)
		skip_table[i] = pattern_len;
	for (int i = 0; i < pattern_len - 1; i++)
		skip_table[pattern[i]] = pattern_len - i - 1;

	printf("Skip table created\n");
	if(print_process){
		for(int i = 0; i < UCHAR_MAX; i++){
	        if(skip_table[i] < pattern_len)
	            printf(" char:%c, skip_table[%03d], step:%d\n", (char)i, i, (int)skip_table[i]);
	    }
		printf("-----------------------------------\n");
	}

	return 0;
}

// Caluculate next position
int next_position(int *skip_table, const char key, const int nextstep){
	if(skip_table[(int)key] > nextstep)
		return skip_table[(int)key];
	else
		return nextstep;
}

void print_comparison_process(const char text[], const char pattern[], const int ptr_text, const int ptr_pattern, const int pattern_len){
// TODO print comparison process function
    if(!text){
        fprintf(stderr, "text NULL\n");
		exit(0);
    }
	if(!pattern){
        fprintf(stderr, "pattern NULL\n");
		exit(0);
    }

	for(int i = 0; i < ptr_text; i++)
		printf(" ");
	printf("*\n");
	printf("%s\n", text);
	for(int i = 0; i < ptr_text - ptr_pattern; i++)
		printf(" ");
	printf("%s\n", pattern);
	for(int i = 0; i < ptr_text; i++)
		printf(" ");
	printf("*\n");
	printf("\n");
}

int boyermoore_match(const char text[], const char pattern[], const int print_process)
{
	int text_len = strlen(text);
	int pattern_len = strlen(pattern);
	int skip_table[UCHAR_MAX + 1];		// Skip table
	int ptr_text = pattern_len - 1;		// Cursor to text (ptr_text starts from the end position of pattern)
	int ptr_pattern = pattern_len - 1;	// Cursor to pattern (Matching starts from the end character of pattern)
	int count = 0;

	// Initialize skip table
	if(init_skiptable(skip_table, pattern, pattern_len, print_process) < 0){
		fprintf(stderr, "skip_table NULL\n");
		return -1;
	}

	while (ptr_text < text_len) { // Continue to the end of text
		ptr_pattern = pattern_len - 1; // Matching starts from the end character of pattern

		while (text[ptr_text] == pattern[ptr_pattern]) {
			if(print_process) print_comparison_process(text, pattern, ptr_text, ptr_pattern, pattern_len);
			if (ptr_pattern == 0){ // Pattern matches a part of text
				printf("Total comparison count:%d\n", count);
				return ptr_text;
			}
			ptr_pattern--;
			ptr_text--;
			count++;
		}
		count++;

		if(print_process) print_comparison_process(text, pattern, ptr_text, ptr_pattern, pattern_len);

		// Move text pointer to the next position
		ptr_text += next_position(skip_table, text[ptr_text], pattern_len - ptr_pattern);
	}

	printf("Total comparison count:%d\n", count);
	return -1; // Pattern does not match any part of text
}

int main(int argc, char *argv[])
{
	char *text;
	char *pattern;
    int  idx;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s text pattern print_process(0:no, 1:yes)\n", argv[0]);
		return 0;
	}

    text = argv[1];
    if(!text){
        fprintf(stderr, "text NULL\n");
		return 0;
    }
    if(strlen(text) < 1){
		fprintf(stderr, "text must be longer than 1 character\n");
		return 0;
	}

    pattern = argv[2];
    if(!pattern){
        fprintf(stderr, "pattern NULL\n");
		return 0;
    }
    if(strlen(pattern) < 1){
		fprintf(stderr, "pattern must be longer than 1 character\n");
		return 0;
	}

	int print = atoi(argv[3]);
	if(print < 0 || 1 < print){
		fprintf(stderr, "print_process(0:no, 1:yes)\n");
		return 0;
	}

	idx = boyermoore_match(text, pattern, print);

	if (idx < 0)
		printf("%s does not included in %s\n", pattern, text);
	else
		printf("%s is matched at %d in %s\n", pattern, idx + 1, text);

	return 0;
}
