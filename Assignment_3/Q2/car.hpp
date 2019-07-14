#ifndef __car_hpp__
#define __car_hpp__
#include "enum_dir.hpp"
#include <thread>
#include <atomic>
#include <iostream>
#include <mutex>
#include <string>
/*
A representation of a car used in this project
contains several peices of useful information such as were
the care is and it's direction
 */
class car
{
private:
    direc car_direction;
    std::string intersection;
    int in_inter = 0;

    /* data */
public:
    bool wait_flag = false;
    bool approved = false;
    car();
    car(direc direction,std::string inter);
    ~car();
    void set_direc(direc direction);
    direc get_direc();
    void runner();
    void set_inter(int set);
    int get_inter();
    std::string get_sect();
};
#endif