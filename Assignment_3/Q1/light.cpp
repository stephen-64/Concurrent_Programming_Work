#include"light.hpp"
#include<iostream>
#include<thread>
light::light()
{
    l1=green;
    l2=red;
}

light::~light()
{
}

void light::run(volatile std::atomic_bool* run){
    looper = run;
    while(*looper){
        if (l1==green)
        {
            std::cout<< "The Light is currently Green at A and C and Red at B and D"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10));
            l1=yellow;
            std::cout<< "The Light is currently Yellow at A and C" <<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            l1=red;
            l2=green;
            std::cout<< "The Light is currently Red at A and C and Green at B and D"<<std::endl;
        }
        else
        {
            std::cout<< "The Light is currently Green at B and D and Red at A and C"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10));
            l2=yellow;
            std::cout<< "The Light is currently Yellow at B and D" <<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            l2=red;
            l1=green;
            std::cout<< "The Light is currently Red at B and D and Green at B and D"<<std::endl;
            /* code */
        }
        
    }
}

color light::get_lightAC(){
    return l1;
}

color light::get_lightBD(){
    return l2;
}

