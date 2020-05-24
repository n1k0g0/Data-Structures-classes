#include "queuel.h"
#include <stdexcept>


queueA::queueA(int cap): first {-1}, last {0}, bufferSize {cap} {
    queue = new float [cap];
}

queueA::queueA(const queueA& inQ) {
    first = inQ.first;
    last = inQ.last;
    bufferSize = inQ.bufferSize;
    queue = new float[bufferSize];
    for (int ite = 0; ite < bufferSize; ++ite){
        queue[ite] = inQ.queue[ite];
    }
}


queueA::~queueA(){
    delete [] queue;
}

queueA& queueA::operator=(const queueA &inQ) {

    if (this != &inQ) {
        first = inQ.first;
        last = inQ.last;
        bufferSize = inQ.bufferSize;
        if (queue) delete[](queue);
        queue = new float[bufferSize];
        for (int i = 0; i < bufferSize; ++i){
            queue[i] = inQ.queue[i];
        }
    }
    return *this;


}

void queueA::push(const int value){
    if (last % bufferSize == first % bufferSize){
        std::cout << "queue is full";
    }
    else{
        queue[last] = value;
        last = (last + 1) % bufferSize;
        if (first == -1) first = 0;
    }
    if ((++last % bufferSize) == (first))
    {
        bufferSize = bufferSize * 2;
        float* new_buffer = new float[bufferSize];
        if (last >= first)
        {
            for (int i = first; i < last + 1; ++i)
                new_buffer[i-first] = queue[i];
        }
        else
        {
            for (int i = first; i < (bufferSize / 2) + 1; ++i)
            {
                new_buffer[i] = queue[i];
            }

            for (int i = 0; i < last; ++i)
            {
                new_buffer[bufferSize / 2 - first + i] = queue[i];
            }
        }
        std::swap(queue, new_buffer);
        delete[] new_buffer;
    }
}

bool queueA::isEmpty() const{
    if (first == -1) return 1;
    return 0;
}

void queueA::pop(){ //pop,
    if (this->isEmpty()){
        throw std::logic_error("QueueA::pop() - empty queue");
    }
    else{
        first = (first + 1) % bufferSize;
        if (first == last) {
            last = 0;
            first = -1;
        }
    }
}

float& queueA::top(){
    if (this->isEmpty()){
        throw std::logic_error("QueueA::top() - empty queue");
    }
    std::cout << bufferSize << std::endl << std::endl;
    return queue[first];
}




