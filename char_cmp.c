////////////////////////////////////////////////////////
// String comparison algorithm
// Created by Hiro Ebisu
////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Compare strings to end
int str_cmp(const char *str1, const char *str2)
{
	while (*str1 == *str2) {
		if (*str1 == '\0') // Equal to end
			return 0;
		str1++;
		str2++;
	}
	return (unsigned char)*str1 - (unsigned char)*str2;
}

// Compare strings to end
// Not distinguish upper and lower case
int str_cmpic(const char *str1, const char *str2)
{
	while (tolower((int)(*str1)) == tolower((int)(*str2))) {
		if (*str1 == '\0') // Equal to end
			return 0;
		str1++;
		str2++;
	}
	return (unsigned char)tolower((int)(*str1)) - (unsigned char)tolower((int)(*str2));
}

// Compare n characters of 2 strings
int str_ncmp(const char *str1, const char *str2, size_t n)
{
	while (n > 0 && *str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2)
			return (unsigned char)*str1 - (unsigned char)*str2;
		str1++;
		str2++;
        n--;
	}
    if(n <= 0) // str1 and str2 are same to n
    	return 0;
    else if (*str1 == '\0' && *str2 == '\0') // str1 and str2 are same to end
        return 0;
    else if (*str1 == '\0') // str1 is shorter than str2
        return -1;
    else // *str2 == '\0',  str2 is shorter than str1
        return 1;
}

// Compare n characters of 2 strings
// Not distinguish upper and lower case
int str_ncmpic(const char *str1, const char *str2, size_t n)
{
	while (n > 0 && *str1 != '\0' && *str2 != '\0') {
		if (tolower((int)(*str1)) != tolower((int)(*str2)))
			return (unsigned char)tolower((int)(*str1)) - (unsigned char)tolower((int)(*str2));
		str1++;
		str2++;
        n--;
	}
    if(n <= 0) // str1 and str2 are same to n
    	return 0;
    else if (*str1 == '\0' && *str2 == '\0') // str1 and str2 are same to end
        return 0;
    else if (*str1 == '\0') // str1 is shorter than str2
        return -1;
    else // *str2 == '\0',  str2 is shorter than str1
        return 1;
}

int main(int argc, char *argv[])
{
	char *str1;
	char *str2;
    int num_char;
    int upper_lower;

	if (argc != 5) {
		fprintf(stderr, "Usage: %s String1 String2 Num_character(0:all) Does_distinguish_upper_lower(0:yes, 1:no)\n", argv[0]);
		return 0;
	}

    str1 = argv[1]; // String 1
    if(!str1){
        fprintf(stderr, "String1 NULL\n");
		return 0;
    }
    if(strlen(str1) < 1){
		fprintf(stderr, "String1 must be longer than 1 character\n");
		return 0;
	}

    str2 = argv[2]; // String 2
    if(!str2){
        fprintf(stderr, "String2 NULL\n");
		return 0;
    }
    if(strlen(str2) < 1){
		fprintf(stderr, "String2 must be longer than 1 character\n");
		return 0;
	}

	num_char = atoi(argv[3]); // Number of character to compare
	if(num_char < 0){
		fprintf(stderr, "Num_character(0:all)\n");
		return 0;
	}

    upper_lower = atoi(argv[4]); // Distinguish upper and lower case?
	if(upper_lower < 0 || 1 < upper_lower ){
		fprintf(stderr, "Does_distinguish_upper_lower(0:yes, 1:no)\n");
		return 0;
	}

    if(upper_lower == 0){ // Distinguish upper and lower case
        if(num_char == 0)
	        printf("str_cmp(%s, %s) = %d\n", str1, str2, str_cmp(str1, str2));
        else
            printf("str_cmp(%s, %s) = %d\n", str1, str2, str_ncmp(str1, str2, num_char));
    }
    else{
        if(num_char == 0) // Not distinguish upper and lower case
	        printf("str_cmp(%s, %s) = %d\n", str1, str2, str_cmpic(str1, str2));
        else
            printf("str_cmp(%s, %s) = %d\n", str1, str2, str_ncmpic(str1, str2, num_char));
    }

	return 0;
}
