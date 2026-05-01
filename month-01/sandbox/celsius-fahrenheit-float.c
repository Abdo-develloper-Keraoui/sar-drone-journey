#include <stdio.h>

int main(void) {
	float fahr, celsius;

	float lower, upper, step;

	int numberOfValues; 
	
	lower = -272.15; //1 Kelvin above absolute zero lowest temp in the universe
	upper = 56.7025;//highest recorded temperature on earth; added those *025 so for precision to get actaully 20 values, i don't know how exactly but i put it together 
	numberOfValues = 20;
	step = (upper - lower) / (numberOfValues - 1); // to get exactly 20 values for example 

	celsius = lower;
	int counter = 0;
	printf("Celsius\tFahr\n");

	while(celsius <= upper) {
		counter++;
		fahr = (9.0/5.0) * celsius + 32.0; 
		printf("%3.2f\t%6.2f\n", celsius, fahr);
		celsius += step;
	}
	printf("%f\n", celsius);
	printf("%d\n", counter);

	return 0;
}
