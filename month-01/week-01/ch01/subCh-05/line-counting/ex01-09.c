#include <stdio.h>

int main(void) 
{

	//Exercise 1-9. Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank

	int c, blanks;


	blanks = 0;
	

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			blanks++;
			continue;
		}
		if (blanks >= 1) {
			putchar('#');
			blanks = 0;
		}
		putchar(c);
		
	}

	
	return 0;
}
