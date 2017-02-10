cmake_minimum_required(VERSION 3.6)
project(BST_MostCommonWord)

set(CMAKE_C_STANDARD 11)

set(TREE_SOURCE_FILES BST.c BST.h BSTNode.c BSTNode.h BSTNodeData.c BSTNodeData.h)
set(MAIN_SOURCE_FILES main.c ${TREE_SOURCE_FILES})
set(TEST_SOURCE_FILES BST-TestCases.c ${TREE_SOURCE_FILES})

add_executable(BST_CountWords ${MAIN_SOURCE_FILES})
add_executable(BST_TestCases ${TEST_SOURCE_FILES})
