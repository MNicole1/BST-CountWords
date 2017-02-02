#ifndef BST_MOSTCOMMONWORD_BST_H
#define BST_MOSTCOMMONWORD_BST_He

typedef int (*Compare) (const char *, const char *);

// Stores the word and the number of times it occurs plus pointers to child branches
typedef struct bstNode {
	char *key;
	int count;
	struct bstNode *left;
	struct bstNode *right;
} BstNode;

// Keeps track of root of tree, allows for root to be included in rotations.
typedef struct bst {
	BstNode *rootNode;
	int count;
} Bst;

Bst *newBst ();

BstNode *newBstNode (char *newWord);

void destroySubtree (BstNode *thisNode);

void destroyTree (Bst *thisNode);

void incrementOrInsertSubtree (BstNode *thisNode, char *word, Compare cmp);

void incrementOrInsert (Bst *thisTree, char *word);

void debugSubtree (BstNode *thisNode, int depth);

void debugTree (Bst *thisTree);

void printSubTree (BstNode *thisNode);

void printTree (Bst *thisTree);

void printSubTreeStructure (BstNode *thisNode, int depth, int tabSize);

void treeToMathematica (Bst *thisTree);

#endif //BST_MOSTCOMMONWORD_BST_H
