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
	return strdup(thisWord); // strdup mallocs a string for me, I'll need to free it later
}

int main () {
	// words.txt has 100 unique words.
	// there are a total of 145 word occurrences.
	// the most times any word shows up is 4.
	Bst *wordTree = newBst();
	FILE *wordFile = fopen("words.txt", "r");

	char *word;
	while (word = getWord(wordFile)) {
		treeInsert(wordTree, word);
		free(word); // freeing the extra word that's been malloced in getWord.
	}
	fclose(wordFile);

	printf("\nWord Counts:\n");
	treePrint(wordTree);
	treeDestroy(wordTree);

	return (0);
}
