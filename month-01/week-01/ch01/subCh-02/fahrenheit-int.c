#include <stdio.h>

int main(void)
{
	int fahr, celsius; // declaration of the variables
	int lower, upper, step;

	lower = 0; 
	upper = 300; 
	step = 20;

	fahr = lower;
	while(fahr <= upper) {
		celsius = (5 * (fahr - 32)) / 9; //the formula must be in this formula because it is a integer divison that uses truncation and stuff
		printf("%d\t%d\n", fahr, celsius);
		fahr = fahr + step;
	}
	


	return 0;
}
