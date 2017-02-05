#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BST.h"
#include "BSTNodeData.h"

// TODO: Implement rotation on insert to allow for self balancing trees.
// TODO: Create remove() functions for a more complete bin tree implementation.
// TODO: Create search() functions for a more complete bin tree implementation.
// TODO: Add treeToArray() and subTreeToArray() functions.

// Constructor for Bst, sets default values.
Bst *newBst () {
	Bst *tree = (Bst *)malloc(sizeof(Bst));

	tree->rootNode = NULL;
	tree->size = 0;

	return tree;
}

// Constructor for BstNode, sets default values for branch pointers & passes key for NodeData construction.
BstNode *newBstNode (Key *newKey) {
	BstNode *newNode = (BstNode *)malloc(sizeof(BstNode));

	newNode->data = newNodeData(newKey);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

// Destroys this node, for use both with remove (as a leaf) and as part of finalizing the tree.
void nodeDestroy (BstNode *thisNode) {
	nodeDataDestroy(thisNode->data);
	free(thisNode);
}

// Recursively destroys the subtree under this node as well as this node, for use as part of finalizing the tree.
void subTreeDestroy (BstNode *thisNode) {
	if (thisNode->left != NULL) {
		subTreeDestroy(thisNode->left);
	}

	if (thisNode->right != NULL) {
		subTreeDestroy(thisNode->right);
	}

	nodeDestroy(thisNode);
}

// Starts the recursive destruction process. Finalizes the tree, completely freeing it.
void treeDestroy (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		subTreeDestroy(thisTree->rootNode);
	}
	free(thisTree);
}

// Recurse down the right branch to find the maximum value under this node.
// Used as part of the remove process and as a general utility.
NodeData *subTreeMax (BstNode *thisNode) {
	if (thisNode->right == NULL) { // Base Case, fully right
		return thisNode->data;
	}

	return subTreeMax(thisNode->right);
}

// Begins the recursion to find the tree's maximum value.
NodeData  __unused *treeMax (Bst *thisTree) {
	if (thisTree->rootNode == NULL) {
		return NULL;
	}
	return subTreeMax(thisTree->rootNode);
}

// Recurse down the left branch to find the minimum value under this node.
// Used as part of the remove process and as a general utility.
NodeData *subTreeMin (BstNode *thisNode) {
	if (thisNode->left == NULL) { // Base Case, fully left
		return thisNode->data;
	}

	return subTreeMin(thisNode->left);
}

// Begins the recursion to find the tree's minimum value.
NodeData  __unused *treeMin (Bst *thisTree) {
	if (thisTree->rootNode == NULL) {
		return NULL;
	}
	return subTreeMin(thisTree->rootNode);
}

// Recursively counts nodes in this subtree.
int subTreeCount (BstNode *thisNode) {
	if (thisNode == NULL) {
		return 0;
	}

	return subTreeCount(thisNode->left) + subTreeCount(thisNode->right) + 1;
}

// Recursively counts nodes in this tree.
int __unused treeCount (Bst *thisTree) {
	if (thisTree->rootNode == NULL) {
		return 0;
	}

	return subTreeCount(thisTree->rootNode);
}

// Destroys the array created below.
void treeArrayDestroy (NodeData **array, int size) {
	NodeData *thisNode;
	for (int i = 0; i < size; i++) {
		thisNode = array[i];
		nodeDataDestroy(thisNode);
	}
	free(array);
}

// Recursively traverses in order while adding to the array.
// return the running total. only increment it once per call.
// This shouldn't be called anywhere but itself or treeToArray()
int subTreeToArray (BstNode *thisNode, NodeData **arrayInProgress, int runningTotal) {
	if (thisNode->left != NULL) {
		runningTotal = subTreeToArray(thisNode->left, arrayInProgress, runningTotal);
	}

	arrayInProgress[runningTotal++] = copyNodeData(thisNode->data);

	if (thisNode->right != NULL) {
		runningTotal = subTreeToArray(thisNode->right, arrayInProgress, runningTotal);
	}
	return runningTotal;
}

// Returns the tree in order as an array of NodeData pointers to copies of the node's data.
NodeData __unused **treeToArray (Bst *thisTree) {
	if (thisTree->rootNode == NULL) {
		return NULL;
	}
	NodeData **array = (NodeData **)malloc(sizeof(NodeData) * thisTree->size);
	subTreeToArray(thisTree->rootNode, array, 0);
	return array;
}

