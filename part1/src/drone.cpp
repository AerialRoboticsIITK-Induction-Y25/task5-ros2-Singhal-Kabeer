#include "../include/drone.hpp"
#include "../include/drone_exceptions.hpp"
#include "../include/drone_states.hpp"
#include <sstream>

void Drone::take_off(float target_altitude){
    if (this->get_status() != GROUNDED_STATE) {
        throw InvalidStateError();
    }
    if (target_altitude > max_altitude) throw AltitudeError();
    else {
        altitude = target_altitude;
        this->set_status(FLYING_STATE);
    }
}

void Drone::land(){
    if (this->get_status() != FLYING_STATE && this->get_status() != CRITICAL_STATE) {
        throw InvalidStateError();
    }
    this->set_status("Grounded");
    altitude=0;
}

void Drone::emergency_stop(){
    if (this->get_status() != FLYING_STATE && this->get_status() != CRITICAL_STATE) {
        throw InvalidStateError();
    }
    this->set_status("Grounded");
    altitude=0;
    this->drain_battery(30);
}

std::string Drone::get_info(){
    std::stringstream answer;
    answer << "Drone getinfo" << "\n";
    answer << "===================================" << "\n";
    answer << "Drone Name        " << this->get_name() << "\n";
    answer << "Battery Level     " << this->get_battery() << "\n";
    answer << "Status            " << this->get_status() << "\n";
    answer << "Altitude          " << altitude << "\n";
    answer << "===================================" << "\n";
    return answer.str();
}