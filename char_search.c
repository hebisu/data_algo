////////////////////////////////////////////////////////
// 1-character search algorithm
// Created by Hiro Ebisu
////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Search from top(left)
char *str_chr(const char *str, int c)
{
	int i = 0;
	c = (char)c;

	while (*str != c) {
		if (*str == '\0') //Search fail
			return NULL;
		str++;
	}
	return (char*)str; //Search seccess
}

// Search from bottom(right)
char *str_rchr(const char *str, int c)
{
	int idx = -1;
    int i = 0;
	c = (char)c;

	while (str[i] != '\0') {
        if(str[i] == c){
            idx = i;
        }
        i++;
	}

    if(idx < 0) //Search fail
    	return NULL;
    else
        return (char*)(str + idx); //Search seccess

}

int main(int argc, char *argv[])
{
	char *str;
	char *tmp;
    char *result;
	int  ch;
	int  idx;

	if (argc != 4) {
		fprintf(stderr, "Usage: %s String Search_character Search_from(0:left, 1:right)\n", argv[0]);
		return 0;
	}

    str = argv[1];
    if(!str){
        fprintf(stderr, "String NULL\n");
		return 0;
    }
    if(strlen(str) < 1){
		fprintf(stderr, "String must be longer than 1 character\n");
		return 0;
	}

    tmp = argv[2];
    if(!tmp){
        fprintf(stderr, "Search_character NULL\n");
		return 0;
    }
    if(strlen(tmp) != 1){
		fprintf(stderr, "Search_character must be 1 character\n");
		return 0;
	}
	ch = tmp[0];

	int lr = atoi(argv[3]);
	if(lr < 0 || 1 < lr){
		fprintf(stderr, "Search_from(0:left, 1:right)\n");
		return 0;
	}

    if(lr == 0)
        result = str_chr(str, ch);
    else
        result = str_rchr(str, ch);

	if (!result)
		printf("'%c' does not exist.\n", ch);
	else
		printf("'%c' exists. result=%c, index=%llu\n", ch, *result, result - str + 1);

	return 0;
}
