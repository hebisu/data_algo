#include <stdio.h>
#include <stdlib.h>

#define MAX_MONTH 12
#define MAX_DATE 31

int prime_judge(int num){
	if(num < 2) return 0;	//Not a prime number
	for(int i = 2; i < num; ++i ) if( num % i == 0 ) return 0;	//Not a prime number
	return 1;	//A prime number
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
	int h_mon, h_day, w_mon, w_day;

	for(h_mon = 1; h_mon <= MAX_MONTH; h_mon++){
		if(prime_judge(h_mon) == 0) continue;//1. My wife's month of birth is a prime number, so is mine.
		for(w_mon = 1; w_mon <= MAX_MONTH; w_mon++){
			if(prime_judge(w_mon) == 0) continue;//1. My wife's month of birth is a prime number, so is mine.
			for(h_day = 1; h_day <= MAX_DATE; h_day++){
				if(prime_judge(h_day) == 0) continue;//2. Her day of birth is a prime number, so is mine.
				for(w_day = 1; w_day <= MAX_DATE; w_day++){
					if(prime_judge(w_day) == 0) continue;//2. Her day of birth is a prime number, so is mine.
					if(prime_judge(sum_all_digits(w_mon, w_day)) == 0) continue;//3. The sum of all the digits in her month and day of birth is a prime number, so is mine.
					if(prime_judge(sum_all_digits(h_mon, h_day)) == 0) continue;//3. The sum of all the digits in her month and day of birth is a prime number, so is mine.
					if(prime_judge(connect_all_digits(w_mon, w_day)) == 0) continue;//4. Connect her month of birth with her day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime. For example, if her birthday were January 23, then the connection would lead to the number 123 and reversing all the digits, you would get 321.
					if(prime_judge(connect_all_digits_reverse(w_mon, w_day)) == 1) continue;//4. Connect her month of birth with her day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime. For example, if her birthday were January 23, then the connection would lead to the number 123 and reversing all the digits, you would get 321.
					if(prime_judge(connect_all_digits(h_mon, h_day)) == 0) continue;//5. Connect my month of birth with my day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(prime_judge(connect_all_digits_reverse(h_mon, h_day)) == 1) continue;//5. Connect my month of birth with my day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(prime_judge(connect_all_digits(h_day, w_mon)) == 0) continue;//6. Connect my day of birth with her month of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(prime_judge(connect_all_digits_reverse(h_day, w_mon)) == 1) continue;//6. Connect my day of birth with her month of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(prime_judge(connect_all_digits(h_mon, w_day)) == 0) continue;//7. Connect my month of birth with her day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(prime_judge(connect_all_digits_reverse(h_mon, w_day)) == 1) continue;//7. Connect my month of birth with her day of birth, you get a prime number; but if you reverse all the digits, the number is not a prime.
					if(prime_judge(connect_all_digits(w_day, h_mon)) == 1) continue;//8. Connect her day of birth with my month of birth, you do NOT get a prime number; but if you reverse all the digits, the number is a prime.
					if(prime_judge(connect_all_digits_reverse(w_day, h_mon)) == 0) continue;//8. Connect her day of birth with my month of birth, you do NOT get a prime number; but if you reverse all the digits, the number is a prime.
					if(prime_judge(connect_all_digits(w_mon, h_day)) == 1) continue;//9. Connect her month of birth with my day of birth, you do NOT get a prime number; if you reverse all the digits, the number is NOT a prime either!
					if(prime_judge(connect_all_digits_reverse(w_mon, h_day)) == 1) continue;//9. Connect her month of birth with my day of birth, you do NOT get a prime number; if you reverse all the digits, the number is NOT a prime either!
					if(prime_judge(sum_all_digits(h_mon, h_day) - sum_all_digits(w_mon, w_day)) == 0) continue;//10.Well, things cannot too perfect, can it? So it looks like there is a "difference of a prime". That is true: the difference between the digit sum of my month and day of birth and the digit sum of hers, is a prime!
					printf("husband_month:%d, husband_date:%d, wife_month:%d, wife_date:%d\n", h_mon, h_day, w_mon, w_day);
					printf("Husband's birthday: %d/%d (MM/DD), Wife's birthday: %d/%d (MM/DD)\n", h_mon, h_day, w_mon, w_day);
				}
			}
		}
	}
	return 0;
}