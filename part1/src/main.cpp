#include "../include/vehicle.hpp"
#include "../include/drone.hpp"
#include "../include/mission_drone.hpp"
#include "../include/autonomous_drone.hpp"
#include "../include/drone_exceptions.hpp"

#include <iostream>
#include <tuple>

void TestBatteryAndChargingExceptions(Vehicle* vehicle1){
    vehicle1->drain_battery(50);
    vehicle1->drain_battery(60);

    try
    {
        vehicle1->drain_battery(10);
    }
    catch(const BatteryDepletedError& e)
    {
        std::cout << "Cannot complete this action. Not enough battery. Land the drone, enter charging mode, charge, then takeoff again.\n";
    }

    try
    {
        vehicle1->charge_battery(50, 50);
    }
    catch(const InvalidStateError& e)
    {
        std::cout << "Cannot complete since drone is not in charging mode\n";
    }

    vehicle1->set_status(CHARGING_STATE);
    vehicle1->charge_battery(50, 50);
    vehicle1->drain_battery(10);
    
    std::cout << vehicle1->get_info() << std::endl;
}

void TestTakeoff(Vehicle* vehicle, float amount){
    Drone * drone = (Drone *) vehicle;
    try{
        drone->take_off(amount);
    } catch (const AltitudeError& e){
        std::cout << "Cant go that high\n";
    }
    std::cout << vehicle->get_info() << std::endl;
}

void TestHostileObstacle(Vehicle* vehicle){
    AutonomousDrone* autodrone = (AutonomousDrone *) vehicle;

    try
    {
        autodrone->detect_obstacle(std::tuple<float, float, float>(1, 1, 1), "high");
    }
    catch(const BatteryDepletedError& e)
    {
        std::cout << "Dont even have enough energy to emergency land. Drone crashed. Do not use further.\n";
    }
    catch(const InvalidStateError& e)
    {
        std::cout << "Drone isnt even flying. Detected obstacle. Didnt care. Didnt do anything.\n";
    }
    std::cout << vehicle->get_info() << std::endl;
}

int main(void){
    Vehicle* vehicle1 = new Drone("Alpha", 500);
    Vehicle* vehicle2 = new MissionDrone("Beta", "Defeat Alpha", 550);
    Vehicle* vehicle3 = new AutonomousDrone("Gamma", "Eat 5 stars, do nothing", 100, std::tuple<float, float, float>(0, 0, 0));

    // Printing info
    std::vector<Vehicle *> drones{vehicle1, vehicle2, vehicle3};
    for (Vehicle * a : drones){
        std::cout << a->get_info() << std::endl;
        std::cout << a->get_info() << std::endl;
        std::cout << a->get_info() << std::endl;
    }

    TestBatteryAndChargingExceptions(vehicle1);
    TestTakeoff(vehicle2, 200);
    TestTakeoff(vehicle3, 200);
    TestHostileObstacle(vehicle3);
    TestTakeoff(vehicle3, 50);
    TestHostileObstacle(vehicle3); // no exception
    TestTakeoff(vehicle3, 50);
    vehicle3->drain_battery(100);
    TestHostileObstacle(vehicle3); // no exception
    
    std::cout << "\n\n\nComplete mission with an autonomous drone:\n\n";

    // take off, iterate all waypoints, simulate a high-severity obstacle, print mission summary.
    std::tuple<float, float, float> Waypoint1(10, 10, 10);
    std::tuple<float, float, float> Waypoint2(10, 5, 10);
    std::tuple<float, float, float> Waypoint3(3, 10, 2);
    std::tuple<float, float, float> Waypoint4(10, 50, 1000);
    std::tuple<float, float, float> Waypoint5(10, 0, 73);
    std::vector<std::tuple<float, float, float>> TestWaypoints{Waypoint1, Waypoint2, Waypoint3, Waypoint4, Waypoint5};

    AutonomousDrone* TestDrone = new AutonomousDrone("Test Drone", "Testing", 500, std::tuple<float, float, float>(0, 0, 0), 100, GROUNDED_STATE, "auto", TestWaypoints);

    std::cout << TestDrone->get_info();

    TestDrone->take_off(200);
    TestDrone->next_waypoint();
    TestDrone->next_waypoint();
    TestDrone->skip_waypoint("my life my rulz");
    TestDrone->detect_obstacle(std::tuple<float, float, float>(0, 0, 0), "low");
    TestDrone->detect_obstacle(std::tuple<float, float, float>(0, 0, 0), "high");
    TestDrone->take_off(300);
    TestDrone->next_waypoint();
    TestDrone->next_waypoint();

    std::cout << TestDrone->get_info();
    if (TestDrone->mission_complete()) std::cout << "Success";
    else std::cout << "Pending";

    std::cout << TestDrone->mission_summary();


    delete TestDrone;
    delete vehicle1;
    delete vehicle2;
    delete vehicle3;
    return 0;
}