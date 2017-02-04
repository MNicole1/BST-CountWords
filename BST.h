#include <stdbool.h>

#ifndef BST_MOSTCOMMONWORD_BST_H
#define BST_MOSTCOMMONWORD_BST_He

// TODO: New Comments for each function.
// TODO: Migrate NodeData def and functions to NodeData.(c|h). Anything that needs changing to change the data type of the tree.

// Types and/or Structures ———————————————————————————————————————————————————————————————————————————————————————————————————————————————————

// change this between data types
typedef char Key;

// Stores the custom data for this version of BST
// change this between data types
typedef struct nodeDataType {
	Key *word;
	int count;
} NodeData;

// Stores pointers to data and child branches
typedef struct bstNodeType {
	NodeData *data;
	struct bstNodeType *left;
	struct bstNodeType *right;
} BstNode;

// Keeps track of root of tree, allows for root to be included in rotations.
typedef struct bstType {
	BstNode *rootNode;
	int count;
} Bst;

// Functions ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

int customComparer (const NodeData *nodeData, const Key *key);

void customOnInsertExisting (NodeData *thisNodeData);

char *nodeDataKeyToString (NodeData *thisNodeData);

char *nodeDataToString (NodeData *thisNodeData);

void nodeDataDestroy (NodeData *thisNodeData);

NodeData *newNodeData (Key *key);

Bst *newBst ();

BstNode *newBstNode (Key *newKey);

void nodeDestroy (BstNode *thisNode);

void subTreeDestroy (BstNode *thisNode);

void treeDestroy (Bst *thisNode);

void subTreeInsert (BstNode *thisNode, Key *testKey);

void treeInsert (Bst *thisTree, Key *testKey);

void subTreeDebug (BstNode *thisNode, int depth);

void treeDebug (Bst *thisTree);

void subTreePrint (FILE *fp, BstNode *thisNode);

void treePrint (FILE *fp, Bst *thisTree);

void subTreeToMathematica (BstNode *thisNode);

void treeToMathematica (Bst *thisTree);

#endif //BST_MOSTCOMMONWORD_BST_H
