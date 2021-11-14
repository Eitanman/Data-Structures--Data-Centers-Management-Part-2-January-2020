//
// Created by yarde on 1/4/2020.
//

#include "DataCenterManager.h"

dataCenterManager::dataCenterManager(int num):num_centers(num), ds_server_table(), ds_traffic_tree() , data_centers_tree(upTree(num)){}



StatusType dataCenterManager::AddServer(int dataCenterID, int serverID) {
    try {
        if (ds_server_table.findServerById(serverID) == nullptr) { // then the server isn't in the hash table
            // we add the server only into the hash table because default traffic is 0
            server temp_server(serverID, 0, dataCenterID);
            ds_server_table.insertServer(&temp_server); // hash table copies the data inside
            data_centers_tree.getDCbyNum(dataCenterID-1)->incrementServerNum();
            return SUCCESS;
        }
        return FAILURE; // server is already in DS
    }
    catch(std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}
int dataCenterManager::getNumCenters() {
    return num_centers;
}
StatusType dataCenterManager::SetTraffic(int serverID, int traffic) {
    try {
        Server server_to_update = ds_server_table.findServerById(serverID);
        if (server_to_update == nullptr) { // server isn't in DS
            return FAILURE;
        }
        if (server_to_update->getTraffic() == traffic) {
            return SUCCESS; // no need to change anything
        }
        traffic_key key_to_delete(server_to_update->getTraffic(),server_to_update->getServerId());
        if(server_to_update->getTraffic() != 0) {
            ds_traffic_tree.removeVertex(&key_to_delete);
        }
        if(traffic != 0){
            ds_traffic_tree.addVertex(serverID, traffic);
        }
        DataCenter curr_dc = data_centers_tree.getDCbyNum(server_to_update->getDataCenterId()-1);
        curr_dc->removeServer(server_to_update->getTraffic(),server_to_update->getServerId());
        curr_dc->addServertoDCTree(traffic, serverID);
        server_to_update->setTraffic(traffic);
        return SUCCESS;
    }
    catch (std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}
StatusType dataCenterManager::RemoveServer(int serverID) {
    Server server_to_delete = ds_server_table.findServerById(serverID);
    if(server_to_delete == nullptr){
        return FAILURE;
    }
    DataCenter curr_dc = data_centers_tree.getDCbyNum(server_to_delete->getDataCenterId()-1);
    curr_dc->removeServer(server_to_delete->getTraffic(), serverID);
    if(server_to_delete->getTraffic()!=0){
        traffic_key temp_key(server_to_delete->getTraffic(), server_to_delete->getServerId());
        ds_traffic_tree.removeVertex(&temp_key);
    }
    ds_server_table.deleteServer(server_to_delete);
    return SUCCESS;
}

StatusType dataCenterManager::sumHighestTrafficServers(int dataCenterID, int k, int *traffic) {
    if(dataCenterID == 0){
        *traffic = ds_traffic_tree.getKHighestSum(k, ds_traffic_tree.getRoot());
    }
    else {
        DataCenter temp_dc = data_centers_tree.getDCbyNum(dataCenterID - 1);
        *traffic = temp_dc->getTree()->getKHighestSum(k, temp_dc->getTree()->getRoot());
    }
    return SUCCESS;
}
StatusType dataCenterManager::MergeDataCenters(int dataCenter1, int dataCenter2) {
    try{
        data_centers_tree.uniteDCsbyNum(dataCenter1, dataCenter2);
        return SUCCESS;
    }
    catch (std::bad_alloc &e){
        return ALLOCATION_ERROR;
    }
}