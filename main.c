#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Recursive in-order traversal of tree. prints the word and the number of times it appears.
void printSubtree (struct bstNode *this) {
	if (this->left != NULL) {
		printf("(");
		printSubtree(this->left);
		printf(") <- ");
	}

	printf("%s:%d", this->word, this->count);

	if (this->right != NULL) {
		printf(" -> (");
		printSubtree(this->right);
		printf(")");
	}
}

// Initiates recursive printing.
void printTree (struct bstRoot *root) {
	if (root->rootNode != NULL) {
		printSubtree(root->rootNode);
	} else {
		printf("Tree is empty.");
	}
}

int main () {
	struct bstRoot *wordTree = newBst();

	// Test case, should produce a fairly balanced tree
	incrementOrInsertRoot(wordTree, "mary", strcmp);
	incrementOrInsertRoot(wordTree, "donna", strcmp);
	incrementOrInsertRoot(wordTree, "julie", strcmp);
	incrementOrInsertRoot(wordTree, "orson", strcmp);
	incrementOrInsertRoot(wordTree, "orson", strcmp);
	incrementOrInsertRoot(wordTree, "trever", strcmp);
	incrementOrInsertRoot(wordTree, "trever", strcmp);
	incrementOrInsertRoot(wordTree, "allison", strcmp);
	incrementOrInsertRoot(wordTree, "zain", strcmp);

	printTree(wordTree);

	deleteTree(wordTree);

	return(0);
}
