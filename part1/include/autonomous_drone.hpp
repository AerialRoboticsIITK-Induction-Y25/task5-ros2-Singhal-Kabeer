#ifndef AUTONOMOUSDRONE_H
#define AUTONOMOUSDRONE_H

#include "mission_drone.hpp"
#include <string>
#include <tuple>
#include <vector>

class AutonomousDrone: public MissionDrone{
    private:
    std::string ai_mode; // "manual", "auto", "return_home"
    std::tuple<float, float, float> home_position;
    std::vector<std::string> obstacle_log;

    public:
    void set_ai_mode(const std::string& mode); //"return_home" inserts home as next waypoint.
    void detect_obstacle(std::tuple<float,float,float> position, const std::string& severity); // logs with timestamp; calls emergency_stop() if severity is "high".
    std::vector<std::tuple<float, float, float>> auto_replan(const std::vector<std::tuple<float,float,float>>& obstacles); // returns a new waypoint list avoiding obstacles within 5 units.
    std::string get_info();

    AutonomousDrone(
        std::string DroneName,
        std::string MissionName,
        float MaxAltitude,
        std::tuple<float, float, float> home,
        float Battery_level = 100,
        std::string Status = GROUNDED_STATE,
        std::string AIMode = "auto",
        std::vector<std::tuple<float, float, float>> way = std::vector<std::tuple<float, float, float>>()):
    MissionDrone(DroneName, MissionName, MaxAltitude, Battery_level, Status, way), ai_mode(AIMode), home_position(home){}
};

#endif