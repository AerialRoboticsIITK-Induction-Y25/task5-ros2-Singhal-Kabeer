#ifndef MISSIONDRONE_H
#define MISSIONDRONE_H

#include "drone.hpp"
#include <string>
#include <vector>
#include <tuple>

class MissionDrone: public Drone{
    private:
    std::string mission_name;
    std::vector<std::tuple<float, float, float>> waypoints;
    int current_waypoint_index;
    std::vector<std::pair<std::tuple<float,float,float>, std::string>> visited_waypoints; // point and timestamp

    protected:
    const std::vector<std::tuple<float, float, float>>& get_waypoints() const {
        return waypoints;
    }

    public:
    std::tuple<float, float, float> next_waypoint(); // returns current position as tuple; drains battery by 1.5.
    void skip_waypoint(const std::string& reason);
    bool mission_complete();
    std::string mission_summary();
    std::string get_info();
    void add_next_waypoint(float, float, float);

    MissionDrone(std::string DroneName,
        std::string MissionName,
        float MaxAltitude,
        float Battery_level = 100,
        std::string Status = GROUNDED_STATE,
        std::vector<std::tuple<float, float, float>> way = std::vector<std::tuple<float, float, float>>()) :
    Drone(DroneName, MaxAltitude, Battery_level, Status), mission_name(MissionName), waypoints(way), current_waypoint_index(-1){}

    std::string get_mission_name(){
        return mission_name;
    }

    int get_current_waypoint_index(){
        return current_waypoint_index;
    }

    int get_count_waypoints(){
        return waypoints.size();
    }
};

#endif