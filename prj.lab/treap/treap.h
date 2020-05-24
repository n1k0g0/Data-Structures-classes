//
// Created by Николай Горбачев on 08.04.2020.
//

#ifndef MOREDECTREES_DECTREES_H
#define MOREDECTREES_DECTREES_H

#include <iostream>
#include <vector>
class Treap;
class Node {
public:
    Node *leftChild{nullptr};
    Node *rightChild{nullptr};
    float key{0};
    int priority{0};

    Node( ) {
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->priority = 0;
    }
    Node(int inpElement, Node *left, Node *right, int pr) {
        this->key = inpElement;
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
    void clear( );
    void insertNode(int x , int priority);
    void deleteNode(const int &x);
    int getHeight(Node *r);
    Node * getRoot();
    void toVectorOfPairs(vector<pair<int,int> > & r, Node * n);
    void showAll(Node *t) const;
    float showAllSmallerThan(const float & x, Node* t, float sum) const;
    float sumSmallerThan(const float & x) const;
    void intersect(Treap *t);

private:
    Node *root{nullptr};
    Node *nullNode{nullptr};
    Node * rotateWithLeftChild(Node * & t) const;
    Node * rotateWithRightChild(Node * & t) const;
    Node * insertNode(int x, int priority, Node * t);
    void deleteNode(const int & x, Node * & t);
    void clear(Node * & t);

};




#endif //MOREDECTREES_DECTREES_H
