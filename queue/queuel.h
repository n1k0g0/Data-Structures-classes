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

class Queuea {
public:
    Queuea(int cap);
    Queuea(const Queuea& inQ);
    ~Queuea();
    void push(const int value); //adding to the end
    void pop(); //поп
    float& top();//топ
    bool is_empty() const;
    Queuea& operator=(const Queuea& inQ);
private:
    int first{-1};
    int last{-1};
    int bufferSize{0};
    float *queue{nullptr}; //походу надо на float


};


/*


 first last
 size_t
float* ptr{nullptr}

 size{0};

 */

template<class T>
class CQueue
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

    CQueue() : m_pBegin(0), m_pEnd(0) //???
    {
    }

    virtual ~CQueue()
    {
    }

    void EnQueue(T& data) //пуш
    {
        leaf* nleaf = new leaf(data, m_pEnd);
        nleaf->pnext = nleaf;
        if (m_pEnd) m_pEnd->pnext = nleaf;
        m_pEnd = nleaf;
        if (m_pBegin == 0){
            m_pBegin = nleaf;
        }
    }


    T DeQueue() //throw error, поп
    {
        if (m_pEnd == 0) throw new std::exception;
        T beginData = m_pBegin->data;
        if (m_pBegin == m_pEnd) m_pBegin = m_pEnd = 0;
        else{
            m_pBegin = m_pBegin->pnext;
        }
        return beginData;
    }

    bool isQueueEmpty()
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

    void clear() //untested
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




#endif /* queuea_h */


/*std array фикс память на стеке
//std vector память в куче

 еще предыдущие дела на птр и юник птр дз
 мейк юник
 для экземпляра и массива
 дефолт


 */