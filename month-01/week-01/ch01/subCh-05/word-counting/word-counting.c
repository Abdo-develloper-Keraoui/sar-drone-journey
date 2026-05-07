#include <stdio.h>


#define IN 1
#define OUT 0

/* count lines, words, and characters in input */
/*
How does the program work ?? count the lines, words and characters??

so to count lines is obvious '\n', to count chars 'as long as c != EOF then it is a char no matter what'
but words, it starts when there is a word?? what is a word in the loose sense ??

 "a word is any sequence of characters that does not contain a blank, tab or newline"

---- We start by defining an IN and OUT constants 
afterwards we get the loop going by doing the c getchar thingy 

Every time the program encounters the first character of a word, it counts one more word. The
variable state records whether the program is currently in a word or not; initially it is ``not in
a word'', which is assigned the value OUT.
*/


int main(void) {

	int c, numLines, numChars, numWords, state;


	//initialize your variables my dude 
	numLines = 0;
	numChars = 0;
	numWords = 0; 
	
	state = OUT;
	while((c = getchar()) != EOF) {
		numChars++;

		if(c == '\n') {
			numLines++;
		}
		
		if((c == ' ') || (c == '\n') || (c == '\t')) {
			state = OUT;
		} 
		else if(state == OUT) {
			state = IN;
			numWords++;
		}
	}

	printf("%d \t %d \t %d\n", numChars, numWords, numLines);
	return 0;
}
