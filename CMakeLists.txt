cmake_minimum_required(VERSION 3.27)
project(AVL_tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVL_tree main.cpp
        btree.h
        btree.cpp)