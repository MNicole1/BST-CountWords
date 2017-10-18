#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "BSTNodeData.h"
#include "BSTNode.h"

/**
 * Constructor for BstNode.
 * This sets default values for branch pointers & passes key on to
 * NodeData construction.
 */
BstNode *newBstNode (Key *newKey) {
  BstNode *newNode = (BstNode *)malloc(sizeof(BstNode));

  newNode->data = newNodeData(newKey);
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

/**
 * Destroys this node.
 * This is for use both with remove (as a leaf) and as part of finalizing
 * the tree.
 */
void nodeDestroy (BstNode *thisNode) {
  nodeDataDestroy(thisNode->data);
  free(thisNode);
}

/**
 * Recursively destroys this subtree.
 * Destroys the whole subtree under this node as well as this node.
 * For use as part of finalizing the tree.
 */
void subTreeDestroy (BstNode *thisNode) {
  if (thisNode->left != NULL) {
    subTreeDestroy(thisNode->left);
  }

  if (thisNode->right != NULL) {
    subTreeDestroy(thisNode->right);
  }

  nodeDestroy(thisNode);
}

/**
 * Recursively finds maximum height of this subtree.
 */
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

/**
 * Rotates the subtree about this node.
 * Updates this node's parent
 */
void subTreeRotate (BstNode *thisNode, bool rotateLeft, BstNode *parentNode) {
  bool isLeftChild = thisNode == parentNode->left;

  if (thisNode == NULL) {
    return;
  }

  if (rotateLeft) {
    /* This node (p) gets replaced by its right node (q) */
    /* and becomes that node's new left. */
    /* The old right node's old left (beta) becomes this node's new right. */
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
    /* This node (p) gets replaced by its left node (q) */
    /* and becomes that node's new right. */
    /* The old left node's old right (beta) becomes this node's new left. */
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

/**
 * Checks balance of subtree and performs rotation if needed.
 */
void subTreeCheckBalance (BstNode *thisNode, BstNode *parentNode) {
  int balanceFactor =
      subTreeHeight(thisNode->right) - subTreeHeight(thisNode->left);
  if (balanceFactor < -1) { /* left heavy */
    subTreeRotate(thisNode, ROT_RIGHT, parentNode);
  } else if (balanceFactor > 1) { /* right heavy */
    subTreeRotate(thisNode, ROT_LEFT, parentNode);
  }
}

/**
 * Recursively finds the maximum value in this subtree.
 * Recurses down the right branch to the rightmost item.
 */
NodeData *subTreeMax (BstNode *thisNode) {
  if (thisNode->right == NULL) { /* Base Case, fully right */
    return nodeDataCopy(thisNode->data);
  }

  return subTreeMax(thisNode->right);
}

/**
 * Recursively finds the minimum value in this subtree.
 * Recurses down the left branch to the leftmost item.
 * Also used durring the removal process.
 */
NodeData *subTreeMin (BstNode *thisNode) {
  if (thisNode->left == NULL) { /* Base Case, fully left */
    return nodeDataCopy(thisNode->data);
  }

  return subTreeMin(thisNode->left);
}

/**
 * Recursively counts nodes in this subtree.
 */
int subTreeCount (BstNode *thisNode) {
  if (thisNode == NULL) {
    return 0;
  }

  return subTreeCount(thisNode->left) + subTreeCount(thisNode->right) + 1;
}

/**
 * Recursively traverses in order while adding to the array.
 * This shouldn't be called anywhere but itself or treeToArray()
 */
int subTreeToArray (BstNode *thisNode, NodeData **arrayInProgress,
                    int runningTotal) {
  if (thisNode->left != NULL) {
    runningTotal = subTreeToArray(thisNode->left, arrayInProgress,
                                  runningTotal);
  }

  arrayInProgress[runningTotal++] = nodeDataCopy(thisNode->data);

  if (thisNode->right != NULL) {
    runningTotal = subTreeToArray(thisNode->right, arrayInProgress,
                                  runningTotal);
  }
  return runningTotal;
}

/**
 * Recursively searches for key. If found, calls NodeData's
 * customOnInsertExisting, else creates a new node in correct place.
 * True means key was new, false means it wasn't.
 */
bool subTreeInsert (BstNode *thisNode, Key *testKey) {
  int compared = customComparer(testKey, thisNode->data);

  if (compared < 0) {
    /* insert left */
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
    /* insert right */
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
  } else { /* if (compared == 0) */
    /* This call may do nothing. */
    customOnInsertExisting(thisNode->data);
    return false;
  }
}

/**
 * Recursively searches subtree for key value. If found, calls
 * NodeData's customOnSearchFind, else returns NULL.
 */
NodeData *subTreeSearch (BstNode *thisNode, Key *testKey) {
  if (thisNode == NULL) {
    return NULL;
  }

  int compared = customComparer(testKey, thisNode->data);

  if (compared < 0) {
    /* search left */
    return subTreeSearch(thisNode->left, testKey);
  } else if (compared > 0) {
    /* search right */
    return subTreeSearch(thisNode->right, testKey);
  } else { /* if (compared == 0) */
    customOnSearchFind(thisNode->data); /* This call may do nothing. */
    return nodeDataCopy(thisNode->data);
  }
}

/**
 * Recursively searches for key. When found, return a copy of the removed
 * node data.
 * Assumes node for testKey does exist because treeRemove verifies this first.
 */
bool subTreeRemove (BstNode *thisNode, Key *testKey, BstNode *parentNode) {
  bool isLeftChild = (parentNode->left == thisNode);

  int compared = customComparer(testKey, thisNode->data);
  if (compared < 0) {
    bool didRemove = subTreeRemove(thisNode->left, testKey, thisNode);
    if (didRemove) {
      if (thisNode->left != NULL) {
        subTreeCheckBalance(thisNode->left, thisNode);
      }
    }
    return didRemove;
  } else if (compared > 0) {
    bool didRemove = subTreeRemove(thisNode->right, testKey, thisNode);
    if (didRemove) {
      if (thisNode->right != NULL) {
        subTreeCheckBalance(thisNode->right, thisNode);
      }
    }
    return didRemove;
  } else {
    if (thisNode->left == NULL && thisNode->right == NULL) {
      /* Case 1 */
      nodeDestroy(thisNode);
      if (isLeftChild) {
        parentNode->left = NULL;
      } else {
        parentNode->right = NULL;
      }
    } else if (thisNode->left != NULL && thisNode->right == NULL) {
      /* Case 2: left */
      /* Change this node into it's left. */
      BstNode *toDestroy = thisNode->left;
      nodeDataDestroy(thisNode->data);
      thisNode->data = nodeDataCopy(toDestroy->data);
      thisNode->left = toDestroy->left;
      thisNode->right = toDestroy->right;
      nodeDestroy(toDestroy);
    } else if (thisNode->left == NULL && thisNode->right != NULL) {
      /* Case 2: right */
      /* Change this node into it's right. */
      BstNode *toDestroy = thisNode->right;
      nodeDataDestroy(thisNode->data);
      thisNode->data = nodeDataCopy(toDestroy->data);
      thisNode->left = toDestroy->left;
      thisNode->right = toDestroy->right;
      nodeDestroy(toDestroy);
    } else if (thisNode->left != NULL && thisNode->right != NULL) {
      /* Case 3 */
      nodeDataDestroy(thisNode->data);
      thisNode->data = subTreeMin(thisNode->right);
      Key *newKey = nodeDataGetKey(thisNode->data);
      subTreeRemove(thisNode->right, newKey, thisNode);
    }

    return true;
  }
}

/**
 * Prints diagnostic information about tree structure.
 * Note that this is unreadable on larger trees, use mathematica for that.
 */
void subTreeDebug (BstNode *thisNode, int depth) {
  if (thisNode->left != NULL) {
    printf("(");
    subTreeDebug(thisNode->left, depth + 1);
    printf(") <- ");
  }

  char *temp = nodeDataToString(thisNode->data);
  printf("%d:%s", depth, temp);
  /* freeing the extra word that's been malloced in nodeDataToString. */
  free(temp);

  if (thisNode->right != NULL) {
    printf(" -> (");
    subTreeDebug(thisNode->right, depth + 1);
    printf(")");
  }
}

/**
 * Recursively prints an in order traversal of the
 * subtree to a file (or stdio).
 */
void subTreeFPrint (struct __sFILE *fp, BstNode *thisNode) {
  if (thisNode->left != NULL) {
    subTreeFPrint(fp, thisNode->left);
  }

  char *temp = nodeDataToString(thisNode->data);
  fprintf(fp, "%s\n", temp);
  /* freeing the extra word that's been malloced in nodeDataToString. */
  free(temp);

  if (thisNode->right != NULL) {
    subTreeFPrint(fp, thisNode->right);
  }
}

/**
 * Recursively prints relationships between this node and it's children as
 * part of transforming to mathematica's structure.
 */
void subTreeToMathematica (BstNode *thisNode) {
  if (thisNode->left != NULL) {
    char *temp1 = nodeDataKeyToString(thisNode->data),
        *temp2 = nodeDataKeyToString(thisNode->left->data);
    printf("%s -> %s, ", temp1, temp2);
    /* freeing the extra word that's been malloced in nodeDataKeyToString. */
    free(temp1);
    free(temp2);
    subTreeToMathematica(thisNode->left);
  }

  if (thisNode->right != NULL) {
    char *temp1 = nodeDataKeyToString(thisNode->data),
        *temp2 = nodeDataKeyToString(thisNode->right->data);
    printf("%s -> %s, ", temp1, temp2);
    /* freeing the extra word that's been malloced in nodeDataKeyToString. */
    free(temp1);
    free(temp2);
    subTreeToMathematica(thisNode->right);
  }
}
