//
// Created by Николай Горбачев on 08.04.2020.
//

#ifndef MOREDECTREES_DECTREES_H
#define MOREDECTREES_DECTREES_H

#include <iostream>
#include <vector>
using namespace std;
class Treap;
class Node {
public:
    Node *leftChild;
    Node *rightChild;
    float data;
    int priority;

    Node( ) {
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->priority = 0;
    }
    Node(int inpElement, Node *left, Node *right, int pr) {
        this->data = inpElement;
        this->leftChild = left;
        this->rightChild = right;
        this->priority = pr;
    }
    friend class Treap;
};

class Treap{
public:
    Treap(const Treap &inp);
    Treap();
    ~Treap( );
    int size;
    const int & findMin( ) const;
    const int & findMax( ) const;
    const int & searchNode(const int& x) const;
    bool isEmpty( ) const;
    void showAll( ) const;
    void makeEmpty( );
    void insertNode(int x , int priority);
    void deleteNode(const int &x);
    int getHeight(Node *r);
    Node * getRoot();
private:
    Node *root;
    Node *nullNode;
    Node * rotateWithLeftChild(Node * & t) const;
    Node * rotateWithRightChild(Node * & t) const;
    Node * insertNode(int x, int priority, Node * t);
    void deleteNode(const int & x, Node * & t);
    void clear(Node * & t);
    void showAll(Node *t) const;
};



#endif //MOREDECTREES_DECTREES_H
