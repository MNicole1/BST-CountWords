#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "BST.h"

// TODO: New Comments for each function to account for updated functionality
// TODO: Implement rotation on insert to allow for self balancing trees.
// TODO: Create remove() functions for a more complete bin tree implementation.
// TODO: Make subTree insert() & remove() boolean for if truly inserted or not. this is to maintain good counts.

int customComparer (const NodeData *nodeData, const Key *key) {
	// change this between data types
	return strcmp(key, nodeData->word);
}

void customOnInsertExisting (NodeData *thisNodeData) {
	// change this between data types
	thisNodeData->count++;
}

char *nodeDataKeyToString (NodeData *thisNodeData) {
	// change this between data types
	return strdup(thisNodeData->word); // strdup mallocs a string for me, I'll need to free it later
}

char *nodeDataToString (NodeData *thisNodeData) {
	// change this between data types
	char *toString = (char *)malloc(strlen(thisNodeData->word) + 8); // NOTE: This can only do up to 3 digit numbers for count
	sprintf(toString, "%s: %d", thisNodeData->word, thisNodeData->count);
	return toString;
}

// Handles all custom deletion for node data type
void nodeDataDestroy (NodeData *thisNodeData) {
	// change this between data types
	free(thisNodeData->word);

	free(thisNodeData);
}

// Handles custom creation for node data type
NodeData *newNodeData (Key *key) {
	NodeData *newData = (NodeData *)malloc(sizeof(NodeData));

	// change this between data types
	newData->word = (char *)malloc(strlen(key) + 1);
	strcpy(newData->word, key);
	newData->count = 1;

	return newData;
}

Bst *newBst () {
	Bst *root = (Bst *)malloc(sizeof(Bst));

	root->rootNode = NULL;

	return root;
}

// Initializes new tree node with newKey for key
BstNode *newBstNode (Key *newKey) {
	BstNode *newNode = (BstNode *)malloc(sizeof(BstNode));

	newNode->data = newNodeData(newKey);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

void nodeDestroy (BstNode *thisNode) {
	nodeDataDestroy(thisNode->data);
	free(thisNode);
}

// Recursively destories the subtree under this node as well as this node.
void subTreeDestroy (BstNode *thisNode) {
	if (thisNode->left != NULL) {
		subTreeDestroy(thisNode->left);
	}

	if (thisNode->right != NULL) {
		subTreeDestroy(thisNode->right);
	}

	nodeDestroy(thisNode);
}

// Starts the recursive process
void treeDestroy (Bst *thisNode) {
	if (thisNode->rootNode != NULL) {
		subTreeDestroy(thisNode->rootNode);
	}
	free(thisNode);
}

// Recursively searches for a word. if found increments the node's count, if not adds new node in correct place.
void subTreeInsert (BstNode *thisNode, Key *testKey) {
	int compared = customComparer(thisNode->data, testKey);

	if (compared < 0) {
		// insert left
		if (thisNode->left == NULL) {
			thisNode->left = newBstNode(testKey);
		} else {
			subTreeInsert(thisNode->left, testKey);
		}
	} else if (compared > 0) {
		// insert right
		if (thisNode->right == NULL) {
			thisNode->right = newBstNode(testKey);
		} else {
			subTreeInsert(thisNode->right, testKey);
		}
	} else { // if (compared == 0)
		customOnInsertExisting(thisNode->data);
	}
}

void treeInsert (Bst *thisTree, Key *testKey) {
	if (thisTree->rootNode == NULL) {
		thisTree->rootNode = newBstNode(testKey);
		thisTree->count = 1;
	} else {
		subTreeInsert(thisTree->rootNode, testKey);
		thisTree->count++;
	}
}

// Recursive in-order traversal of tree. prints some extra information about tree structure
void subTreeDebug (BstNode *thisNode, int depth) {
	if (thisNode->left != NULL) {
		printf("(");
		subTreeDebug(thisNode->left, depth + 1);
		printf(") <- ");
	}

	char *temp = nodeDataToString(thisNode->data);
	printf("%d:%s", depth, temp);
	free(temp); // freeing the extra word that's been malloced in nodeDataToString.

	if (thisNode->right != NULL) {
		printf(" -> (");
		subTreeDebug(thisNode->right, depth + 1);
		printf(")");
	}
}

// Initiates recursive printing.
void treeDebug (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		subTreeDebug(thisTree->rootNode, 0);
	} else {
		printf("Tree is empty.");
	}
	printf("\n");
}

void subTreePrint (FILE *fp, BstNode *thisNode) {
	if (thisNode->left != NULL) {
		subTreePrint(fp, thisNode->left);
	}

	char *temp = nodeDataToString(thisNode->data);
	fprintf(fp, "%s\n", temp);
	free(temp); // freeing the extra word that's been malloced in nodeDataToString.

	if (thisNode->right != NULL) {
		subTreePrint(fp, thisNode->right);
	}
}

void treePrint (FILE *fp, Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		subTreePrint(fp, thisTree->rootNode);
	} else {
		fprintf(fp, "There were no words given.");
	}
	printf("\n");
}\


void subTreeToMathematica (BstNode *thisNode) {
	if (thisNode->left != NULL) {
		char *temp1 = nodeDataKeyToString(thisNode->data), *temp2 = nodeDataKeyToString(thisNode->left->data);
		printf("%s -> %s, ", temp1, temp2);
		free(temp1);
		free(temp2); // freeing the extra word that's been malloced in nodeDataKeyToString.
		subTreeToMathematica(thisNode->left);
	}

	if (thisNode->right != NULL) {
		char *temp1 = nodeDataKeyToString(thisNode->data), *temp2 = nodeDataKeyToString(thisNode->right->data);
		printf("%s -> %s, ", temp1, temp2);
		free(temp1);
		free(temp2); // freeing the extra word that's been malloced in nodeDataKeyToString.
		subTreeToMathematica(thisNode->right);
	}
}

void treeToMathematica (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		char *temp = nodeDataKeyToString(thisTree->rootNode->data);
		printf("TreePlot[{root -> %s, ", temp);
		free(temp); // freeing the extra word that's been malloced in nodeDataKeyToString.
		subTreeToMathematica(thisTree->rootNode);
		printf("}, Automatic, root, VertexLabeling -> True, ImageSize -> Full, AspectRatio -> Automatic]");
	} else {
		printf("There were no words given.");
	}
	printf("\n");
}
