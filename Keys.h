//
// Created by Eitan on 10/12/2019.
//
#ifndef EX1_KEYS_H
#define EX1_KEYS_H

#include <iostream>


typedef class traffic_key {
private:
    int traffic_num;
    int server_num;
public:
    traffic_key(int traffic_num,int server);
    traffic_key(const traffic_key& w) = default;
    ~traffic_key() = default;
    bool operator<(traffic_key const &b);
    bool operator>(traffic_key const &b);
    bool operator==(traffic_key const&b);
    int getServerNum();
    int getTrafficNum();
    friend std::ostream& operator<<(std::ostream& os, const traffic_key& c);
    //traffic_key** mergeKeysArrays(traffic_key* arr1[], traffic_key* arr2[], int m, int n);
} *Traffic_Key;

#endif //EX1_KEYS_H
