#include "../include/mission_drone.hpp"
#include "../include/drone_exceptions.hpp"
#include "../include/drone_states.hpp"
#include <sstream>

std::tuple<float, float, float> MissionDrone::next_waypoint(){

    if (this->get_status()!=FLYING_STATE) throw InvalidStateError();

    drain_battery(1.5);
    current_waypoint_index++;

    std::pair<std::tuple<float,float,float>, std::string> visit;
    visit.first = waypoints[current_waypoint_index];
    visit.second = "0.0.0";
    visited_waypoints.push_back(visit);

    std::stringstream LOG;
    LOG << "Visited waypoint (" << std::get<0>(waypoints[current_waypoint_index])
        << std::get<1>(waypoints[current_waypoint_index])
        << std::get<2>(waypoints[current_waypoint_index])
        << ")";
    log_to_flight(LOG.str(), "0.0.0");

    return waypoints[current_waypoint_index];
}

void MissionDrone::skip_waypoint(const std::string& reason){
    std::stringstream LOG;
    LOG << "Skipping waypoint (" << std::get<0>(waypoints[current_waypoint_index+1])
        << std::get<1>(waypoints[current_waypoint_index+1])
        << std::get<2>(waypoints[current_waypoint_index+1])
        << ")"
        << " because"
        << reason;
    
    log_to_flight(LOG.str(), "0.0.0");

    waypoints.erase(waypoints.begin() + current_waypoint_index+1);
}

bool MissionDrone::mission_complete(){
    if ((waypoints.begin()+current_waypoint_index) == waypoints.end()) return true;
    else return false;
}

std::string MissionDrone::mission_summary(){
    return this->get_flight_log();
}

std::string MissionDrone::get_info(){

    std::stringstream answer;
    answer << "MissionDrone getinfo" << "\n";
    answer << "===================================" << "\n";
    answer << "Drone Name        " << this->get_name() << "\n";
    answer << "Mission Name      " << mission_name << "\n";
    answer << "Battery Level     " << this->get_battery() << "\n";
    answer << "Status            " << this->get_status() << "\n";
    answer << "Altitude          " << this->get_altitude() << "\n";
    answer << "Current Waypoint  " << current_waypoint_index << " (zero indexed) "<< "\n";
    answer << "Total Waypoints   " << waypoints.size() << "\n";
    answer << "===================================" << "\n";
    return answer.str();
}

void MissionDrone::add_next_waypoint(float x, float y, float z){
    std::tuple<float, float, float> point(x, y, z);
    waypoints.insert(waypoints.begin() + (current_waypoint_index+1), point);

    std::stringstream LOG;
    LOG << "Adding waypoint (" << std::get<0>(waypoints[current_waypoint_index+1])
        << std::get<1>(waypoints[current_waypoint_index+1])
        << std::get<2>(waypoints[current_waypoint_index+1])
        << ")";
    
    log_to_flight(LOG.str(), "0.0.0");
}
