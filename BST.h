#ifndef BST_MOSTCOMMONWORD_BST_H
#define BST_MOSTCOMMONWORD_BST_He

typedef int (*Compare) (const char *, const char *);

// Stores the word and the number of times it occurs plus pointers to child branches
typedef struct bstNode {
	char *key;
	int count;
	struct BstNode *left;
	struct BstNode *right;
} BstNode;

// Keeps track of root of tree, allows for root to be included in rotations.
typedef struct bst {
	BstNode *rootNode;
	int count;
} Bst;

Bst *newBst ();

BstNode *newBstNode (char *newWord);

void deleteSubtree (BstNode *this);

void deleteTree (Bst *this);

void incrementOrInsert (BstNode *this, char *word, Compare cmp);

void incrementOrInsertRoot (Bst *root, char *word);

void debugSubtree (BstNode *this, int depth);

void debugTree (Bst *root);

void printSubTree (BstNode *this);

void printTree (Bst *root);

#endif //BST_MOSTCOMMONWORD_BST_H
