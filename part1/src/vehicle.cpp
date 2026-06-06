#include "../include/vehicle.hpp"
#include "../include/drone_exceptions.hpp"
#include "../include/drone_states.hpp"
#include <sstream>

void Vehicle::log_to_flight(std::string log, std::string timestamp){
    std::stringstream LOG;
    LOG << "(" << timestamp << "): " << log << "\n";
    flight_log.push_back(LOG.str());
}

void Vehicle::drain_battery(float amount){
    if (battery_level == 0) {
        status = CRITICAL_STATE;
        log_to_flight("Entered critical state", "0.0.0");
        throw BatteryDepletedError();
    }

    if (amount <= battery_level) battery_level-=amount;
    else battery_level=0;

    std::stringstream LOG;
    LOG << "Battery drained to " << battery_level;
    log_to_flight(LOG.str(), "0.0.0");
}

void Vehicle::charge_battery(float amount, int){
    if (status != "Charging"){
        throw InvalidStateError("Can not charge if not in charging state");
    } else {
        if (amount + battery_level <= 100) battery_level+=amount;
        else battery_level = 100;

        std::stringstream LOG;
        LOG << "Battery charged to " << battery_level;
        log_to_flight(LOG.str(), "0.0.0");
    }
}

bool Vehicle::is_critical(){
    if (status == CRITICAL_STATE) return true;
    else return false;
}

void Vehicle::set_status(std::string Status){
    if (Status==CRITICAL_STATE || Status==CHARGING_STATE || Status==FLYING_STATE || Status==GROUNDED_STATE) {
        status = Status;

        std::stringstream LOG;
        LOG << "Entered state " << status;
        log_to_flight(LOG.str(), "0.0.0");
    }
}

std::string Vehicle::get_name(){
    return name;
}

float Vehicle::get_battery(){
    return battery_level;
}

std::string Vehicle::get_status(){
    return status;
}

std::string Vehicle::get_flight_log(){
    std::string temp = "Flight Log";
    for (std::string p : flight_log){
        temp += "\n";
        temp += p;
    }
    return temp;
}