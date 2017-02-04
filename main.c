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

int main (int argc, char *argv[]) {

	if (argc <= 1) {
		// Literals next to each other are effectively concatenated.
		printf("\nUsage: BST_CountWords <file_suffix>\n"
					   "The argument file_suffix specifies which input/output pair to use.\n"
					   "It is inserted into the file name in place of the X in 'inputX.txt' and 'outputX.txt'\n");
		return 1;
	}

	if (strlen(argv[1]) > 4) {
		printf("file_suffix can only be at most 4 characters long.");
		return 1;
	}

	char *inputPrefix = "input";
	char *inputFileName = (char *)malloc(strlen(inputPrefix) + 9);
	sprintf(inputFileName, "%s%s.txt", inputPrefix, argv[1]);

	char *outputPrefix = "myoutput";
	char *outputFileName = (char *)malloc(strlen(outputPrefix) + 9);
	sprintf(outputFileName, "%s%s.txt", outputPrefix, argv[1]);

	Bst *wordTree = newBst();

	FILE *inputFile = fopen(inputFileName, "r");
	char *word;
	while ((word = getWord(inputFile))) {
		treeInsert(wordTree, word);
		free(word); // freeing the extra word that's been malloced in getWord.
	}
	fclose(inputFile);

	FILE *outputFile = fopen(outputFileName, "w+");

	treeFPrint(outputFile, wordTree);
	fclose(outputFile);

	treeDestroy(wordTree);

	return (0);
}
