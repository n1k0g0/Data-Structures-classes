#include "treap.h"





Treap::Treap(){
    root = nullptr;
    size = 0;
}

Treap::Treap(const Treap& inp){
    nullNode = new Node;
    nullNode->leftChild = nullNode->rightChild = nullptr;
    nullNode->priority = INT_MAX;
    root = nullptr;
    *this = inp;
}


Treap::~Treap( ) {
    clear();
}

void Treap::insertNode(int x, int priority ) {
    this->root = insertNode(x, priority, this->root);
}

void Treap::deleteNode(const int & x ) {
    deleteNode(x, root);
}

const int & Treap::findMin( ) const {

    Node *ptr = root;
    while(ptr->leftChild != nullptr )
        ptr = ptr->leftChild;

    return ptr->data;
}
const int & Treap::findMax( ) const {

    Node *ptr = root;
    while(ptr->rightChild != nullptr )
        ptr = ptr->rightChild;

    return ptr->data;
}

const int & Treap::searchNode(const int & x ) const {
    Node *current = root;

    for( ; ; )
    {
        if( x < current->data )
            current = current->leftChild;
        else if(current->data < x )
            current = current->rightChild;
        else if( current != nullptr )
            return current->data;

    }
}

float Treap::showAllSmallerThan(const float & x, Node* t, float sum) const {
    if(t->leftChild != nullptr) {
        sum = showAllSmallerThan(x, t->leftChild, sum);
    }
    if(t->rightChild != nullptr) {
        sum = showAllSmallerThan(x, t->rightChild, sum);
    }
    if((t->rightChild == nullptr) && (t->leftChild == nullptr)) {
    }
    if (t->data < x) sum += t->data;
    return sum;
}

float Treap::sumSmallerThan(const float & x) const{
    return showAllSmallerThan(x, root, 0);
}

void Treap::clear( ) {
    clear(root);
}

bool Treap::isEmpty( ) const {
    return root == nullptr;
}

void Treap::showAll( ) const {
    if( isEmpty( ) )
        cout << "Empty tree" << endl;
    else
        showAll(root);
}



Node * Treap::insertNode(int x, int priority, Node * t ) { //internal method
    if( t == nullptr ) {
        this->size++;
        return new Node(x, nullptr, nullptr, priority );
    }
    if( x < t->data ) {
        t->leftChild = insertNode(x, priority, t->leftChild);
        if(t->leftChild->priority >= t->priority ) {
            return rotateWithLeftChild( t );
        }
        return t;
    }

    if(t->data < x ) {
        t->rightChild = insertNode(x, priority, t->rightChild);
        if(t->rightChild->priority > t->priority) {
            return rotateWithRightChild( t );
        }
        return t;
    }
    return t;
}

void Treap::deleteNode(const int & x, Node * & t) {
    if( t != nullptr ) {
        if( x < t->data )
            deleteNode(x, t->leftChild);
        else if(t->data < x )
            deleteNode(x, t->rightChild);
        else {
            // Match found
            if(t->leftChild->priority > t->rightChild->priority )
                rotateWithLeftChild( t );
            else
                rotateWithRightChild( t );

            if( t != nullptr)      // Continue on down
                deleteNode(x, t);
            else {
                delete t->leftChild;
                t->leftChild = nullptr;  // At a leaf
            }
        }
    }
}


void Treap::clear(Node * & t ) {
    if( t != nullptr) {
        clear(t->leftChild);
        clear(t->rightChild);
        delete t;
    }
}

void Treap::showAll(Node *t ) const {
    if( t != nullptr ) {
        showAll(t->leftChild);
        cout << t->data << endl;
        showAll(t->rightChild);
    }
}


int Treap::getHeight(Node *r ) {
    if (r == nullptr || r->priority == 0) {
        return 0;
    }
    return 1+(max(getHeight(r->leftChild), getHeight(r->rightChild)));
}

Node *  Treap::getRoot() {
    return this->root;
}
Node* Treap::rotateWithLeftChild(Node * & node) const {
    Node *result = node->leftChild;
    Node *x = result->rightChild;
    result->rightChild = node;
    node->leftChild = x;
    return result;
}

Node* Treap::rotateWithRightChild(Node * & node) const {
    Node *result = node->rightChild;
    Node *x = result->leftChild;
    result->leftChild = node;
    node->rightChild = x;
    return result;
}


void Treap::toVectorOfPairs(vector<pair<int,int> > & r, Node * n)  {
    if (n == nullptr)
        return;
    r.push_back(make_pair(n->data,n->priority));
    toVectorOfPairs(r, n->leftChild);
    toVectorOfPairs(r, n->rightChild);
}

void intersect_aux(Node *node1, Node *node2) {
    if (node1 == nullptr) return;
    if (node2 == nullptr) return;
    if (node1->data == node2->data) {
        intersect_aux(node1->leftChild, node2->leftChild);
        intersect_aux(node1->rightChild, node2->leftChild);
        return;
    } else {
        if (node1->data > node2->data) {
            intersect_aux(node1, node2->rightChild);
            intersect_aux(node1->leftChild, node2);
        }
        if (node1->data < node2->data) {
            intersect_aux(node1->rightChild, node2);
            intersect_aux(node1, node2->leftChild);
        }
    }
}

void Treap::intersect(Treap *t) {
    intersect_aux(t->getRoot(),this->getRoot());
}






