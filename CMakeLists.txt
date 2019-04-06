cmake_minimum_required(VERSION 3.13)
project(DataStructure)

set(CMAKE_CXX_STANDARD 14)

add_executable(DataStructure main.cpp Tree/BinSearchTree/BinSearchTree.cpp Tree/MST/MST.cpp Tree/LinkedList/ReverseList.cpp)