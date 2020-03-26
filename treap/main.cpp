
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

