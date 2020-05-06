//
//  queuea.h
//  queuea
//
//  Created by Николай Горбачев on 12.02.2020.
//  Copyright © 2020 Николай Горбачев. All rights reserved.
//

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




template<class T>
class queueL
{
private:
    struct leaf
    {
        T data;
        leaf * pnext;
        leaf(T& _data, leaf * _pnext)
        {
            data = _data;
            pnext = _pnext;
        }
    };
public:

    queueL() : m_pBegin(0), m_pEnd(0) {
    }
    virtual ~queueL() {
    }
    void push(T& data) {
        leaf* nleaf = new leaf(data, m_pEnd);
        nleaf->pnext = nleaf;
        if (m_pEnd) m_pEnd->pnext = nleaf;
        m_pEnd = nleaf;
        if (m_pBegin == 0){
            m_pBegin = nleaf;
        }
    }
    void pop() {
        if (m_pEnd == 0) throw new std::exception;
        T beginData = m_pBegin->data;
        if (m_pBegin == m_pEnd) m_pBegin = m_pEnd = 0;
        else{
            m_pBegin = m_pBegin->pnext;
        }
    }

    T top(){
        if (m_pBegin == 0) throw new std::exception;
        return m_pBegin->data;
    }

    bool isEmpty()
    {
        if (m_pEnd == 0) {
            return 1;
        }
        else return 0;
    }

    int getSize()
    {
        int size = 0;
        leaf* lleaf = m_pBegin;
        if (lleaf){
            ++size;
        }
        while (lleaf && (lleaf != lleaf->pnext)){
            lleaf = lleaf->pnext;
            ++size;
        }
        return size;
    }

    void clear()
    {
        leaf* itLeaf = m_pBegin;
        leaf* itNextLeaf = m_pBegin->pnext;
        while(itNextLeaf){
            delete itLeaf;
            itLeaf = itNextLeaf;
            itNextLeaf = itNextLeaf->pnext;
        }
    }

private:
    leaf* m_pBegin, *m_pEnd;
};




#endif

