#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <vector>
#include "drone_states.hpp"

class Vehicle{
    private:
    std::string name;
    float battery_level;
    std::string status;
    std::vector<std::string> flight_log;

    protected:
    Vehicle(std::string Name, float Battery_level = 100, std::string Status = GROUNDED_STATE) :
    name(Name), battery_level(Battery_level), status(Status){}

    public:
    virtual std::string get_info()=0;
    void drain_battery(float amount);
    void charge_battery(float amount, int duration_seconds);
    bool is_critical();
    void set_status(std::string Status);

    void log_to_flight(std::string log, std::string timestamp);

    std::string get_name();
    float get_battery();
    std::string get_status();
    std::string get_flight_log();

    virtual ~Vehicle() {}
};

#endif