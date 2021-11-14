//
// Created by yarde on 1/1/2020.
//

#ifndef RANK_TREE_SERVER_H
typedef class server{
private:
    int server_id;
    int traffic;
    int dataCenter_id;
public:
    server() = delete;
    server(int server_id, int traffic, int dataCenter_id);
    server(const server & serv);
    ~server() = default;
    int getServerId();
    int getTraffic();
    int getDataCenterId();
    void setTraffic(int temp_traffic);
}*Server;
#define RANK_TREE_SERVER_H

#endif //RANK_TREE_SERVER_H
