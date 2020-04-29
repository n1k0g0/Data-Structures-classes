#include "myTreap.h"

int main(){

    Treap *t = new Treap();


    t->insertNode( 10,1 );
    t->insertNode( 4,6 );
    t->insertNode( 3,4 );
    t->insertNode( 20,7 );
    t->insertNode( 15,4 );
    t->insertNode( 5,1 );

    vector<pair<int,int> > p;
    t->toVectorOfPairs(p, t->getRoot());
    for (int i = 0 ; i < p.size();i++) {
        cout << "d = " << p[i].first << " f = " << p[i].second << endl;
    }
    float vectorSum = 0;
    float x = 10;
    for (auto& entry : p){
        if (entry.first < x) vectorSum += entry.first;
    }
    std::cout << "std::vector answer: " << vectorSum << std::endl;


    std::cout << "treap answer: " << t->sumSmallerThan(10);
}