#include <stdio.h>

int main(void)
{
	float fahr, celsius; // declaration of the variables in float this time
	float lower, upper, step;

	lower = 0.0; 
	upper = 300.0; 
	step = 20.0;

	fahr = lower;

	printf("Fahr\tCelsius\n");
	while(fahr <= upper) {
		celsius = (5.0 / 9.0) * (fahr - 32.0); //the formula now can have the  (5.0/9.0) because it is not an integer divison any more, but 32.0 needs the 0 to be considred float for the human reader
		printf("%3.0f\t%6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
	


	return 0;
}
