//
// Created by yarde on 1/4/2020.
//
#include "library2.h"
#include "DataCenterManager.h"
void* Init(int n){
    try {
        DCManager new_ds = new dataCenterManager(n);
        return new_ds;
    }
    catch( std::bad_alloc &e){
        return nullptr;
    }
}

StatusType MergeDataCenters(void *DS, int dataCenter1, int dataCenter2){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    DCManager new_ds = static_cast<DCManager>(DS);
    //int n = new_ds->getNumCenters();
    if(dataCenter1 > new_ds->getNumCenters() || dataCenter2 > new_ds->getNumCenters() || dataCenter1<=0 || dataCenter2 <=0){
        return INVALID_INPUT;
    }
    StatusType status = new_ds->MergeDataCenters(dataCenter1, dataCenter2);
    return status;
}

StatusType AddServer(void *DS, int dataCenterID, int serverID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    DCManager new_ds = static_cast<DCManager>(DS);
    //int n = new_ds->getNumCenters();
    if(dataCenterID <= 0 || dataCenterID > new_ds->getNumCenters() || serverID <= 0){
        return INVALID_INPUT;
    }
    StatusType status = new_ds->AddServer(dataCenterID, serverID);
    return status;
}

StatusType RemoveServer(void *DS, int serverID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    DCManager new_ds = static_cast<DCManager>(DS);
    //int n = new_ds->getNumCenters();
    if(serverID <= 0){
        return INVALID_INPUT;
    }
    StatusType status = new_ds->RemoveServer(serverID);
    return status;
}

StatusType SetTraffic(void *DS, int serverID,  int traffic){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    DCManager new_ds = static_cast<DCManager>(DS);
    if(serverID <= 0 || traffic < 0){
        return INVALID_INPUT;
    }
    StatusType status = new_ds->SetTraffic(serverID, traffic);
    return status;
}
StatusType SumHighestTrafficServers(void *DS, int dataCenterID,  int k, int *traffic){
    if(DS == nullptr || traffic == nullptr || k < 0){
        return INVALID_INPUT;
    }
    DCManager new_ds = static_cast<DCManager>(DS);
    int n = new_ds->getNumCenters();
    if(dataCenterID < 0 || dataCenterID > n){
        return INVALID_INPUT;
    }
    StatusType status = new_ds->sumHighestTrafficServers(dataCenterID, k , traffic);
    return status;
}

void Quit(void** DS){
    DCManager new_ds = static_cast<DCManager>(*DS);
    delete new_ds;
    *DS = nullptr;
}