#ifndef BST_MOSTCOMMONWORD_BST_H
#define BST_MOSTCOMMONWORD_BST_He

typedef int (*Compare) (const char *, const char *);

// Keeps track of root of tree, allows for root to be included in rotations.
struct bstRoot {
	struct bstNode *rootNode;
	int count;
};

// Stores the word and the number of times it occurs plus pointers to child branches
struct bstNode {
	char *key;
	int count;
	struct bstNode *left;
	struct bstNode *right;
};

struct bstRoot *newBst ();

struct bstNode *newBstNode (char *newWord);

void deleteSubtree (struct bstNode *this);

void deleteTree (struct bstRoot *this);

void incrementOrInsert (struct bstNode *this, char *word, Compare cmp);

void incrementOrInsertRoot (struct bstRoot *root, char *word);

void debugSubtree (struct bstNode *this, int depth);

void debugTree (struct bstRoot *root);

void printSubTree (struct bstNode *this);

void printTree (struct bstRoot *root);

#endif //BST_MOSTCOMMONWORD_BST_H
