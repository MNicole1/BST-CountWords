//
// Created by Marcello Nicoletti on 1/31/17.
//

#include <stdio.h>
#include "BST.h"

int main () {
	// Test case 1, should produce a balanced tree. This is because keys are inserted in level-order
	printf("\nCase 1: Balanced tree. (due to insertion order)\n");
	Bst *wordTree = newBst();
	incrementOrInsert(wordTree, "mary");
	incrementOrInsert(wordTree, "donna");
	incrementOrInsert(wordTree, "julie");
	incrementOrInsert(wordTree, "trever");
	incrementOrInsert(wordTree, "trever");
	incrementOrInsert(wordTree, "orson");
	incrementOrInsert(wordTree, "orson");
	incrementOrInsert(wordTree, "allison");
	incrementOrInsert(wordTree, "zain");
	debugTree(wordTree);
	printTree(wordTree);
	deleteTree(wordTree);

	// Test case 2, should produce a right skewed tree
	printf("\nCase 2: Right only tree.\n");
	Bst *wordTree2 = newBst();
	incrementOrInsert(wordTree2, "allison");
	incrementOrInsert(wordTree2, "donna");
	incrementOrInsert(wordTree2, "julie");
	incrementOrInsert(wordTree2, "mary");
	incrementOrInsert(wordTree2, "orson");
	incrementOrInsert(wordTree2, "orson");
	incrementOrInsert(wordTree2, "trever");
	incrementOrInsert(wordTree2, "trever");
	incrementOrInsert(wordTree2, "zain");
	debugTree(wordTree2);
	printTree(wordTree2);
	deleteTree(wordTree2);

	// Test case 3, should produce a left skewed tree
	printf("\nCase 3: Left only tree.\n");
	Bst *wordTree3 = newBst();
	incrementOrInsert(wordTree3, "zain");
	incrementOrInsert(wordTree3, "trever");
	incrementOrInsert(wordTree3, "trever");
	incrementOrInsert(wordTree3, "orson");
	incrementOrInsert(wordTree3, "orson");
	incrementOrInsert(wordTree3, "mary");
	incrementOrInsert(wordTree3, "julie");
	incrementOrInsert(wordTree3, "donna");
	incrementOrInsert(wordTree3, "allison");
	debugTree(wordTree3);
	printTree(wordTree3);
	deleteTree(wordTree3);

	// Test case 4, from assignment
	printf("\nCase 4: Tree from assignment.\n");
	Bst *wordTree4 = newBst();
	incrementOrInsert(wordTree4, "now");
	incrementOrInsert(wordTree4, "is");
	incrementOrInsert(wordTree4, "the");
	incrementOrInsert(wordTree4, "time");
	incrementOrInsert(wordTree4, "for");
	incrementOrInsert(wordTree4, "all");
	incrementOrInsert(wordTree4, "good");
	incrementOrInsert(wordTree4, "men");
	incrementOrInsert(wordTree4, "to");
	incrementOrInsert(wordTree4, "come");
	incrementOrInsert(wordTree4, "to");
	incrementOrInsert(wordTree4, "the");
	incrementOrInsert(wordTree4, "aid");
	incrementOrInsert(wordTree4, "of");
	incrementOrInsert(wordTree4, "their");
	incrementOrInsert(wordTree4, "party");
	debugTree(wordTree4);
	printTree(wordTree4);
	deleteTree(wordTree4);

	// Test case 5, empty tree
	printf("\nCase 5: An empty tree.\n");
	Bst *wordTree5 = newBst();
	debugTree(wordTree5);
	printTree(wordTree5);
	deleteTree(wordTree5);

	return (0);
}
