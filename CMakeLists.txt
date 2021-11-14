cmake_minimum_required(VERSION 3.13)
project(ex2)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex2 main.cpp Tree_1.h Keys.cpp Keys.h UpTree.cpp UpTree.h DataCenterManager.h DataCenterManager.cpp
        hash_table.h hash_table.cpp library.cpp library2.h list.h list.cpp node.h node.cpp server.cpp server.h)