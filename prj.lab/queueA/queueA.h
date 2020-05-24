#ifndef queuea_h
#define queuea_h

#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

class queueA {
public:
    queueA(int cap);
    queueA(const queueA& inQ);
    ~queueA();
    void push(const int value);
    void pop();
    float& top();
    bool isEmpty() const;
    queueA& operator=(const queueA& inQ);
private:
    int first{-1};
    int last{-1};
    int bufferSize{0};
    float *queue{nullptr};
};


#endif