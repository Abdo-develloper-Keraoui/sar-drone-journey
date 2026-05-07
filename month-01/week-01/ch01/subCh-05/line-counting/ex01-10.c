#include <stdio.h>

int main(void) 
{

	/*Exercise 1-10. Write a program to copy its input to its output, replacing each tab by \t, each
	backspace by \b, and each backslash by \\. This makes tabs and backspaces visible in an
	unambiguous way.
	*/
	int c;

	

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			putchar('\\');
			putchar('t');
			continue;
		}
		if (c == ' ') {
			putchar('#');
			continue;
		}
		putchar(c);
			
	}

	
	return 0;
}
