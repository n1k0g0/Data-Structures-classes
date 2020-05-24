#include "queueA/queueA.h"
#include "queueL/queueL.h"
#include <exception>
#include <chrono>
#include <fstream>
#include <queue>

int main(int argc, const char * argv[]) {





    //METHODS TESTING


    std::string amountArrStr = "";




    //QUEUE ON ARRAYS TIME TESTING

    for (int r = 0; r < 10; ++r){
        Queuea q(1000);
        auto arraysEnqStart = std::chrono::high_resolution_clock::now();
        for (int ii = 0; ii < 1000; ++ii){
            q.push(ii);
        }
        auto arraysEnqFinish = std::chrono::high_resolution_clock::now();


        amountArrStr += std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(arraysEnqFinish - arraysEnqStart).count());
        amountArrStr += " ";


        for (int iPop = 0; iPop < 1000; ++iPop){
            q.pop();
        }
    }

    std::cout << amountArrStr << std::endl;








    //QUEUE ON LISTS TIME TESTING


    std::cout << std::endl << "CQueue: enqueueing and getting size" << std::endl << std::endl;
    CQueue<float> queue;

    std::string amountListStr = "";

    for (int z = 0; z < 10; ++z){
        auto listsEnqStart = std::chrono::high_resolution_clock::now();
        for (float j = 0; j < 1000; ++j){
            queue.EnQueue(j);
        }
        auto listsEnqFinish = std::chrono::high_resolution_clock::now();



        amountListStr += std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(listsEnqFinish - listsEnqStart).count());
        amountListStr += " ";


        int size = queue.getSize();
        std::cout << std::endl << size << std::endl << std::endl;
        auto lists_time_start = std::chrono::high_resolution_clock::now();

        for (int k = 0; k < size; ++k){
            queue.DeQueue();
        }

        auto lists_time_finish = std::chrono::high_resolution_clock::now();


    }


    std::cout << amountListStr << std::endl;



//здесь стоит делать std::queue


    std::queue<float> standardQueue;
    std::string amountStandQStr = "";
    for (int ind = 0; ind < 10; ++ind){

        auto standardQueueEnqStart = std::chrono::high_resolution_clock::now();
        for (int l = 0; l < 1000; ++l)
            standardQueue.push(5.1);
        auto standardQueueEnqFinish = std::chrono::high_resolution_clock::now();

        amountStandQStr += std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(standardQueueEnqFinish - standardQueueEnqStart).count());
        amountStandQStr += " ";


        auto standard_q_time_start = std::chrono::high_resolution_clock::now();
        for (int q = 0; q < 1000; ++q)
            standardQueue.pop();
        auto standard_q_time_finish = std::chrono::high_resolution_clock::now();
    }

    std::cout << amountStandQStr << std::endl;


/*
    std::list<float> standardList;
    std::string amountStandStr = "";

    for (int y = 0; y < 10; ++y){

        auto standardEnqStart = std::chrono::high_resolution_clock::now();
        for (int l = 0; l < 1000; ++l)
            standardList.push_back(5.1);
        auto standardEnqFinish = std::chrono::high_resolution_clock::now();

        amountStandStr += std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(standardEnqFinish - standardEnqStart).count());
        amountStandStr += " ";


        auto standard_time_start = std::chrono::high_resolution_clock::now();
        for (int q = 0; q < 1000; ++q)
            standardList.pop_back();
        auto standard_time_finish = std::chrono::high_resolution_clock::now();
    }


    std::cout << amountStandStr << std::endl;


*/







    std::cout << std::endl << "Testing copying and copy constructor" << std::endl << std::endl;



    Queuea q4(1000);

    q4.push(1);

    std::cout << q4.top() << std::endl;

    //adding elements into queue below

    for (int iii = 0; iii < 1000; ++iii){
        q4.push(iii);
    }



    Queuea q2 = q4;
    Queuea q3 = q4;
    Queuea q5(10);
    for (int iq5 = 0; iq5 < 10; ++iq5){
        q5.push(0);
    }

    std::cout << q2.top() << std::endl;



    std::ofstream outputFile("data.txt", std::ofstream::binary);
    outputFile << amountArrStr  << amountListStr << amountStandQStr;
    outputFile.close();

/*
    q5 = q2;

    std::cout << q5.top() << std::endl;



    */
/*

    Queuea q3(0);
    q3 = q2;

    std::cout << q2.top() << std::endl;
*/

    return 0;
}
