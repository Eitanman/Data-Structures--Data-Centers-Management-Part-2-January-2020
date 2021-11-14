//
// Created by yarde on 1/1/2020.
//
#include "hash_table.h"
#include <iostream>
hash_table::hash_table() {
    try{
        table_size = 11;
        hash_array = new List[11];
        number_of_items = 0;
        for (int i = 0; i < table_size; i++) {
            hash_array[i] = new list();
        }
    }
    catch(std::bad_alloc &e){
        throw std::bad_alloc();
    }
}
int hash_table::hashFunction(int server) {
    return server%table_size;
}
Server hash_table::findServerById(int server_id) {// return nullptr if server isn't in hash table. otherwise returns the server
    int index = hashFunction(server_id);
    return hash_array[index]->getItemInList(server_id);
}
void hash_table::insertServer(Server serv) {
    try {
        if (number_of_items + 1 >= table_size / 2) {
            resizeTableBigger();
        }
        int index = hashFunction(serv->getServerId());
        Node new_node = new node(serv); // dynamically distributed memory with node cpy ctor
        hash_array[index]->addItem(new_node);
        number_of_items++;
    }
    catch (std::bad_alloc &e){
        throw std::bad_alloc();
    }
}
void hash_table::deleteServer(Server serv) {
    int index  = hashFunction(serv->getServerId());
    hash_array[index]->deleteItemById(serv->getServerId());
    number_of_items--;
    if(number_of_items < table_size/4){
        resizeTableSmaller();
    }
}
void hash_table::resizeTableBigger() {
    try {
        int old_table_size = table_size;
        table_size = table_size * 2;
        List *new_array = new List[table_size];
        for (int i = 0; i < table_size; ++i) {
            new_array[i] = new list();
        }
        rehash(new_array, old_table_size);
        delete[] hash_array;// this is after deleting the lists themselves
        hash_array = new_array;
    }
    catch(std::bad_alloc &e){
        throw std::bad_alloc();
    }
}
void hash_table::resizeTableSmaller() {
    try {
        int old_table_size = table_size;
        table_size = table_size / 2;
        List *new_array = new List[table_size];
        for (int i = 0; i < table_size; ++i) {
            new_array[i] = new list();
        }
        rehash(new_array, old_table_size);
        delete[] hash_array;// this is after deleting the lists themselves
        hash_array = new_array;
    }
    catch(std::bad_alloc &e){
        throw std::bad_alloc();
    }
}

void hash_table::rehash(List *new_hash_array , int old_table_size){
    try {
        for (int i = 0; i < old_table_size; i++) {
            Node *node_array = hash_array[i]->getNodeArray();
            int array_size = hash_array[i]->getListSize();
            for (int j = 0; j < array_size; ++j) {
                if (j == 1 && i == 2)
                    std::cout << "!";
                int new_index = hashFunction(node_array[j]->getServer()->getServerId());
                Node new_node = new node(node_array[j]->getServer());
                new_hash_array[new_index]->addItem(
                        new_node); // I don't think it allocates memory dynamically here, only uses existing memory
            }
            delete[] node_array;
        }
        for (int i = 0; i < old_table_size; ++i) {
            delete hash_array[i]; // deletes all lists with their nodes
        }
    }
    catch(std::bad_alloc &e){
        throw std::bad_alloc();
    }
}
void hash_table::printHash() {
    for(int i=0;i<table_size;i++){
        std::cout<<" number of entry in hash table: "<<i<<"\n";
        Node* node_array = (hash_array[i])->getNodeArray();
        for(int j=0;j<hash_array[i]->getListSize();++j){
            if(j==1)
                std::cout<<"!";
            Server curr_server = node_array[j]->getServer();
            std::cout<<"server id:"<<curr_server->getServerId()<<"\n";
        }
        delete [] node_array;
    }
}
hash_table::~hash_table(){
    for(int i=0;i<table_size;++i){
        if(i==2)
            std::cout<<"!";
         delete hash_array[i];
    }
    delete [] hash_array;
}