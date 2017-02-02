#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "BST.h"


char *getWord (FILE *fp) {
	char word[100];
	int ch;
	size_t idx;

	for (idx = 0; idx < sizeof word - 1;) {
		ch = fgetc(fp);
		if (ch == EOF) break;
		if (!isalpha(ch)) {
			if (!idx) continue; // Nothing read yet; skip this character
			else break; // we are beyond the current word
		}
		word[idx++] = tolower(ch);
	}
	if (!idx) return NULL; // No characters were successfully read
	word[idx] = '\0';
	return strdup(word);
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
	treeToMathematica(wordTree);
	destroyTree(wordTree);

	fclose(wordFile);
	return (0);
}
