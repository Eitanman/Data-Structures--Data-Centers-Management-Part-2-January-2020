//
// Created by yarde on 1/1/2020.
//
#include "server.h"

server::server(int server_id, int traffic, int dataCenter_id):server_id(server_id), traffic(traffic), dataCenter_id(dataCenter_id){;}
int server::getServerId(){
    return server_id;
}
int server::getTraffic(){
    return traffic;
}
int server::getDataCenterId(){
    return dataCenter_id;
}
server::server(const server &serv) {
    this->traffic = serv.traffic;
    this->server_id = serv.server_id;
    this->dataCenter_id = serv.dataCenter_id;
}
void server::setTraffic(int temp_traffic) {
    traffic = temp_traffic;
}