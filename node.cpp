//
// Created by yarde on 1/1/2020.
//
#include "node.h"
node::node(Server serv){
    server = new class server(*serv);
    previous = nullptr;
    next = nullptr;
}
node::~node() {
    delete server;
}
void node::setNext(class node * node_next) {
    this->next = node_next;
}
class node * node::getNext() {
    return next;
}
Server node::getServer() {
    return this->server;
}