//
// Created by yarde on 1/1/2020.
//
#include "list.h"
list::list() {
    list_size =0;
    first = nullptr;
}
void list::addItem(Node node) {
    if(list_size == 0){
        first = node;
        node->setNext(nullptr);
        list_size++;
        return;
    }
    if(list_size == 1){
        first->setNext(node);
        node->setNext(nullptr);
        list_size++;
        return;
    }
    // there are at least two items in the list
    Node curr_node = first;
    while(curr_node->getNext()!= nullptr) {
        curr_node = curr_node->getNext();
    }
    curr_node->setNext(node);
    list_size++;
}
void list::deleteItemById(int server_id) {
    if (list_size == 0){
        return;
    }
    if(list_size==1){
        if(first->getServer()->getServerId() == server_id ) {
            delete first;
            first = nullptr;
            list_size--;
            return;
        }
    }
    Node curr_node = first;
    Node prev_node = nullptr;
    while(curr_node->getNext()!= nullptr){
        if(curr_node->getServer()->getServerId() == server_id){
            if(prev_node == nullptr){//then wer'e deleting the first element
                first = curr_node->getNext();
                delete curr_node;
                list_size--;
                return;
            }
            prev_node->setNext(curr_node->getNext());
            delete curr_node;
            list_size--;
        }
        prev_node = curr_node;
        curr_node = curr_node->getNext();
    }
}
Server list::getItemInList(int server_id) {//return nullptr if item not in list otherwise return the server
    if(list_size == 0){
        return nullptr;
    }
    if(list_size == 1){
        if(first->getServer()->getServerId() == server_id){
            return first->getServer();
        }
    }
    Node curr_node = first;
    while(curr_node->getNext()!= nullptr) {
        if (curr_node->getServer()->getServerId() == server_id) {
            return curr_node->getServer();
        }
        curr_node = curr_node->getNext();
    }
    return nullptr;
}
int list::getListSize() {
    return list_size;
}
Node * list::getNodeArray() {
    if(list_size == 0){
        return nullptr;
    }
    Node* node_array = new Node[list_size];
    Node curr = first;
    int i=0;
    node_array[i] = curr;//does this incase there's only one element
    while(curr->getNext()!= nullptr){
        node_array[i] = curr;
        i++;
        curr = curr->getNext();
    }
    node_array[i] = curr;
    return node_array;
}
list::~list() {
    if(list_size == 0){
        return;
    }
    Node curr = first;
    Node to_delete = curr;
    while(curr->getNext() != nullptr){
        to_delete = curr;
        curr = curr->getNext();
        delete to_delete;
    }
    //deleting last element
    delete curr;
}