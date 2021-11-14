//
// Created by Eitan on 10/12/2019.
//

#include "Keys.h"
traffic_key::traffic_key(int traffic_num,int server) : traffic_num(traffic_num),server_num(server) {}
bool traffic_key:: operator<(traffic_key const &b) {
    if(this->traffic_num == b.traffic_num) {
        return (this->server_num > b.server_num);
    }
    return this->traffic_num < b.traffic_num;
}
bool traffic_key::operator>(traffic_key const &b) {
    if(this->traffic_num == b.traffic_num) {
        return (this->server_num < b.server_num);
    }
    return this->traffic_num > b.traffic_num;
}

bool traffic_key::operator == (traffic_key const &b){
    return (this->server_num == b.server_num);
}

int traffic_key::getServerNum() {
    return server_num;
}

int traffic_key::getTrafficNum(){
    return traffic_num;
}

std::ostream& operator<<(std::ostream& os, const traffic_key& c){
    os << "(" << c.traffic_num << "," << c.server_num << ")";
    return os;
}

