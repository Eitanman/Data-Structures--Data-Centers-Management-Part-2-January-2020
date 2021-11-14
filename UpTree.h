//
// Created by Eitan on 02/01/2020.
//

#ifndef EX2_UPTREE_H
#define EX2_UPTREE_H

#include "Tree_1.h"
#include "Keys.h"
#include "library2.h"

typedef class dataCenter{
private:
    tree <Traffic_Key>* dc_tree;
    int server_num;
    int dc_num;
public:
    dataCenter();
    ~dataCenter();
    int getServerNum();
    int getdcNum();
    void removeServer(int traffic_num,int server_num);
    void addServertoDCTree(int traffic_num,int server_num);
    void incrementServerNum();
    tree<Traffic_Key>* getTree();
    void setTree(tree<Traffic_Key>* tree);
    tree<Traffic_Key>* mergeTrees(tree<Traffic_Key>* tree_1,tree<Traffic_Key>* tree_2,int n, int m);
    dataCenter* uniteDataCenters(dataCenter* dc_1, dataCenter* dc_2);
}*DataCenter;


typedef class upTree {
private:
    //inner parts:
    typedef class edge{
    public:
        edge* parent;
        DataCenter data_center;
        edge();
        ~edge(){
            delete data_center;
        }
    }*Edge;
    //base
    int initial_ds_num;
    Edge* array;
public:
    upTree() = delete;
    upTree(int n);
    ~upTree();
    DataCenter getDCbyNum(int dc_num);
    Edge findMainEdge(Edge start_edge);
    Edge getEdge(int dc_num);
    void uniteEdges(Edge first_edge, Edge second_edge);
    void uniteDCsbyNum(int a, int b);

    }*UpTree;

#endif //EX2_UPTREE_H
