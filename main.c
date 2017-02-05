#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) // if in a windows environment path separator is '\'
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>
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

char *getOutputFileName (char *inputFileName) {
	char *filePart = basename(inputFileName);
	char *pathPart = dirname(inputFileName);

	char *word_input = strstr(filePart, "input");

	if (word_input != filePart) { // TODO: Check for .txt at the end
		fprintf(stderr, "ERROR: Input file name must start with \"input\".\n");
		return NULL;
	}

	size_t endOfWord_input = filePart - word_input + 5;
	char *indexAndFileExtension = filePart + endOfWord_input;

	// "myoutput" is 3 longer than "input" + 1 more for '\0' + 1 more for a possible '.' + 1 more for '/'
	char *outputFileName = (char *)malloc(strlen(inputFileName) + 6);
	sprintf(outputFileName, "%s%smyoutput%s", pathPart, PATH_SEPARATOR, indexAndFileExtension);
	return outputFileName;
}

int main (int argc, char *argv[]) {

	if (argc <= 1) {
		// Literals next to each other are effectively concatenated.
		printf("\nUsage: BST_CountWords <path/of/input_file>\n"
					   "The file name should be input*.txt where the expansion of * will be the index.\n"
					   "This same index will appear in the output file \"myoutput*.txt\".\n"
					   "You can pass a file name alone or a path to a file.\n"
					   "Output will be in the same directory as input.\n");
		return 1;
	}

	char *inputFileName = argv[1];

	char *outputFileName = getOutputFileName(inputFileName);
	if (outputFileName == NULL) {
		return 1;
	}

	Bst *wordTree = newBst();

	FILE *inputFile = fopen(inputFileName, "r");
	// TODO: handle missing file

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
