//
//  main.cpp
//  practice
//
//  Created by Mahmud on 12/6/17.
//  Copyright © 2017 Mahmud. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <functional>
#include <ctime>
#include <cassert>

using namespace std;

struct Node{
    float data;
    int priority;
    Node* leftChild, *rightChild;
    Node(int data_) {
        data = data_;
        priority = rand() % 100;
        leftChild = rightChild = nullptr;
    }
};

class Treap{
public:
    void insertNode(Node* root, int data_);
    bool searchNode(Node* root, int key);
    void deleteNode(Node* root, int key);
    void showAll(Node* root, int space, int height);
private:
    Node* root = nullptr;
};


void Treap::insertNode(Node* root, int data_) { //insertion
    if (&(this->root) == nullptr) {
        Node* rootVal = new Node(data_);
        this->root = rootVal;
        return;
    }
    if (data_ < this->root->data) {
        insertNode(this->root->leftChild, data_);
        if (this->root->leftChild != nullptr && this->root->leftChild->priority > this->root->priority);
    } else {
        insertNode(this->root->rightChild, data_);
        if (this->root->rightChild != nullptr && this->root->rightChild->priority > this->root->priority);
    }
    return;
}

bool Treap::searchNode(Node* root, int key) {
    if (this->root == nullptr)
        return false;
    if (this->root->data == key)
        return true;
    if (key < this->root->data)
        return searchNode(this->root->leftChild, key);
    return searchNode(this->root->rightChild, key);
}

void Treap::deleteNode(Node* root, int key) {
    if (this->root == nullptr)
        return;
    if (key < this->root->data)
        deleteNode(this->root->leftChild, key);
    else if (key > this->root->data)
        deleteNode(this->root->rightChild, key);
    else {
        if (this->root->leftChild ==nullptr && this->root->rightChild == nullptr) {
            delete this->root;
            this->root = nullptr;
        }
        else if (this->root->leftChild && this->root->rightChild) {
            if (this->root->leftChild->priority < this->root->rightChild->priority) {
                deleteNode(this->root->leftChild, key);
            } else {
                deleteNode(this->root->rightChild, key);
            }
        }
        else {
            Node* curr = this->root;
            delete curr;
        }
    }
}

void Treap::showAll(Node* root, int space = 0, int height =10) {
    if (this->root == nullptr)
        return;
    space += height;
    showAll(this->root->leftChild, space);
    cout << endl;
    for (int i = height; i < space; i++) {
        cout << ' ';
        cout << this->root->data << "(" << root->priority << ")\n";
        cout << endl;
    }
    showAll(root->rightChild, space);
}

int main() {
    int nums[] = {1,7,6,4,3,2,8,9,10 };
    Node* root = nullptr;
    Treap* MyTreap = new Treap();
    srand(time(nullptr));
    for (int n: nums)
        MyTreap->insertNode(root, n);
    cout << "Constructed Treap:\n\n";
    MyTreap->showAll(root);
    cout << "\nDeleting node 8:\n\n";
    MyTreap->deleteNode(root, 8);
    MyTreap->showAll(root);
    cout << "\nDeleting node 3:\n\n";
    MyTreap->deleteNode(root, 3);
    MyTreap->showAll(root);
    return 0;
}



/*
struct node {
    int nodeValue;
    int subtreeSize;
    int subtreeValue;
    int priority;
    bool reversed;
    node* leftChild;
    node* rightChild;
    node () {

    }
};
typedef node* tree;

int getSize(tree &t) {
    return t ? t->subtreeSize : 0;
}
int getValue(tree &t) {
    return t ? t->subtreeValue : 0;
}
void update(tree &t) {
    if (t) {
        t->subtreeSize = getSize(t->leftChild) + 1 + getSize(t->rightChild);
        t->subtreeValue = max({getValue(t->leftChild), t->nodeValue, getValue(t->rightChild)});
    }
}
void relax(tree &t) {
    if (t && t->reversed) {
        update(t);
        t->reversed = false;
        swap(t->leftChild, t->rightChild);
        if (t->leftChild) t->leftChild->reversed ^= true;
        if (t->rightChild) t->rightChild->reversed ^= true;
    }
}
tree initialize(int key) {
    tree t = (tree)malloc(sizeof(node));
    t->nodeValue = key;
    t->subtreeSize = 1;
    t->subtreeValue = key;
    t->priority = rand();
    t->reversed = false;
    t->leftChild = NULL;
    t->rightChild = NULL;
    return t;
}
void Split(tree &t, tree &l, tree &r, int position, int skipped = 0) {
    if (!t) return void(l = r = NULL);
    int currentPosition = skipped + getSize(t->leftChild) + 1;
    if (currentPosition <= position) {
        Split(t->rightChild, t->rightChild, r, position, currentPosition);
        l = t;
    }
    else {
        Split(t->leftChild, l, t->leftChild, position, skipped);
        r = t;
    }
    update(t);
}
void Merge(tree &t, tree &l, tree &r) {
    if (!l || !r) t = l ? l : r;
    else if(l->priority > r->priority) {
        Merge(l->rightChild, l->rightChild, r);
        t = l;
    }
    else {
        Merge(r->leftChild, l, r->leftChild);
        t = r;
    }
    update(t);
}
void Insert(tree &t, int position, int key) {
    tree l, r;
    tree current = initialize(key);
    Split(t, l, r, position - 1);
    Merge(l, l, current);
    Merge(t, l, r);
}
void Erase(tree &t, int position) {
    tree l, r;
    Split(t, l, r, position - 1);
    tree lx, rx;
    Split(r, lx, rx, 1);
    free(lx);
    Merge(t, l, rx);
}
bool Exists(tree &t, int key) {
    if (!t) return false;
    if (t->nodeValue == key) return true;
    if (t->nodeValue > key) return Exists(t->leftChild, key);
    else return Exists(t->rightChild, key);
}
int _getIndex(tree &t, int key, int skipped = 0) { // lower_bound
    if (t->nodeValue == key) return skipped + getSize(t->leftChild) + 1;
    if (t->nodeValue > key) return _getIndex(t->leftChild, skipped);
    else return _getIndex(t->rightChild, skipped + getSize(t->leftChild) + 1);
}
int getIndex(tree &t, int key) {
    if (!Exists(t, key)) return -1;
    return _getIndex(t, key);
}

void Print(tree &t) {
    if (!t) return;
    Print(t->leftChild);
    cout << t->nodeValue << " ";
    Print(t->rightChild);
}

 */
/*
int main() {
    srand(unsigned(time((NULL))));

    tree t = NULL;
    for (int i = 0; i < 5; i ++) {
        Insert(t, i + 1, i + 1);
    }
    Print(t); cout << endl;
    Insert(t, 1, 6);
    Print(t); cout << endl;


    return 0;
}*/