#include "car_watcher.hpp"
car_watcher::car_watcher(car* c,int car_len,std::atomic<bool> *b2)
{
    ch = c;
    len = car_len;
    b=b2;
}

car_watcher::~car_watcher()
{
}

void car_watcher::run(){
    while(*b){
        for (size_t i = 0; i < len; i++)
        {
            if(ch[i].get_inter()>0){
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout<< "A car just left Intersection " + ch->get_sect()<<std::endl;
                    ch[i].set_inter(0);
                    // std::cout<<ch[i].get_inter()<<std::endl;
            }
            if(ch[i].wait_flag){
                std::this_thread::sleep_for(std::chrono::seconds(3));
                ch[i].wait_flag=false;
                ch[i].approved=true;
            }
        }
    }
}