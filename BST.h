#include <stdbool.h>
#include "BSTNodeData.h"

#ifndef MARCO_BST_H
#define MARCO_BST_H

// Types and/or Structures ————————————————————————————————————————————————————————————————————————————————————————————————————————————————

// Stores pointers to data type and child branches. NodeData can be changed to make this a different kind of tree as needed.
typedef struct bstNodeType {
	NodeData *data;
	struct bstNodeType *left;
	struct bstNodeType *right;
} BstNode;

// Keeps track of root of tree and the size.
// This allows for root to be included in rotations.
typedef struct bstType {
	BstNode *rootNode;
	int size;
} Bst;

// Functions ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Bst *newBst ();

BstNode *newBstNode (Key *newKey);

void nodeDestroy (BstNode *thisNode);

void subTreeDestroy (BstNode *thisNode);

void treeDestroy (Bst *thisTree);

bool subTreeInsert (BstNode *thisNode, Key *testKey);

bool treeInsert (Bst *thisTree, Key *testKey);

void subTreeDebug (BstNode *thisNode, int depth);

void __unused treeDebug (Bst *thisTree);

void subTreeFPrint (FILE *fp, BstNode *thisNode);

void __unused treeFPrint (FILE *fp, Bst *thisTree);

void subTreeToMathematica (BstNode *thisNode);

void __unused treeToMathematica (Bst *thisTree);

#endif // MARCO_BST_H
