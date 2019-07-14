#ifndef __car_watcher_hpp__
#define __car_watcher_hpp__
#include "car.hpp"
#include <atomic>
/*
Manages the cars removing those that have spent the time they need 
to in the intersection and applying required delays
 */
class car_watcher
{
private:
    car * ch;
    int len;
    volatile std::atomic<bool> *b;
    /* data */
public:
    car_watcher(car * c,int car_len,std::atomic<bool> *b2);
    ~car_watcher();
    void run();
};

#endif