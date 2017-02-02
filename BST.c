#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

struct bstRoot *newBst () {
	struct bstRoot *root = (struct bstRoot *)malloc(sizeof(struct bstRoot));
	root->rootNode = NULL;
	return root;
}

// initializes new tree node with newWord for key
struct bstNode *newBstNode (char *newWord) {
	struct bstNode *newNode = (struct bstNode *)malloc(sizeof(struct bstNode));

	newNode->key = (char *)malloc(strlen(newWord) + 1); // memory for the key
	strcpy(newNode->key, newWord);
	newNode->count = 1;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

// Recursively deletes the subtree under this node as well as this node.
void  deleteSubtree (struct bstNode *this) {
	if (this->left != NULL) {
		deleteSubtree(this->left);
		this->left = NULL;
	}

	if (this->right != NULL) {
		deleteSubtree(this->right);
		this->right = NULL;
	}

	free(this->key);
	free(this);
}

// Starts the recursive process
void deleteTree (struct bstRoot *this) {
	if (this->rootNode != NULL) {
		deleteSubtree(this->rootNode);
	}
	free(this);
}

// Recursively searches for a word. if found increments the node's count, if not adds new node in correct place.
void incrementOrInsert (struct bstNode *this, char *word, Compare cmp) {
	int compared = cmp(word, this->key);
	if (compared < 0) {
		// insert left
		if (this->left == NULL) {
			this->left = newBstNode(word);
		} else {
			incrementOrInsert(this->left, word, cmp);
		}
	} else if (compared > 0) {
		// insert right
		if (this->right == NULL) {
			this->right = newBstNode(word);
		} else {
			incrementOrInsert(this->right, word, cmp);
		}
	} else { // if (compared == 0)
		this->count++;
	}
}

void incrementOrInsertRoot (struct bstRoot *root, char *word) {
	if (root->rootNode == NULL) {
		root->rootNode = newBstNode(word);
		root->count = 1;
	} else {
		incrementOrInsert(root->rootNode, word, strcmp);
		root->count++;
	}
}

// Recursive in-order traversal of tree. prints some extra information about tree structure
void debugSubtree (struct bstNode *this, int depth) {
	if (this->left != NULL) {
		printf("(");
		debugSubtree(this->left, depth + 1);
		printf(") <- ");
	}

	printf("%d:%s:%d", depth, this->key, this->count);

	if (this->right != NULL) {
		printf(" -> (");
		debugSubtree(this->right, depth + 1);
		printf(")");
	}
}

// Initiates recursive printing.
void debugTree (struct bstRoot *root) {
	if (root->rootNode != NULL) {
		debugSubtree(root->rootNode, 0);
	} else {
		printf("Tree is empty.");
	}
	printf("\n");
}

void printSubTree (struct bstNode *this) {
	if (this->left != NULL) {
		printSubTree(this->left);
	}

	printf("%s: %d\n", this->key, this->count);

	if (this->right != NULL) {
		printSubTree(this->right);
	}
}

void printTree (struct bstRoot *root) {
	if (root->rootNode != NULL) {
		printSubTree(root->rootNode);
	} else {
		printf("Tree is empty.");
	}
	printf("\n");
}