// Recursively searches for key. If found, calls NodeData's customOnInsertExisting, else creates a new node in correct place.
// True means key was new, false means it wasn't.
// Coming soon: Keeps tree balanced by performing rotations as needed.
bool subTreeInsert (BstNode *thisNode, Key *testKey) {
	int compared = customComparer(testKey, thisNode->data);

	if (compared < 0) {
		// insert left
		if (thisNode->left == NULL) {
			thisNode->left = newBstNode(testKey);
			return true;
		} else {
			return subTreeInsert(thisNode->left, testKey);
		}
	} else if (compared > 0) {
		// insert right
		if (thisNode->right == NULL) {
			thisNode->right = newBstNode(testKey);
			return true;
		} else {
			return subTreeInsert(thisNode->right, testKey);
		}
	} else { // if (compared == 0)
		customOnInsertExisting(thisNode->data); // This call may do nothing.
		return false;
	}
}

// Starts recursive insert process. Increments size correctly.
bool treeInsert (Bst *thisTree, Key *testKey) {
	if (thisTree->rootNode == NULL) {
		thisTree->rootNode = newBstNode(testKey);
		thisTree->size = 1;
		return true;
	} else {
		bool isNew = subTreeInsert(thisTree->rootNode, testKey);
		if (isNew) {
			thisTree->size++;
		}
		return isNew;
	}
}

NodeData *subTreeSearch (NodeData *thisNode, Key *testKey) {
	// TODO: Not Implemented
	return NULL;
}

NodeData *treeSearch (Bst *thisTree, Key *testKey) {
	// TODO: Not Implemented
	return NULL;
}

// Recursive in-order traversal of tree.
// Prints diagnostic information about tree structure.
// Note that this is unreadable on larger trees, use mathematica for that.
void subTreeDebug (BstNode *thisNode, int depth) {
	if (thisNode->left != NULL) {
		printf("(");
		subTreeDebug(thisNode->left, depth + 1);
		printf(") <- ");
	}

	char *temp = nodeDataToString(thisNode->data);
	printf("%d:%s", depth, temp);
	free(temp); // freeing the extra word that's been malloced in nodeDataToString.

	if (thisNode->right != NULL) {
		printf(" -> (");
		subTreeDebug(thisNode->right, depth + 1);
		printf(")");
	}
}

// Initiates recursive in-order traversal of tree.
// Prints diagnostic information about tree structure.
// Note that this is unreadable on larger trees, use mathematica for that.
// Note that this is an extra diagnostic and may go unused.
void __unused treeDebug (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		subTreeDebug(thisTree->rootNode, 0);
	} else {
		printf("The tree is empty");
	}
	printf("\n");
}

// Recursively prints an in order traversal of the tree to a file (or stdio).
void subTreeFPrint (FILE *fp, BstNode *thisNode) {
	if (thisNode->left != NULL) {
		subTreeFPrint(fp, thisNode->left);
	}

	char *temp = nodeDataToString(thisNode->data);
	fprintf(fp, "%s\n", temp);
	free(temp); // freeing the extra word that's been malloced in nodeDataToString.

	if (thisNode->right != NULL) {
		subTreeFPrint(fp, thisNode->right);
	}
}

// Initiates recursive printing in order traversal of the tree to a file (or stdio).
// Note, may go unused if tree is only for internal utility.
void __unused treeFPrint (FILE *fp, Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		subTreeFPrint(fp, thisTree->rootNode);
	} else {
		fprintf(fp, "The tree is empty.\n");
	}
}\


// Recursively prints relationships between this node and it's children as part of transforming to mathematica's structure.
void subTreeToMathematica (BstNode *thisNode) {
	if (thisNode->left != NULL) {
		char *temp1 = nodeDataKeyToString(thisNode->data), *temp2 = nodeDataKeyToString(thisNode->left->data);
		printf("%s -> %s, ", temp1, temp2);
		free(temp1);
		free(temp2); // freeing the extra word that's been malloced in nodeDataKeyToString.
		subTreeToMathematica(thisNode->left);
	}

	if (thisNode->right != NULL) {
		char *temp1 = nodeDataKeyToString(thisNode->data), *temp2 = nodeDataKeyToString(thisNode->right->data);
		printf("%s -> %s, ", temp1, temp2);
		free(temp1);
		free(temp2); // freeing the extra word that's been malloced in nodeDataKeyToString.
		subTreeToMathematica(thisNode->right);
	}
}

// Transforms this tree's structure into a format that can be executed in mathematica. Prints the function/data to stdio.
// Note that this is an extra diagnostic and may go unused.
void __unused treeToMathematica (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		char *temp = nodeDataKeyToString(thisTree->rootNode->data);
		printf("TreePlot[{root -> %s, ", temp);
		free(temp); // freeing the extra word that's been malloced in nodeDataKeyToString.
		subTreeToMathematica(thisTree->rootNode);
		printf("}, Automatic, root, VertexLabeling -> True, ImageSize -> Full, AspectRatio -> Automatic]");
	} else {
		printf("The tree is empty.");
	}
	printf("\n");
}
