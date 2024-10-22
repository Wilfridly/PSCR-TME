#pragma once

#include <mutex>
#include <condition_variable>

class Barrier{
    int counter;
    const int N;
    std::mutex m;
    std::condition_variable cv;
public:
    Barrier(int N):counter(0),N(N){}
    
    void done(){
        std::unique_lock<std::mutex> lg(m);
        counter++;
        if(counter == N){
            cv.notify_all();
        }
    }
    
    void waitFor(){
        std::unique_lock<std::mutex> lg(m);
        while(counter != N){
            cv.wait(lg);
        }
    }

};

