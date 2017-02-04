#ifndef MARCO_BST_NODE_DATA_H
#define MARCO_BST_NODE_DATA_H

// Types and/or Structures ————————————————————————————————————————————————————————————————————————————————————————————————————————————————

// change this between data types
typedef char Key;

// Stores the custom data for this version of BST
// change this between data types
typedef struct nodeDataType {
	Key *word;
	int count;
} NodeData;

// Functions ——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

NodeData *newNodeData (Key *key);

NodeData *copyNodeData (NodeData *toCopy);

int customComparer (const NodeData *nodeData, const Key *key);

void customOnInsertExisting (NodeData *thisNodeData);

char *nodeDataKeyToString (NodeData *thisNodeData);

char *nodeDataToString (NodeData *thisNodeData);

void nodeDataDestroy (NodeData *thisNodeData);

#endif // MARCO_BST_NODE_DATA_H
