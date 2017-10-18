#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>
#include "BST.h"

/* If a windows environment path separator is '\', else '/'. No NeXT ':' */
#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

/**
 * Gets each word one at a time from the file buffer
 * represented by filePointer.
 *
 * Retrieved from <http://stackoverflow.com/a/26359165> on 2017-02-02
 * vars renamed for clarity after retrieval.
 */
char *getWord (FILE *filePointer) {
  char thisWord[100];
  int currentChar;
  size_t charIndex;

  for (charIndex = 0; charIndex < sizeof(thisWord) - 1;) {
    currentChar = fgetc(filePointer);
    if (currentChar == EOF) break;
    if (!isalpha(currentChar)) {
      if (!charIndex) continue; /* Nothing read yet; skip this character */
      else break; /* We are beyond the current word */
    }
    thisWord[charIndex++] = (char)tolower(currentChar);
  }
  /* charIndex still 0, no characters were successfully read */
  if (!charIndex) return NULL;
  thisWord[charIndex] = '\0';
  /* strdup mallocs a string. the caller will need to free it later */
  return strdup(thisWord);
}

/**
 * Transforms the input filename to the corresponding output filename.
 * Also validates format of input filename.
 */
char *getOutputFileName (char *inputFileName) {
  char *filePart = basename(inputFileName);
  char *pathPart = dirname(inputFileName);

  char *word_input = strstr(filePart, "input");

  if (word_input != filePart) { /* TODO: Check for .txt at the end */
    fprintf(stderr, "ERROR: Input file name must start with \"input\".\n");
    return NULL;
  }

  size_t endOfWord_input = filePart - word_input + 5;
  char *indexAndFileExtension = filePart + endOfWord_input;

  /* "myoutput" is 3 longer than "input"
   * + 1 more for '\0' + 1 more for a possible '.' + 1 more for '/' */
  char *outputFileName = (char *)malloc(strlen(inputFileName) + 6);
  sprintf(outputFileName, "%s%smyoutput%s",
          pathPart, PATH_SEPARATOR, indexAndFileExtension);
  return outputFileName;
}

int main (int argc, char *argv[]) {

  if (argc <= 1) {
    /* Literals next to each other are effectively concatenated. */
    printf("\nUsage: BST_CountWords <path/of/input_file>\n"
               "The file name should be input*.txt where the expansion of * "
               "will be the index.\nThis same index will appear in the output "
               "file \"myoutput*.txt\".\nYou can pass a file name alone or a "
               "path to a file.\nOutput will be in the same directory as "
               "input.\n");
    return 1;
  }

  Bst *wordTree = newBst();

  char *inputFileName = argv[1];
  char *outputFileName = getOutputFileName(inputFileName);
  if (outputFileName == NULL) {
    return 1;
  }


  FILE *inputFile = fopen(inputFileName, "r");
  if (inputFile == NULL) {
    fprintf(stderr, "Error: File \"%s\" does not exist. "
        "Please ensure you pass a valid filename.", inputFileName);
    return 1;
  }

  char *word;
  while ((word = getWord(inputFile))) {
    treeInsert(wordTree, word);
    free(word); /* freeing the extra word that's been malloced in getWord. */
  }
  fclose(inputFile);

  FILE *outputFile = fopen(outputFileName, "w+");
  treeFPrint(outputFile, wordTree);
  fclose(outputFile);

  treeDestroy(wordTree);

  return (0);
}
