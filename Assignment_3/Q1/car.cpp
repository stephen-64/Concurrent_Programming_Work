#include"car.hpp"
car::car()
{
}

car::car(direc direction,std::string inter)
{
    in_inter = 0;
    intersection = inter;
    car_direction = direction;
}


car::~car()
{
}


void car::set_direc(direc direction){
    car_direction = direction;
}

direc car::get_direc(){
    return car_direction;
}


void car::set_inter(int set){
    //std::mutex m;
   // m.lock();
    in_inter = set;
   // m.unlock();
}

int car::get_inter(){
    return in_inter;
}

std::string car::get_sect(){
    return intersection;
}