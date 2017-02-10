#ifndef MARCO_BST_H
#define MARCO_BST_H

#include <stdbool.h>
#include "BSTNode.h"
#include "BSTNodeData.h"

#define ROT_LEFT true
#define ROT_RIGHT false

// Types and/or Structures ————————————————————————————————————————————————————————————————————————————————————————————————————————————————

/// Keeps track of root of tree and the size.
/// This allows for root to be included in rotations.
typedef struct bstType {
	BstNode *rootNode;
	int size;
} Bst;

// Functions ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

Bst *newBst ();

void treeDestroy (Bst *thisTree);

int __unused treeHeight (Bst *thisTree);

void treeRotate (Bst *thisTree, bool rotateLeft);

void treeCheckBalance (Bst *thisTree);

bool treeInsert (Bst *thisTree, Key *testKey);

NodeData  __unused *treeSearch (Bst *thisTree, Key *testKey);

NodeData  __unused *treeRemove (Bst *thisTree, Key *testKey);

NodeData  __unused *treeMax (Bst *thisTree);

NodeData  __unused *treeMin (Bst *thisTree);

int __unused treeCount (Bst *thisTree);

void __unused treeArrayDestroy (NodeData **array, int size);

NodeData __unused **treeToArray (Bst *thisTree);

void __unused treeDebug (Bst *thisTree);

void __unused treeFPrint (FILE *fp, Bst *thisTree);

void __unused treeToMathematica (Bst *thisTree);

#endif // MARCO_BST_H
