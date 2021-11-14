//
// Created by yarde on 1/1/2020.
//

#ifndef RANK_TREE_HASH_TABLE_H

#include "server.h"
#include "list.h"

typedef class hash_table{
private:
    int table_size;
    int number_of_items;
    List* hash_array;
    void resizeTableBigger();
    void resizeTableSmaller();
    void rehash(List *new_hash_array, int old_table_size);
public:
    hash_table();
    ~hash_table();
    int hashFunction(int server_id);
    void insertServer(Server serv);
    void deleteServer(Server serv);
    Server findServerById(int server_id);
    void printHash();
}*HashTable;

#define RANK_TREE_HASH_TABLE_H

#endif //RANK_TREE_HASH_TABLE_H
