#ifndef __intersection_hpp__
#define __intersection_hpp__
#include "light.hpp"
#include "car.hpp"
#include <thread>
#include <iostream>

/**
 * Representation of an intersection contains all the lined 
 * up cars and the lights
 */
class intersection
{
private:
    light tlight = light();
    car ca = car();
    car cb = car();
    car cc = car();
    car cd = car();
    car *cah;
    car *cbh;
    car *cch;
    car *cdh;
    int a=0;
    int b=0;
    int c=0;
    int d=0;
    volatile std::atomic<bool>* loop_runner;
    /* data */
public:
    int a_index,b_index,c_index,d_index=0;
    intersection();
    ~intersection();
    void run(std::atomic<bool>* b2);
    void set_car_arrays(car *c1,car *c2,car *c3,car *c4);
};


#endif 