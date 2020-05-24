//
// Created by Николай Горбачев on 13.05.2020.
//

#ifndef VECTORBASEDTREAP_MYVECTORBASEDTREAP_H
#define VECTORBASEDTREAP_MYVECTORBASEDTREAP_H



#include <iostream>
#include <vector>
class VectorBasedTreap;
class Node {
public:
    int leftChildNum{0};
    int rightChildNum{0};
    int priority{0};
    int key{0};

    Node() {
        leftChildNum = -1;
        rightChildNum = -1;
        priority = 0;
    }
    Node(int inpElement, int left, int right, int inPriority) {
        key = inpElement;
        leftChildNum = left;
        rightChildNum = right;
        priority = inPriority;
    }
    ~Node() = default;

};


class VectorBasedTreap{
public:
    VectorBasedTreap(const VectorBasedTreap &inp);
    VectorBasedTreap();
    ~VectorBasedTreap( ) = default;
    void insertNode(int x);
    bool removeNode(int x, int start);
    void split(Node* &t, int key, Node* &l, Node* &r);

    void insert(Node* &root, int key);
    int sumFrom(Node* &start);

    vector<Node> dataVector;
private:
    int rootPr{0};
    int size{0};

    void rotateWithLeftChild(Node* &y) const;
    void rotateWithRightChild(Node* &x) const;

    void insert(Node* &root, int key, int priority);
};







#endif //VECTORBASEDTREAP_MYVECTORBASEDTREAP_H
