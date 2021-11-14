//
// Created by yarde on 1/1/2020.
//

#ifndef RANK_TREE_SERVER_LIST_H
#define RANK_TREE_SERVER_LIST_H

#include "node.h"
#include <stdbool.h>
typedef class list{
private:
    int list_size;
    Node first;
public:
    list();
    ~list();
    void addItem(Node node);
    void deleteItemById(int server_id);
    Server getItemInList(int server_id);
    Node* getNodeArray();
    int getListSize();
}*List;

#endif //RANK_TREE_SERVER_LIST_H
