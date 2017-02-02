#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "BST.h"


char *getWord (FILE *filePointer) {
	char thisWord[100];
	int currentChar;
	size_t charIndex;

	for (charIndex = 0; charIndex < sizeof(thisWord) - 1;) {
		currentChar = fgetc(filePointer);
		if (currentChar == EOF) break;
		if (!isalpha(currentChar)) {
			if (!charIndex) continue; // Nothing read yet; skip this character
			else break; // we are beyond the current word
		}
		thisWord[charIndex++] = (char)tolower(currentChar);
	}
	if (!charIndex) return NULL; // charIndex still 0, no characters were successfully read
	thisWord[charIndex] = '\0';
	return strdup(thisWord);
}

int main () {
	// words.txt has 100 unique words.
	// there are a total of 145 word occurrences.
	// the most times any word shows up is 4.
	FILE *wordFile = fopen("words.txt", "r");
	Bst *wordTree = newBst();

	char *word;
	while (word = getWord(wordFile)) {
		incrementOrInsert(wordTree, word);
	}

	printf("\nWord Counts:\n");
	printTree(wordTree);
	destroyTree(wordTree);

	fclose(wordFile);
	return (0);
}
