/*
 * This file and the associated H file have all of the data type specific code.
 * Change these to change the type of tree.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BST.h"
#include "BSTNodeData.h"

// Constructor for this tree's data type.
// Note, currently only takes a key so any extra data has to be made from scratch (eg. a count, or an expansion of the key type).
NodeData *newNodeData (Key *key) {
	NodeData *newData = (NodeData *)malloc(sizeof(NodeData));

	newData->word = (char *)malloc(strlen(key) + 1); // Make space for a copy of the key.
	strcpy(newData->word, key); // The key is the word.
	newData->count = 1; // start at 1 since this is the first I've seen of this word.

	return newData;
}

// Coming soon: This will get used as part of the process of removing a node.
NodeData __unused *copyNodeData (NodeData *toCopy) {
	// TODO: Not Implemented, as part of remove code.
	return NULL;
}

// Called as part of the insert process.
// Determines how a keys is greater than or less than the current node.
// This is the core of the BST.
int customComparer (const Key *key, const NodeData *nodeData) {
	return strcmp(key, nodeData->word); // compare the key to the data's word.
}

// Called when inserting a key that already existed.
void customOnInsertExisting (NodeData *thisNodeData) {
	thisNodeData->count++; // Re-encountered this word, increment it's count.
}

// Represents this node's key as a string. Useful when you only want the key.
char *nodeDataKeyToString (NodeData *thisNodeData) {
	return strdup(thisNodeData->word); // strdup mallocs a string for me, I'll need to free it later
}

// Represents this node's data as a string. Feel free to give as much or as little detail here.
char *nodeDataToString (NodeData *thisNodeData) {
	char *toString = (char *)malloc(strlen(thisNodeData->word) + 8); // NOTE: This string can only do up to 3 digit numbers for count.
	// I could also use itoa() and strcpy()+strcat(), but this is one call. Didn't need itoa after all.
	sprintf(toString, "%s: %d", thisNodeData->word, thisNodeData->count);
	return toString;
}

// Destroys this NodeData. Called when the node using it is destroyed or before being replaced as part of the remove process.
void nodeDataDestroy (NodeData *thisNodeData) {
	free(thisNodeData->word);

	free(thisNodeData);
}
