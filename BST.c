/**
 * This is an implementation of a binary search tree.
 * It has been made fairly generically and its value data type can be changed by changing the nodeDataType struct in BSENodeData.c/
 * When adding functions make sure to make them agnostic to the datatype of the data member.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BSTNodeData.h"
#include "BST.h"

// TODO: Implement rotation on insert/remove to allow for self balancing trees.
// TODO: "Methods" don't check of their "thisX" is null.

/// Constructor for Bst.
/// This sets default values.
Bst *newBst () {
	Bst *tree = (Bst *)malloc(sizeof(Bst));

	tree->rootNode = NULL;
	tree->size = 0;

	return tree;
}

/// Constructor for BstNode.
/// This sets default values for branch pointers & passes key on to NodeData construction.
BstNode *newBstNode (Key *newKey) {
	BstNode *newNode = (BstNode *)malloc(sizeof(BstNode));

	newNode->data = newNodeData(newKey);
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

/// Destroys this node.
/// This is for use both with remove (as a leaf) and as part of finalizing the tree.
void nodeDestroy (BstNode *thisNode) {
	nodeDataDestroy(thisNode->data);
	free(thisNode);
}

/// Recursively destroys this subtree.
/// Destroys the whole subtree under this node as well as this node.
/// For use as part of finalizing the tree.
void subTreeDestroy (BstNode *thisNode) {
	if (thisNode->left != NULL) {
		subTreeDestroy(thisNode->left);
	}

	if (thisNode->right != NULL) {
		subTreeDestroy(thisNode->right);
	}

	nodeDestroy(thisNode);
}

/// Recursively destroys this tree.
/// Finalizes the tree, completely freeing it.
void treeDestroy (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		subTreeDestroy(thisTree->rootNode);
	}
	free(thisTree);
}

/// Recursively finds maximum height of this subtree.
int subTreeHeight (BstNode *thisNode) {
	if (thisNode == NULL) {
		return 0;
	}

	int leftHeight = subTreeHeight(thisNode->left);
	int rightHeight = subTreeHeight(thisNode->right);

	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	} else {
		return rightHeight + 1;
	}
}

/// Recursively finds maximum height of this tree.
int __unused treeHeight (Bst *thisTree) {
	if (thisTree->rootNode == NULL) {
		return 0;
	}

	return subTreeHeight(thisTree->rootNode);
}

/// Rotates the subtree about this node.
/// Updates this node's parent
void subTreeRotate (BstNode *thisNode, bool rotateLeft, BstNode *parentNode) {
	bool isLeftChild = thisNode == parentNode->left;

	if (thisNode == NULL) {
		return;
	}

	if (rotateLeft) {
		// This node (p) gets replaced by its right node (q) and becomes that node's new left.
		// The old right node's old left (beta) becomes this node's new right.
		BstNode *p = thisNode;
		BstNode *q = thisNode->right;
		if (q == NULL) {
			return;
		}
		BstNode *beta = q->left;

		p->right = beta;
		q->left = p;
		if (isLeftChild) {
			parentNode->left = q;
		} else {
			parentNode->right = q;
		}
	} else {
		// This node (p) gets replaced by its left node (q) and becomes that node's new right.
		// The old left node's old right (beta) becomes this node's new left.
		BstNode *p = thisNode;
		BstNode *q = thisNode->left;
		if (q == NULL) {
			return;
		}
		BstNode *beta = q->right;

		p->left = beta;
		q->right = p;
		if (isLeftChild) {
			parentNode->left = q;
		} else {
			parentNode->right = q;
		}
	}
}

/// Rotates the tree about it's root.
void treeRotate (Bst *thisTree, bool rotateLeft) {
	BstNode *rootNode = thisTree->rootNode;

	if (rootNode == NULL) {
		return;
	}

	if (rotateLeft) {
		// This node (p) gets replaced by its right node (q) and becomes that node's new left.
		// The old right node's old left (beta) becomes this node's new right.
		BstNode *p = rootNode;
		BstNode *q = rootNode->right;
		if (q == NULL) {
			return;
		}
		BstNode *beta = q->left;

		p->right = beta;
		q->left = p;
		thisTree->rootNode = q;
	} else {
		// This node (p) gets replaced by its left node (q) and becomes that node's new right.
		// The old left node's old right (beta) becomes this node's new left.
		BstNode *p = rootNode;
		BstNode *q = rootNode->left;
		if (q == NULL) {
			return;
		}
		BstNode *beta = q->right;

		p->left = beta;
		q->right = p;
		thisTree->rootNode = q;
	}

}

/// Checks balance of subtree and performs rotation if needed.
void subTreeCheckBalance (BstNode *thisNode, BstNode *parentNode) {
	int balanceFactor = subTreeHeight(thisNode->right) - subTreeHeight(thisNode->left);
	if (balanceFactor < -1) { // left heavy
		subTreeRotate(thisNode, ROT_RIGHT, parentNode);
	} else if (balanceFactor > 1) { // right heavy
		subTreeRotate(thisNode, ROT_LEFT, parentNode);
	}
}

/// Checks balance of tree and performs rotation if needed.
void treeCheckBalance (Bst *thisTree) {
	BstNode *rootNode = thisTree->rootNode;

	int balanceFactor = subTreeHeight(rootNode->right) - subTreeHeight(rootNode->left);
	if (balanceFactor < -1) { // left heavy
		treeRotate(thisTree, ROT_RIGHT);
	} else if (balanceFactor > 1) { // right heavy
		treeRotate(thisTree, ROT_LEFT);
	}
}

/// Recursively finds the maximum value in this subtree.
/// Recurses down the right branch to the rightmost item.
NodeData *subTreeMax (BstNode *thisNode) {
	if (thisNode->right == NULL) { // Base Case, fully right
		return nodeDataCopy(thisNode->data);
	}

	return subTreeMax(thisNode->right);
}

/// Recursively finds the maximum value in this tree.
/// Recurses down the right branch to the rightmost item.
NodeData  __unused *treeMax (Bst *thisTree) {
	if (thisTree->rootNode == NULL) {
		return NULL;
	}
	return subTreeMax(thisTree->rootNode);
}

/// Recursively finds the minimum value in this subtree.
/// Recurses down the left branch to the leftmost item.
/// Also used durring the removal process.
NodeData *subTreeMin (BstNode *thisNode) {
	if (thisNode->left == NULL) { // Base Case, fully left
		return nodeDataCopy(thisNode->data);
	}

	return subTreeMin(thisNode->left);
}

/// Recursively finds the minimum value in this tree.
/// Recurses down the left branch to the leftmost item.
NodeData  __unused *treeMin (Bst *thisTree) {
	if (thisTree->rootNode == NULL) {
		return NULL;
	}
	return subTreeMin(thisTree->rootNode);
}

/// Recursively counts nodes in this subtree.
int subTreeCount (BstNode *thisNode) {
	if (thisNode == NULL) {
		return 0;
	}

	return subTreeCount(thisNode->left) + subTreeCount(thisNode->right) + 1;
}

/// Recursively counts nodes in this tree.
int __unused treeCount (Bst *thisTree) {
	if (thisTree->rootNode == NULL) {
		return 0;
	}

	return subTreeCount(thisTree->rootNode);
}

/// Destroys the array created by treeToArray.
void __unused treeArrayDestroy (NodeData **array, int size) {
	NodeData *thisNode;
	for (int i = 0; i < size; i++) {
		thisNode = array[i];
		nodeDataDestroy(thisNode);
	}
	free(array);
}

/// Recursively traverses in order while adding to the array.
/// This shouldn't be called anywhere but itself or treeToArray()
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

/// Returns the tree in order as an array of NodeData pointers to copies of the node's data.
/// Needs to be
NodeData __unused **treeToArray (Bst *thisTree) {
	if (thisTree->rootNode == NULL) {
		return NULL;
	}
	NodeData **array = (NodeData **)malloc(sizeof(NodeData) * thisTree->size);
	subTreeToArray(thisTree->rootNode, array, 0);
	return array;
}

/// Recursively searches for key. If found, calls NodeData's customOnInsertExisting, else creates a new node in correct place.
/// True means key was new, false means it wasn't.
/// Coming soon: Keeps tree balanced by performing rotations as needed.
bool subTreeInsert (BstNode *thisNode, Key *testKey) {
	int compared = customComparer(testKey, thisNode->data);

	if (compared < 0) {
		// insert left
		if (thisNode->left == NULL) {
			thisNode->left = newBstNode(testKey);
			return true;
		} else {
			bool didInsert = subTreeInsert(thisNode->left, testKey);
			if (didInsert) {
				subTreeCheckBalance(thisNode->left, thisNode);
			}
			return didInsert;
		}
	} else if (compared > 0) {
		// insert right
		if (thisNode->right == NULL) {
			thisNode->right = newBstNode(testKey);
			return true;
		} else {
			bool didInsert = subTreeInsert(thisNode->right, testKey);
			if (didInsert) {
				subTreeCheckBalance(thisNode->right, thisNode);
			}
			return didInsert;
		}
	} else { // if (compared == 0)
		customOnInsertExisting(thisNode->data); // This call may do nothing.
		return false;
	}
}

/// Inserts new nodes into tree.
/// Maintains the count.
bool treeInsert (Bst *thisTree, Key *testKey) {
	if (thisTree->rootNode == NULL) {
		thisTree->rootNode = newBstNode(testKey);
		thisTree->size = 1;
		return true;
	} else {
		bool didInsert = subTreeInsert(thisTree->rootNode, testKey);
		if (didInsert) {
			thisTree->size++;
			treeCheckBalance(thisTree);
		}
		return didInsert;
	}
}

/// Recursively searches subtree for key value. If found, calls NodeData's customOnSearchFind, else returns NULL.
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

/// Recursively searcehs tree for key value.
/// Note that this creates a copy that will need to be freed by the caller.
NodeData  __unused *treeSearch (Bst *thisTree, Key *testKey) {
	if (thisTree->rootNode == NULL) {
		return NULL;
	}

	return subTreeSearch(thisTree->rootNode, testKey);
}

/// Recursively searches for key. If found, return a copy of the removed node data, else returns NULL.
/// Assumes node for testKey does exist because treeRemove verifies this first.
bool subTreeRemove (BstNode *thisNode, Key *testKey, BstNode *parentNode) {
	bool isLeftChild = (parentNode->left == thisNode);

	int compared = customComparer(testKey, thisNode->data);
	if (compared < 0) {
		bool didRemove = subTreeRemove(thisNode->left, testKey, thisNode);
		if (didRemove) {
			if (thisNode->left !=NULL) {
				 subTreeCheckBalance(thisNode->left, thisNode);
			}
		}
		return didRemove;
	} else if (compared > 0) {
		bool didRemove = subTreeRemove(thisNode->right, testKey, thisNode);
		if (didRemove) {
			if (thisNode->right !=NULL) {
				subTreeCheckBalance(thisNode->right, thisNode);
			}
		}
		return didRemove;
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
}

/// Removes nodes from tree.
/// Note that this creates a copy that will need to be freed by the caller.
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

	treeCheckBalance(thisTree);
	thisTree->size--;
	return toReturn; // return the state of the node data from before it was removed.
}

/// Prints diagnostic information about tree structure.
/// Note that this is unreadable on larger trees, use mathematica for that.
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

/// Prints diagnostic information about tree structure.
/// Note that this is unreadable on larger trees, use ToMathematica for that.
void __unused treeDebug (Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		subTreeDebug(thisTree->rootNode, 0);
	} else {
		printf("The tree is empty");
	}
	printf("\n");
}

/// Recursively prints an in order traversal of the subtree to a file (or stdio).
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

/// Initiates recursive printing in order traversal of the tree to a file (or stdio).
void __unused treeFPrint (FILE *fp, Bst *thisTree) {
	if (thisTree->rootNode != NULL) {
		subTreeFPrint(fp, thisTree->rootNode);
	} else {
		fprintf(fp, "The tree is empty.\n");
	}
}\


/// Recursively prints relationships between this node and it's children as part of transforming to mathematica's structure.
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

/// Transforms this tree's structure into a format that can be executed in mathematica.
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
