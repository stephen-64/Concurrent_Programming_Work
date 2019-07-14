#include <iostream>
#include "intersection.hpp"
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "car_watcher.hpp"

/*
Setups the cars and the intersection for us in the simulation
 */
int main(int argc, char* argv[]){
    srand(time(NULL));
    std::cout << "Beginning Light Simulation" << std::endl;
    intersection in = intersection();
    //Applied the required arbirtrary queues
    in.a_index = 6;
    car cah[in.a_index];
    in.b_index = 4;
    car cbh[in.a_index];
    in.c_index = 6;
    car cch[in.a_index];
    in.d_index = 3;
    car cdh[in.a_index];
    for (size_t i = 0; i < in.a_index; i++)
    {
        cah[i]=car((direc)(rand()%3),"a");
    }
    for (size_t i = 0; i < in.b_index; i++)
    {
        cbh[i]=car((direc)(rand()%3),"b");
    }
    for (size_t i = 0; i < in.c_index; i++)
    {
        cch[i]=car((direc)(rand()%3),"c");
    }
    for (size_t i = 0; i < in.d_index; i++)
    {
        cdh[i]=car((direc)(rand()%3),"d");
    }
    in.set_car_arrays(cah,cbh,cch,cdh);
    std::atomic<bool> b (true);
    car_watcher cw1 = car_watcher(cah,in.a_index,&b);
    car_watcher cw2 = car_watcher(cbh,in.b_index,&b);
    car_watcher cw3 = car_watcher(cch,in.c_index,&b);
    car_watcher cw4 = car_watcher(cdh,in.d_index,&b);
    std::thread cwt1(&car_watcher::run,&cw1);
    std::thread cwt2(&car_watcher::run,&cw2);
    std::thread cwt3(&car_watcher::run,&cw3);
    std::thread cwt4(&car_watcher::run,&cw4);
    std::thread f(&intersection::run,&in,&b);
    std::this_thread::sleep_for(std::chrono::seconds(60));
    b=false;
    f.join();
    cwt1.join();
    cwt2.join();
    cwt3.join();
    cwt4.join();
    std::cout << "Ending Light Simulation" << std::endl;
    return 0;   
}