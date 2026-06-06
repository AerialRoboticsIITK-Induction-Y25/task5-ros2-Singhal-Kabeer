#include <string>
#include <tuple>
#include <vector>
#include <sstream>
#include "../include/autonomous_drone.hpp"

void AutonomousDrone::set_ai_mode(const std::string& mode){
    if (mode=="manual"||mode=="auto"||mode=="return_home"){
        ai_mode = mode;

        std::stringstream LOG;
        LOG << "Setting AI mode to " << mode;
        log_to_flight(LOG.str(), "0.0.0");
    }

    if (mode=="return_home"){
        this->add_next_waypoint(std::get<0>(home_position), std::get<1>(home_position), std::get<2>(home_position));
    }
}

void AutonomousDrone::detect_obstacle(std::tuple<float,float,float> position, const std::string& severity){
    std::stringstream LOG;
    LOG << "Detected obstacle at (" << std::get<0>(position)
        << std::get<1>(position)
        << std::get<2>(position)
        << ") of severity "
        << severity;
    log_to_flight(LOG.str(), "0.0.0");

    if (severity == "high"){
        this->emergency_stop();
    }
}

std::vector<std::tuple<float, float, float>> AutonomousDrone::auto_replan(const std::vector<std::tuple<float,float,float>>& obstacles){
    const std::vector<std::tuple<float, float, float>>& original = this->get_waypoints();
    std::vector<std::tuple<float, float, float>> answer;
    bool remove;
    float delta_x, delta_y, delta_z;
    for (std::tuple<float, float, float> point : original){
        remove=0;
        for (std::tuple<float, float, float> obstacle : obstacles){
            delta_x = std::get<0>(point) - std::get<0>(obstacle);
            delta_y = std::get<1>(point) - std::get<1>(obstacle);
            delta_z = std::get<2>(point) - std::get<2>(obstacle);
            if (delta_x*delta_x+delta_y*delta_y+delta_z*delta_z <= 25){
                remove = 1;
                break;
            }
        }
        if (remove==0) answer.push_back(point);
    }

    return answer;
}

std::string AutonomousDrone::get_info(){

    std::stringstream answer;
    answer << "AutonomousDrone getinfo" << "\n";
    answer << "===================================" << "\n";
    answer << "Drone Name        " << this->get_name() << "\n";
    answer << "Mission Name      " << this->get_mission_name() << "\n";
    answer << "Battery Level     " << this->get_battery() << "\n";
    answer << "Status            " << this->get_status() << "\n";
    answer << "AI Mode           " << ai_mode << "\n";
    answer << "Altitude          " << this->get_altitude() << "\n";
    answer << "Current Waypoint  " << this->get_current_waypoint_index() << " (zero indexed) "<< "\n";
    answer << "Total Waypoints   " << this->get_count_waypoints() << "\n";
    answer << "===================================" << "\n";
    return answer.str();
}