#include <stdio.h>

int main(void) 
{
	float fahr, celsius;

	float lower, upper, step;//these are celsius!!

	upper = 150.0;
	lower = -30.0;
	step = 3.0;

	celsius = lower;
	printf("celsius\tfahr\n");
	
	while(celsius <= upper) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%3.2f\t%3.2f\n", celsius, fahr);
		celsius = celsius + step;	
	}
	return 0;
}
