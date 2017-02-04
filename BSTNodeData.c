#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BST.h"
#include "BSTNodeData.h"

// Handles custom creation for node data type
NodeData *newNodeData (Key *key) {
	NodeData *newData = (NodeData *)malloc(sizeof(NodeData));

	newData->word = (char *)malloc(strlen(key) + 1);
	strcpy(newData->word, key);
	newData->count = 1;

	return newData;
}

NodeData *copyNodeData (NodeData *toCopy) {
	// TODO: Not Implemented, as part of remove code.
	return NULL;
}

int customComparer (const NodeData *nodeData, const Key *key) {
	return strcmp(key, nodeData->word);
}

void customOnInsertExisting (NodeData *thisNodeData) {
	thisNodeData->count++;
}

char *nodeDataKeyToString (NodeData *thisNodeData) {
	return strdup(thisNodeData->word); // strdup mallocs a string for me, I'll need to free it later
}

char *nodeDataToString (NodeData *thisNodeData) {
	char *toString = (char *)malloc(strlen(thisNodeData->word) + 8); // NOTE: This can only do up to 3 digit numbers for count
	sprintf(toString, "%s: %d", thisNodeData->word, thisNodeData->count);
	return toString;
}

// Handles all custom deletion for node data type
void nodeDataDestroy (NodeData *thisNodeData) {
	free(thisNodeData->word);

	free(thisNodeData);
}
