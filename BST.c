#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BST.h"
#include "BSTNodeData.h"

// TODO: Create remove() functions for a more complete bin tree implementation.
// TODO: Implement rotation on insert/remove to allow for self balancing trees.
// TODO: "Methods" don't check of their "thisX" is null.

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
		return nodeDataCopy(thisNode->data);
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
		return nodeDataCopy(thisNode->data);
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

	arrayInProgress[runningTotal++] = nodeDataCopy(thisNode->data);

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

	// TODO: Check Balance here.
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

	// TODO: Check Balance here.
}

// Recursively searches for key. If found, calls NodeData's customOnSearchFind, else returns NULL.
NodeData *subTreeSearch (BstNode *thisNode, Key *testKey) {
	if (thisNode == NULL) {
		return NULL;
	}

	int compared = customComparer(testKey, thisNode->data);

	if (compared < 0) {
		// search left
		return subTreeSearch(thisNode->left, testKey);
	} else if (compared > 0) {
		// search right
		return subTreeSearch(thisNode->right, testKey);
	} else { // if (compared == 0)
		customOnSearchFind(thisNode->data); // This call may do nothing.
		return nodeDataCopy(thisNode->data);
	}
}

// Starts recursive search process.
// Note that this creates a copy that will need to be freed by the caller.
NodeData  __unused *treeSearch (Bst *thisTree, Key *testKey) {
	if (thisTree->rootNode == NULL) {
		return NULL;
	}

	return subTreeSearch(thisTree->rootNode, testKey);
}

// Recursively searches for key. If found, there are a few cases, return a copy of the removed node data, else returns NULL.
// Must operate from the parent of the found node.
// Cases:
// 1) Found node has no children. Easy, set parent's pointer to NULL and nodeDestroy() the found node.
// 2) Node has 1 child. Easy, set parent's pointer to the child and nodeDestroy() the found node.
// 3) Node has 2 children. Hard, Swap the data of this node and the next biggest (subTreeMin(thisNode->right)), recurse down right.
//    * Eventually case 1 or 2 will be hit by further recursion.
bool subTreeRemove (BstNode *thisNode, Key *testKey, BstNode *parentNode) {
	bool isLeftChild = (parentNode->left == thisNode);

	int compared = customComparer(testKey, thisNode->data);
	if (compared < 0) {
		return subTreeRemove(thisNode->left, testKey, thisNode);
	} else if (compared > 0) {
		return subTreeRemove(thisNode->right, testKey, thisNode);
	} else {
		if (thisNode->left == NULL && thisNode->right == NULL) {
			// Case 1
			nodeDestroy(thisNode);
			if (isLeftChild) {
				parentNode->left = NULL;
			} else {
				parentNode->right = NULL;
			}
		} else if (thisNode->left != NULL && thisNode->right == NULL) {
			// Case 2: left
			// Change this node into it's left.
			BstNode *toDestroy = thisNode->left;
			nodeDataDestroy(thisNode->data);
			thisNode->data = nodeDataCopy(toDestroy->data);
			thisNode->left = toDestroy->left;
			thisNode->right = toDestroy->right;
			nodeDestroy(toDestroy);
		} else if (thisNode->left == NULL && thisNode->right != NULL) {
			// Case 2: right
			// Change this node into it's right.
			BstNode *toDestroy = thisNode->right;
			nodeDataDestroy(thisNode->data);
			thisNode->data = nodeDataCopy(toDestroy->data);
			thisNode->left = toDestroy->left;
			thisNode->right = toDestroy->right;
			nodeDestroy(toDestroy);
		} else if (thisNode->left != NULL && thisNode->right != NULL) {
			// Case 3
			nodeDataDestroy(thisNode->data);
			thisNode->data = subTreeMin(thisNode->right);
			Key *newKey = nodeDataGetKey(thisNode->data);
			subTreeRemove(thisNode->right, newKey, thisNode);
		}

		return true;
	}

	// TODO: Check Balance here.
}

// Starts recursive removal process.
// Note that this creates a copy that will need to be freed by the caller.
// Cases:
// 1) Found node has no children. Easy, set rootNode pointer to NULL and nodeDestroy() the found node.
// 2) Node has 1 child. Easy, set return pointer to the child and nodeDestroy() the found node.
// 3) Node has 2 children. Hard, nodeDataDestroy this data, copy the data of the next biggest
// (subTreeMin(rootNode->right)), recurse down right with key from new data.
NodeData  __unused *treeRemove (Bst *thisTree, Key *testKey) {
	BstNode *rootNode = thisTree->rootNode;
	if (rootNode == NULL) {
		return NULL;
	}

	// Ensure it exists. Grab it's current state if so.
	NodeData *toReturn = subTreeSearch(rootNode, testKey);
	if (toReturn == NULL) {
		return NULL;
	}

	int compared = customComparer(testKey, rootNode->data);
	if (compared < 0) {
		subTreeRemove(rootNode->left, testKey, rootNode);
	} else if (compared > 0) {
		subTreeRemove(rootNode->right, testKey, rootNode);
	} else {
		if (rootNode->left == NULL && rootNode->right == NULL) {
			// Case 1
			nodeDestroy(rootNode);
			thisTree->rootNode = NULL;
		} else if (rootNode->left != NULL && rootNode->right == NULL) {
			// Case 2: left
			// Change this node into it's left.
			BstNode *toDestroy = rootNode->left;
			nodeDataDestroy(rootNode->data);
			rootNode->data = nodeDataCopy(toDestroy->data);
			rootNode->left = toDestroy->left;
			rootNode->right = toDestroy->right;
			nodeDestroy(toDestroy);
		} else if (rootNode->left == NULL && rootNode->right != NULL) {
			// Case 2: right
			// Change this node into it's right.
			BstNode *toDestroy = rootNode->right;
			nodeDataDestroy(rootNode->data);
			rootNode->data = nodeDataCopy(toDestroy->data);
			rootNode->left = toDestroy->left;
			rootNode->right = toDestroy->right;
			nodeDestroy(toDestroy);
		} else if (rootNode->left != NULL && rootNode->right != NULL) {
			// Case 3
			nodeDataDestroy(rootNode->data);
			rootNode->data = subTreeMin(rootNode->right);
			Key *newKey = nodeDataGetKey(rootNode->data);
			subTreeRemove(rootNode->right, newKey, rootNode);
		}
	}

	// TODO: Check Balance here.

	thisTree->size--;
	return toReturn; // return the state of the node data from before it was removed.
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
