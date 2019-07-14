/**
 * Represents the ligths at the intersection changes at a desired interval set in the .cpp file
 */
#ifndef __light_hpp__
#define __light_hpp__
#include<atomic>
#include "enum_lights.hpp"
class light
{
private:
    color l1;
    color l2;
    volatile std::atomic<bool>* looper;
public:
    light();
    ~light();
    void run(volatile std::atomic_bool* run);
    color get_lightAC();
    color get_lightBD();
};
#endif