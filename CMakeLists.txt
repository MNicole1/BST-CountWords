cmake_minimum_required(VERSION 3.6)
project(BST_MostCommonWord)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(BST_CountWords ${SOURCE_FILES})
add_executable(BST_TestCases BST-TestCases.c BST.c)
