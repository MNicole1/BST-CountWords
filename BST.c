#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

// TODO: Implement rotation on insert to allow for self balancing trees.

Bst *newBst () {
	Bst *root = (Bst *)malloc(sizeof(Bst));
	root->rootNode = NULL;
	return root;
}

// initializes new tree node with newWord for key
BstNode *newBstNode (char *newWord) {
	BstNode *newNode = (BstNode *)malloc(sizeof(BstNode));

	newNode->key = (char *)malloc(strlen(newWord) + 1); // memory for the key
	strcpy(newNode->key, newWord);
	newNode->count = 1;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

// Recursively deletes the subtree under this node as well as this node.
void destroySubtree (BstNode *thisNode) {
	if (thisNode->left != NULL) {
		destroySubtree(thisNode->left);
		thisNode->left = NULL;
	}

	if (thisNode->right != NULL) {
		destroySubtree(thisNode->right);
		thisNode->right = NULL;
	}

	free(thisNode->key);
	free(thisNode);
}

// Starts the recursive process
void destroyTree (Bst *thisNode) {
	if (thisNode->rootNode != NULL) {
		destroySubtree(thisNode->rootNode);
	}
	free(thisNode);
}

// Recursively searches for a word. if found increments the node's count, if not adds new node in correct place.
void incrementOrInsertSubtree (BstNode *thisNode, char *word, Compare cmp) {
	int compared = cmp(word, thisNode->key);
	if (compared < 0) {
		// insert left
		if (thisNode->left == NULL) {
			thisNode->left = newBstNode(word);
		} else {
			incrementOrInsertSubtree(thisNode->left, word, cmp);
		}
	} else if (compared > 0) {
		// insert right
		if (thisNode->right == NULL) {
			thisNode->right = newBstNode(word);
		} else {
			incrementOrInsertSubtree(thisNode->right, word, cmp);
		}
	} else { // if (compared == 0)
		thisNode->count++;
	}
}

void incrementOrInsert (Bst *thisTree, char *word) {
	if (thisTree->rootNode == NULL) {
		thisTree->rootNode = newBstNode(word);
		thisTree->count = 1;
	} else {
		incrementOrInsertSubtree(thisTree->rootNode, word, strcmp);
		thisTree->count++;
	}
}

// Recursive in-order traversal of tree. prints some extra information about tree structure
void debugSubtree (BstNode *thisNode, int depth) {
	if (thisNode->left != NULL) {
		printf("(");
		debugSubtree(thisNode->left, depth + 1);
		printf(") <- ");
	}

	printf("%d:%s:%d", depth, thisNode->key, thisNode->count);

	if (thisNode->right != NULL) {
		printf(" -> (");
		debugSubtree(thisNode->right, depth + 1);
		printf(")");
	}
}

// Initiates recursive printing.
void debugTree (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		debugSubtree(thisTree->rootNode, 0);
	} else {
		printf("Tree is empty.");
	}
	printf("\n");
}

void printSubTree (BstNode *thisNode) {
	if (thisNode->left != NULL) {
		printSubTree(thisNode->left);
	}

	printf("%s: %d\n", thisNode->key, thisNode->count);

	if (thisNode->right != NULL) {
		printSubTree(thisNode->right);
	}
}

void printTree (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		printSubTree(thisTree->rootNode);
	} else {
		printf("There were no words given.");
	}
	printf("\n");
}\

void subTreeToMathematica (BstNode *thisNode) {
	if (thisNode->left != NULL) {
		printf("%s -> %s, ", thisNode->key, thisNode->left->key);
		subTreeToMathematica(thisNode->left);
	}

	if (thisNode->right != NULL) {
		printf("%s -> %s, ", thisNode->key, thisNode->right->key);
		subTreeToMathematica(thisNode->right);
	}
}

void treeToMathematica (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		printf("TreePlot[{root -> %s, ", thisTree->rootNode->key);
		subTreeToMathematica(thisTree->rootNode);
		printf("}, Automatic, root, VertexLabeling -> True, ImageSize -> Full, AspectRatio -> Automatic]");
	} else {
		printf("There were no words given.");
	}
	printf("\n");
}
