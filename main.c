#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

int main() {
	char *buf = getWord();
	char *word = malloc((strlen(buf) - 1) * sizeof(char));
	int charCount;
	bool *isCharFound;
	unsigned short numberOfTries = 5;

	strcpy(word, buf);
	removeChar(word, '\n');
	charCount = strlen(word);
	
	isCharFound = malloc(sizeof(bool) * charCount);
	for (int i = 0; i < charCount; i++) {
		isCharFound[i] = false;
	}

	while (numberOfTries > 0) {
		char try
			;
		bool isValid;

		printBoard(charCount, isCharFound, word);

		printf("Number of tries left: %u\n", numberOfTries);
		getGuess(&try);
		isValid = checkValid(try, word, isCharFound, charCount);

		if (!isValid) {
			numberOfTries--;
		} else {
			if (isDone(isCharFound, charCount)) {
				break;
			}
		}
	}

	if (isDone(isCharFound, charCount)) {
		printBoard(charCount, isCharFound, word);
		printf("You won!");
	} else {
		printBoard(charCount, isCharFound, word);
		printf("You lost! Word: %s", word);
	}
	return 0;
}