#include <stdio.h>

int main(void) 
{

	//Exercise 1-8. Write a program to count blanks, tabs, and newlines.

	int c, blanks, tabs, newLines;


	blanks = 0;
	tabs = 0;
	newLines = 0;


	while((c = getchar()) != EOF) {
		if(c == ' ') {
			blanks++;
			continue;
		}
		if(c == '\t') {
			tabs++;
			continue;
		}
		if(c == '\n') {
			newLines++;
		}
	}


	printf("spaces/blanks: %d\t tabs: %d \t new lines: %d \n",blanks, tabs, newLines);

	
	return 0;
}
