//
// Created by yarde on 1/4/2020.
//

#ifndef RANK_TREE_DATACENTERMANAGER_H
#define RANK_TREE_DATACENTERMANAGER_H

#include "hash_table.h"
#include "Tree_1.h"
#include "UpTree.h"
#include "library2.h"

typedef class dataCenterManager {
private:
    int num_centers;
    hash_table ds_server_table;
    tree<Traffic_Key> ds_traffic_tree;
    upTree data_centers_tree;
public:
    dataCenterManager() = delete;
    dataCenterManager(int num);
    ~dataCenterManager() = default;
    StatusType MergeDataCenters(int dataCenter1, int dataCenter2);
    StatusType AddServer(int dataCenterID,int serverID);
    StatusType RemoveServer(int serverID);
    StatusType SetTraffic(int serverID, int traffic);
    StatusType sumHighestTrafficServers(int dataCenterID, int k, int * traffic);
    int getNumCenters();
}*DCManager;


#endif //RANK_TREE_DATACENTERMANAGER_H
