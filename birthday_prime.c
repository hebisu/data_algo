#include <stdio.h>
#include <stdlib.h>

#define MAX_MONTH 12
#define MAX_DATE  31
#define PRIME     1
#define NOT_PRIME 0

int is_prime(int num){
	if(num < 2) return NOT_PRIME;	//Not a prime number
	for(int i = 2; i < num; ++i ) if( num % i == 0 ) return NOT_PRIME;	//Not a prime number
	return PRIME;	//A prime number
}

int sum_all_digits(int val1, int val2){
	int sum = 0;
	sum += val1 / 10;
	sum += val1 % 10;
	sum += val2 / 10;
	sum += val2 % 10;
	return sum;
}

int connect_all_digits(int val1, int val2){
	int connect = 0;
	connect += val2;
	if(val2 > 9) connect += val1 * 100;
	else connect += val1 * 10;
	return connect;
}

int connect_all_digits_reverse(int val1, int val2){
	int connect = 0;
	if(val1 > 9){ 
		connect += val1 / 10;
		connect += (val1 % 10) * 10;
		if(val2 > 9){
			connect += (val2 / 10) * 100;
			connect += (val2 % 10) * 1000;
		}
		else{
			connect += val2 * 100;
		}
	}
	else{
		connect += val1;
		if(val2 > 9){
			connect += (val2 / 10) * 10;
			connect += (val2 % 10) * 100;
		}
		else{
			connect += val2 * 10;
		}
	}
	return connect;
}

int main(int argc, char *argv[])
{
	int hus_mon, hus_day, wif_mon, wif_day;

	for(hus_mon = 1; hus_mon <= MAX_MONTH; hus_mon++){
		if(is_prime(hus_mon) == NOT_PRIME) continue;//1. My wife's month of birth is a prime number, so is mine.
		for(wif_mon = 1; wif_mon <= MAX_MONTH; wif_mon++){
			if(is_prime(wif_mon) == NOT_PRIME) continue;//1. My wife's month of birth is a prime number, so is mine.
			for(hus_day = 1; hus_day <= MAX_DATE; hus_day++){
				if(is_prime(hus_day) == NOT_PRIME) continue;//2. Her day of birth is a prime number, so is mine.
				for(wif_day = 1; wif_day <= MAX_DATE; wif_day++){
					if(is_prime(wif_day) == NOT_PRIME) continue;//2. Her day of birth is a prime number, so is mine.
					if(is_prime(sum_all_digits(wif_mon, wif_day)) == NOT_PRIME) continue;//3. The sum of all the digits in her month and day of birth is a prime number, so is mine.
					if(is_prime(sum_all_digits(hus_mon, hus_day)) == NOT_PRIME) continue;//3. The sum of all the digits in her month and day of birth is a prime number, so is mine.
					if(is_prime(connect_all_digits(wif_mon, wif_day)) == NOT_PRIME) continue;//4. Connect her month of birth with her day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime. For example, if her birthday were January 23, then the connection would lead to the number 123 and reversing all the digits, you would get 321.
					if(is_prime(connect_all_digits_reverse(wif_mon, wif_day)) == PRIME) continue;//4. Connect her month of birth with her day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime. For example, if her birthday were January 23, then the connection would lead to the number 123 and reversing all the digits, you would get 321.
					if(is_prime(connect_all_digits(hus_mon, hus_day)) == NOT_PRIME) continue;//5. Connect my month of birth with my day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(is_prime(connect_all_digits_reverse(hus_mon, hus_day)) == PRIME) continue;//5. Connect my month of birth with my day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(is_prime(connect_all_digits(hus_day, wif_mon)) == NOT_PRIME) continue;//6. Connect my day of birth with her month of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(is_prime(connect_all_digits_reverse(hus_day, wif_mon)) == PRIME) continue;//6. Connect my day of birth with her month of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(is_prime(connect_all_digits(hus_mon, wif_day)) == NOT_PRIME) continue;//7. Connect my month of birth with her day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(is_prime(connect_all_digits_reverse(hus_mon, wif_day)) == PRIME) continue;//7. Connect my month of birth with her day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(is_prime(connect_all_digits(wif_day, hus_mon)) == PRIME) continue;//8. Connect her day of birth with my month of birth, you do NOT get a prime number; but if you reverse all the digits, the number is a prime.
					if(is_prime(connect_all_digits_reverse(wif_day, hus_mon)) == NOT_PRIME) continue;//8. Connect her day of birth with my month of birth, you do NOT get a prime number; but if you reverse all the digits, the number is a prime.
					if(is_prime(connect_all_digits(wif_mon, hus_day)) == PRIME) continue;//9. Connect her month of birth with my day of birth, you do NOT get a prime number; if you reverse all the digits, the number is NOT a prime either!
					if(is_prime(connect_all_digits_reverse(wif_mon, hus_day)) == PRIME) continue;//9. Connect her month of birth with my day of birth, you do NOT get a prime number; if you reverse all the digits, the number is NOT a prime either!
					if(is_prime(sum_all_digits(hus_mon, hus_day) - sum_all_digits(wif_mon, wif_day)) == NOT_PRIME) continue;//10.Well, things cannot too perfect, can it? So it looks like there is a "difference of a prime". That is true: the difference between the digit sum of my month and day of birth and the digit sum of hers, is a prime!
					printf("husband_month:%d, husband_date:%d, wife_month:%d, wife_date:%d\n", hus_mon, hus_day, wif_mon, wif_day);
					printf("Husband's birthday: %d/%d (MM/DD), Wife's birthday: %d/%d (MM/DD)\n", hus_mon, hus_day, wif_mon, wif_day);
				}
			}
		}
	}
	return 0;
}