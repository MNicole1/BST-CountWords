//
// Created by Marcello Nicoletti on 1/31/17.
//

#include <stdio.h>
#include "BST.h"

int main () {
	// Test case 1, should produce a balanced tree. This is because keys are inserted in level-order
	printf("\nCase 1: Balanced tree. (due to insertion order)\n");
	Bst *wordTree = newBst();
	treeInsert(wordTree, "mary");
	treeInsert(wordTree, "donna");
	treeInsert(wordTree, "julie");
	treeInsert(wordTree, "trever");
	treeInsert(wordTree, "trever");
	treeInsert(wordTree, "orson");
	treeInsert(wordTree, "orson");
	treeInsert(wordTree, "allison");
	treeInsert(wordTree, "zain");
	treeDebug(wordTree);
	treePrint(stdout, wordTree);
	treeDestroy(wordTree);

	// Test case 2, should produce a right skewed tree
	printf("\nCase 2: Right only tree.\n");
	Bst *wordTree2 = newBst();
	treeInsert(wordTree2, "allison");
	treeInsert(wordTree2, "donna");
	treeInsert(wordTree2, "julie");
	treeInsert(wordTree2, "mary");
	treeInsert(wordTree2, "orson");
	treeInsert(wordTree2, "orson");
	treeInsert(wordTree2, "trever");
	treeInsert(wordTree2, "trever");
	treeInsert(wordTree2, "zain");
	treeDebug(wordTree2);
	treePrint(stdout, wordTree2);
	treeDestroy(wordTree2);

	// Test case 3, should produce a left skewed tree
	printf("\nCase 3: Left only tree.\n");
	Bst *wordTree3 = newBst();
	treeInsert(wordTree3, "zain");
	treeInsert(wordTree3, "trever");
	treeInsert(wordTree3, "trever");
	treeInsert(wordTree3, "orson");
	treeInsert(wordTree3, "orson");
	treeInsert(wordTree3, "mary");
	treeInsert(wordTree3, "julie");
	treeInsert(wordTree3, "donna");
	treeInsert(wordTree3, "allison");
	treeDebug(wordTree3);
	treePrint(stdout, wordTree3);
	treeDestroy(wordTree3);

	// Test case 4, from assignment
	printf("\nCase 4: Tree from assignment.\n");
	Bst *wordTree4 = newBst();
	treeInsert(wordTree4, "now");
	treeInsert(wordTree4, "is");
	treeInsert(wordTree4, "the");
	treeInsert(wordTree4, "time");
	treeInsert(wordTree4, "for");
	treeInsert(wordTree4, "all");
	treeInsert(wordTree4, "good");
	treeInsert(wordTree4, "men");
	treeInsert(wordTree4, "to");
	treeInsert(wordTree4, "come");
	treeInsert(wordTree4, "to");
	treeInsert(wordTree4, "the");
	treeInsert(wordTree4, "aid");
	treeInsert(wordTree4, "of");
	treeInsert(wordTree4, "their");
	treeInsert(wordTree4, "party");
	treeDebug(wordTree4);
	treePrint(stdout, wordTree4);
	treeDestroy(wordTree4);

	// Test case 5, empty tree
	printf("\nCase 5: An empty tree.\n");
	Bst *wordTree5 = newBst();
	treeDebug(wordTree5);
	treePrint(stdout, wordTree5);
	treeDestroy(wordTree5);

	return (0);
}
