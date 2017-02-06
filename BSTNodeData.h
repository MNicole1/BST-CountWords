/*
 * This file and the associated C file have all of the data type specific code.
 * Change these to change the type of tree.
 */

#ifndef MARCO_BST_NODE_DATA_H
#define MARCO_BST_NODE_DATA_H

// Types and/or Structures ————————————————————————————————————————————————————————————————————————————————————————————————————————————————

typedef char Key; // This tree is indexed by strings.

/// Stores the custom data for this version of BST
typedef struct nodeDataType {
	Key *word; // The keys are the words we are counting
	int count; // We want to know how many times we encounter each word
} NodeData;

// Functions ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

NodeData *newNodeData (Key *key);

NodeData *nodeDataCopy (NodeData *thisNodeData);

Key *nodeDataGetKey(NodeData *thisNodeData);

int customComparer (const Key *key, const NodeData *nodeData);

void customOnInsertExisting (NodeData *thisNodeData);

void customOnSearchFind (NodeData  __unused *thisNodeData);

char *nodeDataKeyToString (NodeData *thisNodeData);

char *nodeDataToString (NodeData *thisNodeData);

void nodeDataDestroy (NodeData *thisNodeData);

#endif // MARCO_BST_NODE_DATA_H
