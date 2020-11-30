#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printBoard(unsigned int charCount, bool *isCharFound, char *word) {
	unsigned int astCount = charCount;
	if (astCount < 7) {
		astCount += 7;
	}

	if((astCount - 7) % 2 != 0) {
		astCount += 1;
	}

	printf("\n\n\n");
	for (int i = 0; i < astCount; i++) {
		printf("*");
	}
	printf("\n");

	for(int i = 1; i <= (astCount - 7) / 2; i++) {
		printf(" ");
	}
	printf("HANGMAN\n");

	for (int i = 0; i < astCount; i++) {
		printf("*");
	}
	printf("\n");

	for(int i = 1; i <= (astCount - charCount) / 2; i++) {
		printf(" ");
	}
	for(int i = 0; i < charCount; i++) {
		if(isCharFound[i]) {
			printf("%c", word[i]);
		} else {
			printf("_");
		}
	}
	printf("\n\n\n\n");
}

void getGuess(char *var) {
	printf("Enter your guess: ");
	scanf(" %c", var);
}

bool checkValid(char try, char *word, bool *isFound, unsigned int charCount) {
	bool out = false;
	for (int i = 0; i < charCount; i++) {
		if (word[i] == try) {
			isFound[i] = true;
			out = true;
		}
	}
	return out;
}

bool isDone(bool *isFound, unsigned int charCount) {
	for (int i = 0; i < charCount; i++) {
		if (!isFound[i]) {
			return false;
		}
	}
	return true;
}

unsigned long getLines() {
	FILE *fp; 
	char filename[] = "words.txt"; 
	char c; 
	unsigned long lines = 0;
	
	fp = fopen(filename, "r"); 

	if (fp == NULL) { 
		printf("Could not open file %s", filename);
		return 0; 
	} else {
		for (c = getc(fp); c != EOF; c = getc(fp)) { 
			if (c == '\n') {
				lines += 1;
			}
		}
		fclose(fp);
		return lines;
	}
}

char *getWord() {
	srand(time(0));

	unsigned long lines = getLines(&lines);
	unsigned long lineNr = (rand() % lines) + 1;;

	char * buffer = NULL;
	size_t line_buf_size = 0;
	int line_count = 0;
	ssize_t line_size;
	FILE *fp = fopen("words.txt", "r");

	line_size = getline(&buffer, &line_buf_size, fp);

	while (line_size >= 0) {
		if(line_count == lineNr) {
			break;
		}
		line_count++;
		line_size = getline(&buffer, &line_buf_size, fp);
	}

	fclose(fp);
	return buffer;
}

void removeChar(char *str, char garbage) {
	char *src, *dst;
	for (src = dst = str; *src != '\0'; src++) {
		*dst = *src;
		if (*dst != garbage) dst++;
	}
	*dst = '\0';
}