//
// Created by Marcello Nicoletti on 1/31/17.
//

#include <stdio.h>
#include "BST.h"

int main () {
	// Test case 1, should produce a balanced tree. This is because keys are inserted in level-order
	printf("\nCase 1: Balanced tree. (due to insertion order)\n");
	Bst *wordTree = newBst();
	incrementOrInsertRoot(wordTree, "mary");
	incrementOrInsertRoot(wordTree, "donna");
	incrementOrInsertRoot(wordTree, "julie");
	incrementOrInsertRoot(wordTree, "trever");
	incrementOrInsertRoot(wordTree, "trever");
	incrementOrInsertRoot(wordTree, "orson");
	incrementOrInsertRoot(wordTree, "orson");
	incrementOrInsertRoot(wordTree, "allison");
	incrementOrInsertRoot(wordTree, "zain");
	debugTree(wordTree);
	deleteTree(wordTree);

	// Test case 2, should produce a right skewed tree
	printf("\nCase 2: Right only tree.\n");
	Bst *wordTree2 = newBst();
	incrementOrInsertRoot(wordTree2, "allison");
	incrementOrInsertRoot(wordTree2, "donna");
	incrementOrInsertRoot(wordTree2, "julie");
	incrementOrInsertRoot(wordTree2, "mary");
	incrementOrInsertRoot(wordTree2, "orson");
	incrementOrInsertRoot(wordTree2, "orson");
	incrementOrInsertRoot(wordTree2, "trever");
	incrementOrInsertRoot(wordTree2, "trever");
	incrementOrInsertRoot(wordTree2, "zain");
	debugTree(wordTree2);
	deleteTree(wordTree2);

	// Test case 3, should produce a left skewed tree
	printf("\nCase 3: Left only tree.\n");
	Bst *wordTree3 = newBst();
	incrementOrInsertRoot(wordTree3, "zain");
	incrementOrInsertRoot(wordTree3, "trever");
	incrementOrInsertRoot(wordTree3, "trever");
	incrementOrInsertRoot(wordTree3, "orson");
	incrementOrInsertRoot(wordTree3, "orson");
	incrementOrInsertRoot(wordTree3, "mary");
	incrementOrInsertRoot(wordTree3, "julie");
	incrementOrInsertRoot(wordTree3, "donna");
	incrementOrInsertRoot(wordTree3, "allison");
	debugTree(wordTree3);
	deleteTree(wordTree3);

	// Test case 4, from assignment
	printf("\nCase 4: Tree from assignment.\n");
	Bst *wordTree4 = newBst();
	incrementOrInsertRoot(wordTree4, "now");
	incrementOrInsertRoot(wordTree4, "is");
	incrementOrInsertRoot(wordTree4, "the");
	incrementOrInsertRoot(wordTree4, "time");
	incrementOrInsertRoot(wordTree4, "for");
	incrementOrInsertRoot(wordTree4, "all");
	incrementOrInsertRoot(wordTree4, "good");
	incrementOrInsertRoot(wordTree4, "men");
	incrementOrInsertRoot(wordTree4, "to");
	incrementOrInsertRoot(wordTree4, "come");
	incrementOrInsertRoot(wordTree4, "to");
	incrementOrInsertRoot(wordTree4, "the");
	incrementOrInsertRoot(wordTree4, "aid");
	incrementOrInsertRoot(wordTree4, "of");
	incrementOrInsertRoot(wordTree4, "their");
	incrementOrInsertRoot(wordTree4, "party");
	debugTree(wordTree4);
	deleteTree(wordTree4);

	// Test case 5, empty tree
	printf("\nCase 5: An empty tree.\n");
	Bst *wordTree5 = newBst();
	debugTree(wordTree5);
	deleteTree(wordTree5);

	return (0);
}
