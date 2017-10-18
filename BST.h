#ifndef MARCO_BST_H
#define MARCO_BST_H

#include <stdbool.h>
#include "BSTNode.h"
#include "BSTNodeData.h"

#define ROT_LEFT true
#define ROT_RIGHT false

/* Types and/or Structures ----------------------------------------------- */

/**
 * Keeps track of root of tree and the size.
 * This allows for root to be included in rotations.
 */
typedef struct bstType {
  BstNode *rootNode;
  int size;
} Bst;

/* Functions ------------------------------------------------------------- */

Bst *newBst ();

void treeDestroy (Bst *thisTree);

int treeHeight (Bst *thisTree);

void treeRotate (Bst *thisTree, bool rotateLeft);

void treeCheckBalance (Bst *thisTree);

bool treeInsert (Bst *thisTree, Key *testKey);

NodeData *treeSearch (Bst *thisTree, Key *testKey);

NodeData *treeRemove (Bst *thisTree, Key *testKey);

NodeData *treeMax (Bst *thisTree);

NodeData *treeMin (Bst *thisTree);

int treeCount (Bst *thisTree);

void treeArrayDestroy (NodeData **array, int size);

NodeData **treeToArray (Bst *thisTree);

void treeDebug (Bst *thisTree);

void treeFPrint (FILE *fp, Bst *thisTree);

void treeToMathematica (Bst *thisTree);

#endif /* MARCO_BST_H */
