//
// Created by Marcello Nicoletti on 1/31/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: Pull tree into own file so I can use in multiple files.

//use typedef to make calling the compare function easier
typedef int (*Compare) (const char *, const char *);

struct bstRoot {
	struct bstNode *rootNode;
};

// Stores the word and the number of times it occurs plus pointers to child branches
struct bstNode {
	char *word;
	int count;
	struct bstNode *left;
	struct bstNode *right;
};

struct bstRoot *newBst () {
	struct bstRoot *root = (struct bstRoot *)malloc(sizeof(struct bstRoot));
	root->rootNode = NULL;
	return root;
}

// initializes new tree node with newWord for key
struct bstNode *newBstNode (char *newWord) {
	struct bstNode *newNode = (struct bstNode *)malloc(sizeof(struct bstNode));

	newNode->word = (char *)malloc(strlen(newWord) + 1); // memory for the word
	strcpy(newNode->word, newWord);
	newNode->count = 1;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

// Recursively deletes the subtree under this node as well as this node.
void deleteSubtree (struct bstNode *this) {
	if (this->left != NULL) {
		deleteSubtree(this->left);
		this->left = NULL;
	}

	if (this->right != NULL) {
		deleteSubtree(this->right);
		this->right = NULL;
	}

	free(this->word);
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
	int compared = cmp(word, this->word);
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

void incrementOrInsertRoot (struct bstRoot *root, char *word, Compare cmp) {
	if (root->rootNode == NULL) {
		root->rootNode = newBstNode(word);
	} else {
		incrementOrInsert(root->rootNode, word, cmp);
	}
}

// Recursive in-order traversal of tree. prints some extra information about tree structure
void debugSubtree (struct bstNode *this, int depth) {
	if (this->left != NULL) {
		printf("(");
		debugSubtree(this->left, depth + 1);
		printf(") <- ");
	}

	printf("%d:%s:%d", depth, this->word, this->count);

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

int main () {
	// Test case 1, should produce a fairly balanced tree
	printf("\nCase 1: Balanced tree. (due to insertion order)\n");
	struct bstRoot *wordTree = newBst();
	incrementOrInsertRoot(wordTree, "mary", strcmp);
	incrementOrInsertRoot(wordTree, "donna", strcmp);
	incrementOrInsertRoot(wordTree, "julie", strcmp);
	incrementOrInsertRoot(wordTree, "trever", strcmp);
	incrementOrInsertRoot(wordTree, "trever", strcmp);
	incrementOrInsertRoot(wordTree, "orson", strcmp);
	incrementOrInsertRoot(wordTree, "orson", strcmp);
	incrementOrInsertRoot(wordTree, "allison", strcmp);
	incrementOrInsertRoot(wordTree, "zain", strcmp);
	debugTree(wordTree);
	deleteTree(wordTree);

	// Test case 2, should produce a right skewed tree
	printf("\nCase 2: Right only tree.\n");
	struct bstRoot *wordTree2 = newBst();
	incrementOrInsertRoot(wordTree2, "allison", strcmp);
	incrementOrInsertRoot(wordTree2, "donna", strcmp);
	incrementOrInsertRoot(wordTree2, "julie", strcmp);
	incrementOrInsertRoot(wordTree2, "mary", strcmp);
	incrementOrInsertRoot(wordTree2, "orson", strcmp);
	incrementOrInsertRoot(wordTree2, "orson", strcmp);
	incrementOrInsertRoot(wordTree2, "trever", strcmp);
	incrementOrInsertRoot(wordTree2, "trever", strcmp);
	incrementOrInsertRoot(wordTree2, "zain", strcmp);
	debugTree(wordTree2);
	deleteTree(wordTree2);

	// Test case 3, should produce a left skewed tree
	printf("\nCase 3: Left only tree.\n");
	struct bstRoot *wordTree3 = newBst();
	incrementOrInsertRoot(wordTree3, "zain", strcmp);
	incrementOrInsertRoot(wordTree3, "trever", strcmp);
	incrementOrInsertRoot(wordTree3, "trever", strcmp);
	incrementOrInsertRoot(wordTree3, "orson", strcmp);
	incrementOrInsertRoot(wordTree3, "orson", strcmp);
	incrementOrInsertRoot(wordTree3, "mary", strcmp);
	incrementOrInsertRoot(wordTree3, "julie", strcmp);
	incrementOrInsertRoot(wordTree3, "donna", strcmp);
	incrementOrInsertRoot(wordTree3, "allison", strcmp);
	debugTree(wordTree3);
	deleteTree(wordTree3);

	// Test case 4, from assignment
	printf("\nCase 4: Tree from assignment.\n");
	struct bstRoot *wordTree4 = newBst();
	incrementOrInsertRoot(wordTree4, "now", strcmp);
	incrementOrInsertRoot(wordTree4, "is", strcmp);
	incrementOrInsertRoot(wordTree4, "the", strcmp);
	incrementOrInsertRoot(wordTree4, "time", strcmp);
	incrementOrInsertRoot(wordTree4, "for", strcmp);
	incrementOrInsertRoot(wordTree4, "all", strcmp);
	incrementOrInsertRoot(wordTree4, "good", strcmp);
	incrementOrInsertRoot(wordTree4, "men", strcmp);
	incrementOrInsertRoot(wordTree4, "to", strcmp);
	incrementOrInsertRoot(wordTree4, "come", strcmp);
	incrementOrInsertRoot(wordTree4, "to", strcmp);
	incrementOrInsertRoot(wordTree4, "the", strcmp);
	incrementOrInsertRoot(wordTree4, "aid", strcmp);
	incrementOrInsertRoot(wordTree4, "of", strcmp);
	incrementOrInsertRoot(wordTree4, "their", strcmp);
	incrementOrInsertRoot(wordTree4, "party", strcmp);
	debugTree(wordTree4);
	deleteTree(wordTree4);

	// Test case 5, empty tree
	printf("\nCase 5: An empty tree.\n");
	struct bstRoot *wordTree5 = newBst();
	debugTree(wordTree5);
	deleteTree(wordTree5);

	return(0);
}
