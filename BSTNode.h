#ifndef MARCO_BST_NODE_H
#define MARCO_BST_NODE_H

#include <stdbool.h>
#include "BSTNodeData.h"

#define ROT_LEFT true
#define ROT_RIGHT false

/* Types and/or Structures ----------------------------------------------- */

/**
 * Stores pointers to data type and child branches.
 * NodeData can be changed to make this a different kind of tree as needed.
 */
typedef struct bstNodeType {
  NodeData *data;
  struct bstNodeType *left;
  struct bstNodeType *right;
} BstNode;

/* Functions ------------------------------------------------------------- */

BstNode *newBstNode (Key *newKey);

void nodeDestroy (BstNode *thisNode);

void subTreeDestroy (BstNode *thisNode);

int subTreeHeight (BstNode *thisNode);

void subTreeRotate (BstNode *thisNode, bool rotateLeft, BstNode *parentNode);

void subTreeCheckBalance (BstNode *thisNode, BstNode *parentNode);

NodeData *subTreeMax (BstNode *thisNode);

NodeData *subTreeMin (BstNode *thisNode);

int subTreeCount (BstNode *thisNode);

int subTreeToArray (BstNode *thisNode, NodeData **arrayInProgress,
                    int runningTotal);

bool subTreeInsert (BstNode *thisNode, Key *testKey);

NodeData *subTreeSearch (BstNode *thisNode, Key *testKey);

bool subTreeRemove (BstNode *thisNode, Key *testKey, BstNode *parentNode);

void subTreeDebug (BstNode *thisNode, int depth);

void subTreeFPrint (struct __sFILE *fp, BstNode *thisNode);

void subTreeToMathematica (BstNode *thisNode);

#endif /* MARCO_BST_NODE_H */
