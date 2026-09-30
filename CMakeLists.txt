cmake_minimum_required(VERSION 3.29)
project(plantillas_parcial)

set(CMAKE_CXX_STANDARD 14)

add_executable(plantillas_parcial
    persistent_segtree.cpp
    persistent_stack.cpp
    persistent_trie_string.cpp
    persistent_trie_xor.cpp)
