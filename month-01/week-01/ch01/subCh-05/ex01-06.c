#include <stdio.h>

int main(void) {
	/*
	Exercsise 1-6. Verify that the expression getchar() != EOF is 0 or 1.
	*/

	//it's ugly here but it works!!
	//the present second program in the file
	int c;

	while((c = getchar()) != EOF){
		printf("(getchar() != EOF) === %d\n", (c != EOF));
		putchar(c);
	}
	///(getchar() != EOF) === 1
		
	return 0;
}
