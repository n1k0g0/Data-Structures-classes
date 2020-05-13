//
// Created by Николай Горбачев on 13.05.2020.
//

#include "myVectorBasedTreap.h"

using namespace std;



VectorBasedTreap::VectorBasedTreap(){
    rootPr = -1;
    size = 0;
}


VectorBasedTreap::VectorBasedTreap(const VectorBasedTreap& inp){
    rootPr = inp.rootPr;
    dataVector = inp.dataVector;
    size = inp.size;
}





void VectorBasedTreap::rotateWithLeftChild(Node* &y) const{
    Node x = dataVector[y->rightChildNum];

    Node r = dataVector[y->leftChildNum]; // will not change
    Node g = dataVector[x.leftChildNum];
    Node b = dataVector[x.rightChildNum]; // will not change

    x.leftChildNum = y->priority;
    y->rightChildNum = g.priority;

    y = &x;
}

void VectorBasedTreap::rotateWithRightChild(Node* &x) const{
    Node y = dataVector[x->rightChildNum];

    Node r = dataVector[y.leftChildNum]; // will not change
    Node g = dataVector[y.leftChildNum];
    Node b = dataVector[x->rightChildNum]; // will not change

    x->leftChildNum = g.priority;
    y.rightChildNum = x->priority;

    x = &y;
}

void VectorBasedTreap::insert(Node* &root, int key) {
    if (!root) {
        insertNode(key);
    }

    insert(reinterpret_cast<Node *&>(key <= root->key ? dataVector[root->leftChildNum]
                                                      : dataVector[root->rightChildNum]), key);

    if (root->leftChildNum and dataVector[root->leftChildNum].priority > root->priority)
        rotateWithLeftChild(root);

    if (root->rightChildNum and dataVector[root->rightChildNum].priority > root->priority)
        rotateWithRightChild(root);
}


void VectorBasedTreap::insertNode(int x){
    ++size;
    Node newNode(x, -1, -1, size-1);
    dataVector.push_back(newNode);

    if(rootPr == -1) {
        rootPr = 0;
        return;
    }

    int nodePr = rootPr;

    while(nodePr != -1) {
        if(x < dataVector[nodePr].key) {
            nodePr = dataVector[nodePr].leftChildNum;
        } else {
            nodePr = dataVector[nodePr].rightChildNum;
        }
    }

    if(x < dataVector[nodePr].key) {
        dataVector[nodePr].leftChildNum = size - 1;
    } else {
        dataVector[nodePr].rightChildNum = size - 1;
    }
}







void VectorBasedTreap::insert(Node* &root, int key, int priority = -1) {
    if (root == NULL) {
        root = new Node(key, -1, -1, priority);
    }

    insert(reinterpret_cast<Node *&>(key < root->key ? dataVector[root->leftChildNum]
                                                     : dataVector[root->rightChildNum]), key, priority);

}

void VectorBasedTreap::split(Node* &t, int key, Node* &l, Node* &r) {
    int inf = 0x3f3f3f3f;

    insert(t, key, inf);

    l = &dataVector[t->leftChildNum];
    r = &dataVector[t->rightChildNum];
}


int VectorBasedTreap::sumFrom(Node* &start){
    if (start == NULL) {
        return 0;
    }

    return (start->key + sumFrom(reinterpret_cast<Node *&>(dataVector[start->leftChildNum])) + sumFrom(
            reinterpret_cast<Node *&>(dataVector[start->rightChildNum])));
}




bool VectorBasedTreap::removeNode(int x, int iterValue = 0) {
    if (rootPr == -1) return false;

    if (x < dataVector[iterValue].key) return removeNode(x, dataVector[iterValue].leftChildNum);
    if (x > dataVector[iterValue].key) return removeNode(x, dataVector[iterValue].rightChildNum);

    // no children at iterValue
    if ((dataVector[iterValue].leftChildNum == -1) and (dataVector[iterValue].rightChildNum == -1)) {
        Node* theNode = &dataVector[iterValue];
        dataVector.erase(dataVector.begin() + iterValue);
        delete theNode;
        --size;
        iterValue = -1;
    }

        // one child at iterValue
    else if ((dataVector[iterValue].leftChildNum == -1) or (dataVector[iterValue].rightChildNum == -1)) {
        int child = (dataVector[iterValue].leftChildNum > 0) ? dataVector[iterValue].leftChildNum : dataVector[iterValue].rightChildNum;
        int old_root = iterValue;
        iterValue = child;

        Node* theNode = &dataVector[old_root];
        dataVector.erase(dataVector.begin() + old_root);
        delete theNode;
        --size;
        iterValue = -1;
    }

        //two children at iterValue
    else {
        if (dataVector[iterValue].leftChildNum < dataVector[iterValue].rightChildNum) {
            rotateWithLeftChild(reinterpret_cast<Node *&>(dataVector[iterValue]));
            removeNode(x, dataVector[iterValue].leftChildNum);
        } else {
            rotateWithRightChild(reinterpret_cast<Node *&>(dataVector[iterValue]));
            removeNode(x, dataVector[iterValue].rightChildNum);
        }
    }


    return true;
}