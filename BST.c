/**
 * This is an implementation of a binary search tree.
 * It has been made fairly generically and its value data type can
 * be changed by changing the nodeDataType struct in BSTNodeData.h
 * When adding functions make sure to make them agnostic to
 * the datatype of the data member.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BSTNode.h"
#include "BST.h"

/* TODO: "Methods" don't check if their "thisX" is null. */

/**
 * Constructor for Bst.
 * This sets default values.
 */
Bst *newBst () {
  Bst *tree = (Bst *)malloc(sizeof(Bst));

  tree->rootNode = NULL;
  tree->size = 0;

  return tree;
}

/**
 * Recursively destroys this tree.
 * Finalizes the tree, completely freeing it.
 */
void treeDestroy (Bst *thisTree) {
  if (thisTree->rootNode != NULL) {
    subTreeDestroy(thisTree->rootNode);
  }
  free(thisTree);
}

/**
 * Recursively finds maximum height of this tree.
 */
int treeHeight (Bst *thisTree) {
  if (thisTree->rootNode == NULL) {
    return 0;
  }

  return subTreeHeight(thisTree->rootNode);
}

/**
 * Rotates the tree about it's root.
 */
void treeRotate (Bst *thisTree, bool rotateLeft) {
  BstNode *rootNode = thisTree->rootNode;

  if (rootNode == NULL) {
    return;
  }

  if (rotateLeft) {
    /* This node (p) gets replaced by its right node (q) and becomes that
     * node's new left. The old right node's old left (beta) becomes this
     * node's new right. */
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
    /* This node (p) gets replaced by its left node (q) and becomes that
     * node's new right. The old left node's old right (beta) becomes this
     * node's new left. */
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

/**
 * Checks balance of tree and performs rotation if needed.
 */
void treeCheckBalance (Bst *thisTree) {
  BstNode *rootNode = thisTree->rootNode;

  int balanceFactor =
      subTreeHeight(rootNode->right) - subTreeHeight(rootNode->left);
  if (balanceFactor < -1) { /* left heavy */
    treeRotate(thisTree, ROT_RIGHT);
  } else if (balanceFactor > 1) { /* right heavy */
    treeRotate(thisTree, ROT_LEFT);
  }
}

/**
 * Recursively finds the maximum value in this tree.
 * Recurses down the right branch to the rightmost item.
 */
NodeData *treeMax (Bst *thisTree) {
  if (thisTree->rootNode == NULL) {
    return NULL;
  }
  return subTreeMax(thisTree->rootNode);
}

/**
 * Recursively finds the minimum value in this tree.
 * Recurses down the left branch to the leftmost item.
 */
NodeData *treeMin (Bst *thisTree) {
  if (thisTree->rootNode == NULL) {
    return NULL;
  }
  return subTreeMin(thisTree->rootNode);
}

/**
 * Recursively counts nodes in this tree.
 */
int treeCount (Bst *thisTree) {
  if (thisTree->rootNode == NULL) {
    return 0;
  }

  return subTreeCount(thisTree->rootNode);
}

/**
 * Destroys the array created by treeToArray.
 */
void treeArrayDestroy (NodeData **array, int size) {
  NodeData *thisNode;
  for (int i = 0; i < size; i++) {
    thisNode = array[i];
    nodeDataDestroy(thisNode);
  }
  free(array);
}

/**
 * Returns the tree in order as an array of NodeData pointers to copies
 * of the node's data.
 * Needs to be freed after use.
 */
NodeData **treeToArray (Bst *thisTree) {
  if (thisTree->rootNode == NULL) {
    return NULL;
  }
  NodeData **array = (NodeData **)malloc(sizeof(NodeData) * thisTree->size);
  subTreeToArray(thisTree->rootNode, array, 0);
  return array;
}

/**
 * Inserts new nodes into tree.
 * Maintains the count.
 */
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

/**
 * Recursively searcehs tree for key value.
 * Note that this creates a copy that will need to be freed by the caller.
 */
NodeData *treeSearch (Bst *thisTree, Key *testKey) {
  if (thisTree->rootNode == NULL) {
    return NULL;
  }

  return subTreeSearch(thisTree->rootNode, testKey);
}

/**
 * Removes nodes from tree.
 * Note that this creates a copy that will need to be freed by the caller.
 */
NodeData *treeRemove (Bst *thisTree, Key *testKey) {
  BstNode *rootNode = thisTree->rootNode;
  if (rootNode == NULL) {
    return NULL;
  }

  /* Ensure it exists. Grab it's current state if so. */
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
      /* Case 1 */
      nodeDestroy(rootNode);
      thisTree->rootNode = NULL;
    } else if (rootNode->left != NULL && rootNode->right == NULL) {
      /* Case 2: left. Change this node into it's left. */
      BstNode *toDestroy = rootNode->left;
      nodeDataDestroy(rootNode->data);
      rootNode->data = nodeDataCopy(toDestroy->data);
      rootNode->left = toDestroy->left;
      rootNode->right = toDestroy->right;
      nodeDestroy(toDestroy);
    } else if (rootNode->left == NULL && rootNode->right != NULL) {
      /* Case 2: right. Change this node into it's right. */
      BstNode *toDestroy = rootNode->right;
      nodeDataDestroy(rootNode->data);
      rootNode->data = nodeDataCopy(toDestroy->data);
      rootNode->left = toDestroy->left;
      rootNode->right = toDestroy->right;
      nodeDestroy(toDestroy);
    } else if (rootNode->left != NULL && rootNode->right != NULL) {
      /* Case 3 */
      nodeDataDestroy(rootNode->data);
      rootNode->data = subTreeMin(rootNode->right);
      Key *newKey = nodeDataGetKey(rootNode->data);
      subTreeRemove(rootNode->right, newKey, rootNode);
      free(newKey);
    }
  }

  treeCheckBalance(thisTree);
  thisTree->size--;
  /* return the state of the node data from before it was removed. */
  return toReturn;
}

/**
 * Prints diagnostic information about tree structure.
 * Note that this is unreadable on larger trees, use ToMathematica for that.
 */
void treeDebug (Bst *thisTree) {
  if (thisTree->rootNode != NULL) {
    subTreeDebug(thisTree->rootNode, 0);
  } else {
    printf("The tree is empty");
  }
  printf("\n");
}

/**
 * Initiates recursive printing in order traversal of the tree to a file
 * (or stdio).
 */
void treeFPrint (FILE *fp, Bst *thisTree) {
  if (thisTree->rootNode != NULL) {
    subTreeFPrint(fp, thisTree->rootNode);
  } else {
    fprintf(fp, "The tree is empty.\n");
  }
}\


/**
 * Transforms this tree's structure into a format that can be executed in
 * mathematica.
 */
void treeToMathematica (Bst *thisTree) {
  if (thisTree->rootNode != NULL) {
    char *temp = nodeDataKeyToString(thisTree->rootNode->data);
    printf("TreePlot[{root -> %s, ", temp);
    /* freeing the extra word that's been malloced in nodeDataKeyToString. */
    free(temp);
    subTreeToMathematica(thisTree->rootNode);
    /* "\b\b" removes the last extra ", " */
    printf(
      "\b\b}, Top, root, VertexLabeling -> False, ImageSize -> {720, 300}]");
  } else {
    printf("The tree is empty.");
  }
  printf("\n");
}
