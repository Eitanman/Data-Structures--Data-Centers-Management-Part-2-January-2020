//
// Created by yarde on 1/1/2020.
//

#ifndef RANK_TREE_NODE_H
#define RANK_TREE_NODE_H

#include "server.h"
typedef class node{
private:
    Server server;
    node* previous;
    node* next;
public:
    node(Server serv);
    ~node();
    void setNext(node* node_next);
    node* getNext();
    Server getServer();
}*Node;

#endif //RANK_TREE_NODE_H
