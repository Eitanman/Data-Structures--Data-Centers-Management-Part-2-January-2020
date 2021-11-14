#ifndef EX1_TREE_H
#define EX1_TREE_H
#include <stdbool.h>
#include <iostream>
#include <stdio.h>
#include "Keys.h"

template <typename Key> class tree { // Key is a pointer to class key
private:
    typedef class vertex {
    public:
        Key key;
        int traffic;
        vertex *left_son;
        vertex *right_son;
        int height;
        int sum;
        int sub_tree_size;
        vertex(int server_num, int traffic) : key(new traffic_key(traffic,server_num)) ,traffic(traffic),
        left_son(nullptr),right_son(nullptr),height(0),sum(0),sub_tree_size(1) {};
        vertex(const vertex &v) {
            this->key = v.key;
            this->left_son = v.left_son;
            this->right_son = v.right_son;
            this->height = v.height;
            this->traffic = v.traffic;
            this->traffic=v.traffic;
            this->sum=v.sum;
            this->sub_tree_size=v.sub_tree_size;
        };
        ~vertex(){delete this->key;}
        void swapVertex(vertex *ver1, vertex *ver2) {
            Key temp_key = ver1->key;
            int temp_traffic = ver1->traffic;
            ver1->traffic = ver2->traffic;
            ver1->key = ver2->key;
            ver2->key = temp_key;
            ver2->traffic = temp_traffic;
        }
    } *Vertex;
    Vertex root;
    Vertex rotateRight(Vertex temp_root) {// returns new root vertex
        Vertex new_root = temp_root->left_son;
        Vertex new_right = temp_root;
        Vertex new_right_left = (temp_root->left_son)->right_son;
        Vertex new_right_right = temp_root->right_son;
        new_root->right_son = temp_root;
        temp_root->left_son = new_right_left;
        new_right->height =
                max(height(new_right_right), height(new_right_left)) + 1;
        new_right->sub_tree_size=subTreeSize(new_right_right)+subTreeSize(new_right_left)+1;
        new_right->sum=trafficSum(new_right_right)+trafficSum(new_right_left)+new_right->traffic;
        new_root->sub_tree_size=subTreeSize(new_root->right_son)+subTreeSize(new_root->left_son)+1;
        new_root->sum=trafficSum(new_root->right_son)+trafficSum(new_root->left_son)+new_root->traffic;
        return new_root;
    };

    Vertex rotateLeft(Vertex temp_root) {// returns new root vertex
        Vertex new_root = temp_root->right_son;
        Vertex new_left = temp_root;
        Vertex new_left_right = (temp_root->right_son)->left_son;
        Vertex new_left_left = temp_root->left_son;
        new_root->left_son = temp_root;
        temp_root->right_son = new_left_right;
        new_left->height =
                max(height(new_left_left), height(new_left_right)) + 1;
        new_left->sub_tree_size=subTreeSize(new_left_left)+subTreeSize(new_left_right)+1;
        new_left->sum=trafficSum(new_left_left)+trafficSum(new_left_right)+new_left->traffic;
        new_root->sub_tree_size=subTreeSize(new_root->right_son)+subTreeSize(new_root->left_son)+1;
        new_root->sum=trafficSum(new_root->right_son)+trafficSum(new_root->left_son)+new_root->traffic;
        return new_root;
    };

    Vertex rotateLR(Vertex temp_root) {
        Vertex new_root = rotateLeft(temp_root->left_son);
        temp_root->left_son = new_root;
        new_root = rotateRight(temp_root);
        new_root->height =
                max(height(new_root->right_son), height(new_root->left_son)) +
                1;
        new_root->sub_tree_size=subTreeSize(new_root->right_son)+subTreeSize(new_root->left_son)+1;
        new_root->sum=trafficSum(new_root->right_son)+trafficSum(new_root->left_son)+new_root->traffic;
        return new_root;
    };

    Vertex rotateRL(Vertex temp_root) {
        Vertex new_root = rotateRight(temp_root->right_son);
        temp_root->right_son = new_root;
        new_root = rotateLeft(temp_root);
        new_root->height =
                max(height(new_root->right_son), height(new_root->left_son)) +
                1;
        new_root->sub_tree_size=subTreeSize(new_root->right_son)+subTreeSize(new_root->left_son)+1;
        new_root->sum=trafficSum(new_root->right_son)+trafficSum(new_root->left_son)+new_root->traffic;
        return new_root;
    };

    Vertex balanceTree(Vertex temp_root) {
        int bf = calculateBF(temp_root);
        if (bf == 2) {
            int bf_left = calculateBF(temp_root->left_son);
            if (bf_left >= 0) { //LL rotation-rotate right
                return rotateRight(temp_root); // returns new root
            } else if (bf_left == -1) {// LR rotation
                return rotateLR(temp_root);
            }
        } else if (bf == -2) {
            int bf_right = calculateBF(temp_root->right_son);
            if (bf_right <= 0) {// RR rotation - rotate left
                return rotateLeft(temp_root);
            } else if (bf_right == 1) { //RL rotation
                return rotateRL(temp_root);
            }
        }
        return temp_root; // no need to do any rotations
    }

    int calculateBF(Vertex ver) {
        Vertex left = ver->left_son;
        Vertex right = ver->right_son;
        return height(left) - height(right);
    }

    Vertex findMinVertex(Vertex temp_root) {
        if (temp_root->left_son == nullptr) {
            return temp_root;
        }
        temp_root = findMinVertex(temp_root->left_son);
        return temp_root;
    }

    int max(const int height1, const int height2) {
        if (height1 > height2)
            return height1;
        return height2;
    }

    Vertex addVertexAux(int server_num, int traffic, Vertex curr_root) {
        vertex ver(server_num, traffic);
        Vertex v = &ver;
        if (curr_root == nullptr) { // this means we've reached a leaf
            curr_root = new vertex(server_num, traffic);
            curr_root->right_son = nullptr;
            curr_root->left_son = nullptr;
            curr_root->height = 0;
            curr_root->sub_tree_size=1;
            curr_root->sum=traffic;
            return curr_root;
        } else if (*(v->key) < *(curr_root->key)) { // v should be on the left of curr root, we have to overload the operator < for key*.
            curr_root->left_son = addVertexAux(server_num, traffic,
                                               curr_root->left_son);
        } else if (*(v->key) > *(curr_root->key)) {
            curr_root->right_son = addVertexAux(server_num, traffic,
                                                curr_root->right_son);
        }
        Vertex left_son = curr_root->left_son;
        Vertex right_son = curr_root->right_son;
        int curr_height = max(height(left_son), height(right_son)) + 1;
        curr_root->height = curr_height;
        curr_root->sub_tree_size = subTreeSize(left_son)+subTreeSize(right_son)+1;
        curr_root->sum= trafficSum(left_son)+trafficSum(right_son)+curr_root->traffic;
        curr_root = balanceTree(curr_root);
        return curr_root;
    }

    Vertex removeVertexAux(Vertex v, Vertex curr_root, bool* is_deleted) {
        Vertex temp_ver = nullptr;
        if (curr_root == nullptr) // check this
            return nullptr;
        if (*(v->key) < *(curr_root->key)) {
            curr_root->left_son = removeVertexAux(v, curr_root->left_son, is_deleted);
        } else if (*(v->key) > *(curr_root->key)) {
            curr_root->right_son = removeVertexAux(v, curr_root->right_son, is_deleted);
        }
        //ver=curr_root at this stage
        if (*is_deleted == 0) { // vertex has two sons
            if(curr_root->left_son != nullptr && curr_root->right_son != nullptr && *(v->key) == *(curr_root->key)) {
                Vertex min_ver = findMinVertex(curr_root->right_son);
                v->swapVertex(v, min_ver); // still need to write this function, it swaps the keys and the data pointers
                curr_root->right_son = removeVertexAux(min_ver, curr_root->right_son,
                                                       is_deleted);// and it starts recursively again
            }
        }
            //we've found the element now and it is the curr_root
         if (*is_deleted == 0) { // executes only if this is the node to delete because it has at most one child (because when we reach this we try to delete the min_value we found
            if(*(v->key) == *(curr_root->key)) {
                temp_ver = curr_root;
                if (curr_root->right_son == nullptr) { // connects right son to father
                    curr_root = curr_root->left_son; // now the vertex is not in the tree anymore
                } else if (curr_root->left_son ==
                           nullptr) { // connects left son to father
                    curr_root = curr_root->right_son;
                }
                if(root == temp_ver){
                    root = curr_root;
                }
                delete temp_ver;
                *is_deleted=1;
            }
        }
        if (curr_root == nullptr) {
            return nullptr;
        }
        curr_root->height =max(height(curr_root->right_son), height(curr_root->left_son))+1;
        curr_root->sum= trafficSum(curr_root->right_son)+trafficSum(curr_root->left_son)+curr_root->traffic;
        curr_root->sub_tree_size=subTreeSize(curr_root->right_son)+subTreeSize(curr_root->left_son)+1;
        curr_root = balanceTree(curr_root);
        return curr_root;
    };

    const int height(Vertex ver) {
        if (ver == nullptr)
            return -1;
        return ver->height;
    }

    const int subTreeSize(Vertex ver){
        if(ver== nullptr){
            return 0;
        }
        return ver->sub_tree_size;
    }

    const int trafficSum(Vertex ver){
        if(ver== nullptr){
            return 0;
        }
        return ver->sum;
    }

public:
    tree() {root = nullptr;}
    tree(const tree &t) = default;

    ~tree(){
        postorderDestroyWithoutData(root);
    }
    Vertex
    getRoot() { return root; }// returns const reference so it can't be changed
    void addVertex(int server_num, int input_traffic) {
        root = addVertexAux(server_num, input_traffic, root);
    }

    void removeVertex(Key input_key) {// if can't find don't delete- have to still add
        Vertex ver_to_delete = findVertexByKey(input_key, root);
        Vertex copy_delete(ver_to_delete);
        bool is_deleted = 0;
        if(root == ver_to_delete && ver_to_delete->left_son == nullptr && ver_to_delete->right_son == nullptr){
            Vertex v1(copy_delete);
            root = removeVertexAux(v1, root, &is_deleted);
            root = nullptr;
        }
        Vertex v1(ver_to_delete);
        root = removeVertexAux(v1, root, &is_deleted);
    }

    bool isKeyInTree(Key key) { // Checks to see if the key exists or doesn't
        if(root == nullptr){
            return false;
        }
        Vertex temp = findVertexByKey(key, this->root);
        if (temp == nullptr)
            return false;
        return true;
    }

    Vertex findVertexByKey(Key key, Vertex curr_root) {
        Vertex temp = nullptr;
        if(curr_root == nullptr){
            return nullptr;
        }
        Key curr_key = curr_root->key;
        if (*curr_key == *key) {
            return curr_root;
        }
        if (*key < *curr_key) {
            temp = findVertexByKey(key, curr_root->left_son);
        } else if (*key > *curr_key) {
            temp = findVertexByKey(key, curr_root->right_son);
        }
        return temp;
    }

    void postorderDestroyWithoutData(Vertex curr_root) {
        if (curr_root == nullptr) {
            return;
        }
        postorderDestroyWithoutData(curr_root->left_son);
        postorderDestroyWithoutData(curr_root->right_son);
        delete curr_root;
    }



    int getKHighestSum(int k, Vertex curr_root){
        if((curr_root== nullptr)||(k==0)){
            return 0;
        }
        if(k>=curr_root->sub_tree_size){
            return curr_root->sum;
        }
        Vertex curr_father=curr_root;
        while((curr_root!= nullptr)&&(curr_root->sub_tree_size>k)){
            curr_father=curr_root;
            curr_root=curr_root->right_son;
        }
        if(curr_root== nullptr){//will happen if k==1 and right_son==null
            return curr_father->traffic;
        }
        if(curr_root->sub_tree_size==k){
            return curr_root->sum;
        }
        if(curr_root->sub_tree_size<k){
            int k_left=k-curr_root->sub_tree_size;
            return (curr_root->sum)+curr_father->traffic+getKHighestSum(k_left-1,curr_father->left_son);
        }
        return 0;
    }

    void inorderPrint(Vertex curr_root){
        if(curr_root==nullptr){
            return;
        }
        inorderPrint(curr_root->left_son);
        std::cout << "curr key is:" << *curr_root->key << std::endl;
        inorderPrint(curr_root->right_son);
    };



};
#endif //EX1_TREE_H