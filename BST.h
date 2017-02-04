#include <stdbool.h>
#include "BSTNodeData.h"

#ifndef MARCO_BST_H
#define MARCO_BST_H

// Types and/or Structures ————————————————————————————————————————————————————————————————————————————————————————————————————————————————

// Stores pointers to data and child branches
typedef struct bstNodeType {
	NodeData *data;
	struct bstNodeType *left;
	struct bstNodeType *right;
} BstNode;

// Keeps track of root of tree, allows for root to be included in rotations.
typedef struct bstType {
	BstNode *rootNode;
	int size;
} Bst;

// Functions ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Bst *newBst ();

BstNode *newBstNode (Key *newKey);

void nodeDestroy (BstNode *thisNode);

void subTreeDestroy (BstNode *thisNode);

void treeDestroy (Bst *thisNode);

bool subTreeInsert (BstNode *thisNode, Key *testKey);

bool treeInsert (Bst *thisTree, Key *testKey);

void subTreeDebug (BstNode *thisNode, int depth);

void treeDebug (Bst *thisTree);

void subTreeFPrint (FILE *fp, BstNode *thisNode);

void treeFPrint (FILE *fp, Bst *thisTree);

void subTreeToMathematica (BstNode *thisNode);

void treeToMathematica (Bst *thisTree);

#endif // MARCO_BST_H
