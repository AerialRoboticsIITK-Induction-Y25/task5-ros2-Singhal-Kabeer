#ifndef DRONE_H
#define DRONE_H

#include "vehicle.hpp"

class Drone: public Vehicle{
    private:
    float altitude;
    float max_altitude;

    public:
    void take_off(float target_altitude); // throws AltitudeError if limit exceeded.
    void land();
    void emergency_stop(); // drains battery by 30 as a penalty.
    float get_altitude(){
        return altitude;
    }
    std::string get_info();

    Drone(std::string Name, float Max, float Battery_level = 100, std::string Status = GROUNDED_STATE) :
    Vehicle(Name, Battery_level, Status), max_altitude(Max){}
};

#endif