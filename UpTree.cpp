//
// Created by Eitan on 02/01/2020.
//

#include "UpTree.h"

dataCenter::dataCenter(){
    try {
        server_num = 0;
        dc_tree = new tree<Traffic_Key>();
        dc_num = 1;
    }
    catch (std::bad_alloc &e){
        throw std::bad_alloc(); //we need to watch for this
    }
}

void dataCenter::incrementServerNum(){
    (this->server_num)++;
}


int dataCenter::getServerNum() {
    return server_num;
}

int dataCenter::getdcNum() {
    return dc_num;
}

dataCenter::~dataCenter() {
    delete dc_tree;
}

void dataCenter::removeServer(int traffic_num,int server_num){
    try {
        (this->server_num)--;
        if(traffic_num != 0) {
            Traffic_Key temp_key = new traffic_key(traffic_num, server_num);
            this->getTree()->removeVertex(temp_key);
            delete temp_key;
        }
    }
    catch (std::bad_alloc &e){
        throw std::bad_alloc(); //we need to watch for this
    }
}

void dataCenter::addServertoDCTree(int traffic_num,int server_num){
    (this->server_num)++;
    if(traffic_num != 0){
        this->getTree()->addVertex(server_num,traffic_num);
    }
}

tree<Traffic_Key>* dataCenter::getTree(){
    return this->dc_tree;
}

void dataCenter::setTree(tree<Traffic_Key>* tree){
    this->dc_tree=tree;
}

traffic_key** mergeKeysArrays(traffic_key* arr1[], traffic_key* arr2[], int m, int n)
{
    // mergedArr[] is going to contain result
    if(arr1[0]->getTrafficNum()==1){

    };
    Traffic_Key *mergedArr = new Traffic_Key[m + n];
    int i = 0, j = 0, k = 0;

    // Traverse through both arrays
    while (i < m && j < n)
    {
        // Pick the smaler element and put it in mergedArr
        if (*(arr1[i]) < *(arr2[j]))
        {
            mergedArr[k] = new traffic_key(arr1[i]->getTrafficNum(),arr1[i]->getServerNum());
            i++;
        }
        else
        {
            mergedArr[k] = new traffic_key(arr2[j]->getTrafficNum(),arr2[j]->getServerNum());
            j++;
        }
        k++;
    }

    // If there are more elements in first array
    while (i < m)
    {
        mergedArr[k] = new traffic_key(arr1[i]->getTrafficNum(),arr1[i]->getServerNum());
        i++; k++;
    }

    // If there are more elements in second array
    while (j < n)
    {
        mergedArr[k] = new traffic_key(arr2[j]->getTrafficNum(),arr2[j]->getServerNum());
        j++; k++;
    }
    return mergedArr;
}

tree<Traffic_Key>* dataCenter::mergeTrees(tree<Traffic_Key>* tree_1,tree<Traffic_Key>* tree_2, int n, int m){
    if((tree_1->getRoot()== nullptr)&&(tree_2->getRoot()== nullptr)){
        return (new tree<Traffic_Key>());
    }
    int i=0;
    Traffic_Key *array1 = new Traffic_Key[n];
    tree_1->storeInorder(tree_1->getRoot(),array1,&i);
    int j = 0;
    Traffic_Key *array2 = new Traffic_Key[m];
    tree_2->storeInorder(tree_2->getRoot(), array2, &j);
    Traffic_Key* merged_array = mergeKeysArrays(array1,array2,i,j);
    tree<Traffic_Key>* new_tree = new tree<Traffic_Key>(); //new tree<Traffic_Key>();
    new_tree = new_tree->arrayToTree(merged_array,0,i+j-1);
    for(int q=0;q<i;q++){
        delete array1[q];
    }
    for(int r=0;r<j;r++){
        delete array2[r];
    }
    for(int d=0;d<i+j;d++){
        delete merged_array[d];
    }
    delete [] array1;
    delete [] array2;
    delete [] merged_array;
    return new_tree;
}

dataCenter* dataCenter::uniteDataCenters(dataCenter* dc_1, dataCenter* dc_2){ // צריך לעבור על החלק הזה שוב!
    if((dc_1 == nullptr)||(dc_2 == nullptr)){
        return nullptr;
        // how to correct?
    }
    if(dc_1==dc_2){
        //delete dc_2;// recently added
        return dc_1;
    }
    DataCenter new_data_center  = new dataCenter();
    new_data_center->server_num = dc_1->server_num + dc_2->server_num;
    new_data_center->dc_num = dc_1->dc_num + dc_2->dc_num;
    tree<Traffic_Key>* temp_tree = new_data_center->dc_tree;
    new_data_center->dc_tree = mergeTrees(dc_1->dc_tree,dc_2->dc_tree,dc_1->getServerNum(),dc_2->getServerNum());
    delete temp_tree;
    return new_data_center;
}

upTree::edge::edge(){
    try {
        data_center = new dataCenter();
        parent = nullptr;
    }
    catch (std::bad_alloc &e){
        throw std::bad_alloc();
    }
}

upTree::upTree(int n){
    try{
        initial_ds_num = n;
        this->array = new Edge[n];
        for(int i=0;i<n;i++){
            this->array[i] = new edge();
        }
    }
    catch (std::bad_alloc &e){
        throw std::bad_alloc();
    }
}

upTree::~upTree(){
    for(int i=0;i<this->initial_ds_num;i++){
        delete this->array[i];
    }
    delete [] array;
}

upTree::Edge upTree::findMainEdge(Edge start_edge){

    if(start_edge->parent == nullptr){ // this this edge was never United with another
        return start_edge;
    }
    Edge curr_edge = start_edge;
    while(curr_edge->parent != nullptr){
        curr_edge = curr_edge->parent;
    }
    Edge temp_edge = start_edge;
    Edge prev_edge = start_edge;
    while(temp_edge->parent != nullptr){
        temp_edge = temp_edge->parent;
        prev_edge->parent = curr_edge;
        prev_edge = temp_edge;
    }
    return curr_edge;
}

upTree::Edge upTree::getEdge(int dc_num){
    return this->array[dc_num];
}


DataCenter upTree::getDCbyNum(int dc_num){
    if((dc_num<0)||(dc_num>=this->initial_ds_num)){
        return nullptr;
    }
    return this->findMainEdge(this->array[dc_num])->data_center;
}

void upTree::uniteDCsbyNum(int a, int b){
    uniteEdges(array[a-1],array[b-1]);
}


void upTree::uniteEdges(Edge first_edge, Edge second_edge) {
    if(first_edge->parent == nullptr){
    }
    Edge main_1 = findMainEdge(first_edge);
    Edge main_2 = findMainEdge(second_edge);
    DataCenter dc_1 = main_1->data_center;
    DataCenter dc_2 = main_2->data_center;
    if(dc_1 == dc_2){
        return;
    }
    if(dc_1->getdcNum() < dc_2->getdcNum()){
        DataCenter new_data_center = dc_1->uniteDataCenters(dc_1, dc_2); // created a new tree and a new data center
        delete dc_1;
        delete dc_2;
        main_2->data_center = nullptr;
        main_2->data_center = new_data_center;
        main_1->data_center = nullptr;
        main_1->parent = main_2;
    }
    else{
        DataCenter new_data_center = dc_1->uniteDataCenters(dc_1, dc_2); // created a new tree and a new data center
        delete dc_1;
        delete dc_2; //because the united data center is tree 2
        main_1->data_center = nullptr;
        main_1->data_center = new_data_center;
        main_2->data_center = nullptr;
        main_2->parent = main_1;
    }


}