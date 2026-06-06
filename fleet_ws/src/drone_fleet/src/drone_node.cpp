#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <iostream>
#include <chrono>
#include <sstream>

using namespace std::chrono_literals;

class drone_node : public rclcpp::Node{
    private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_publisher;
    rclcpp::TimerBase::SharedPtr status_timer;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr waypoint_publisher;
    rclcpp::TimerBase::SharedPtr waypoint_timer;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr alert_publisher;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr telemetry_publisher;
    rclcpp::TimerBase::SharedPtr telemetry_timer;

    std::string drone_name;
    std::string mission_name;
    float battery_level;
    bool is_grounded;

    public:
    drone_node():Node("drone_manager"), battery_level(100), is_grounded(false), count_status_published(0), waypoint(1){

        this->declare_parameter<std::string>("drone_name", "best_drone");
        this->declare_parameter<std::string>("mission_name", "best_mission");
        this->declare_parameter<double>("initial_battery", 100.0);

        drone_name = this->get_parameter("drone_name").as_string();
        mission_name = this->get_parameter("mission_name").as_string();
        battery_level = this->get_parameter("initial_battery").as_double();

        status_publisher = this->create_publisher<std_msgs::msg::String>("/drone/"+drone_name+"/status", 10);
        status_timer = this->create_wall_timer(1s, [this](){this->publish_status();});

        waypoint_publisher = this->create_publisher<std_msgs::msg::String>("/drone/"+drone_name+"/mission_complete", 10);
        waypoint_timer = this->create_wall_timer(3s, [this](){this->publish_waypoint();});

        alert_publisher = this->create_publisher<std_msgs::msg::String>("/drone/"+drone_name+"/alert", 10);

        telemetry_publisher = this->create_publisher<std_msgs::msg::String>("/drone/"+drone_name+"/telemetry", 10);
        telemetry_timer = this->create_wall_timer(2s, [this](){this->publish_telemetry();});
    }

    private:

    int count_status_published;
    void publish_status(){
        std_msgs::msg::String status_message;

        if (battery_level > 0){    
            status_message.data = "Status : Battery levels are going down";
            battery_level -= 1.5;

        } else {
            if (is_grounded == false){
                status_message.data = "Status : Battery is dead";
                publish_alert();
                is_grounded = true;
            }
        }

        //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", status_message.data.c_str());
        status_publisher->publish(status_message);
    }
    
    int waypoint;
    void publish_waypoint(){
        if (battery_level>0){
            if (waypoint==5) {
                std_msgs::msg::String waypoint_message;
                waypoint_message.data = "Completed Mission. Re doing it now.";
                //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", waypoint_message.data.c_str());
                waypoint_publisher->publish(waypoint_message);
                waypoint=0;
            } else waypoint++;
        }
    }

    void publish_alert(){
        std_msgs::msg::String alert_message;
        alert_message.data = "Dead";
        //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", alert_message.data.c_str());
        alert_publisher->publish(alert_message);
    }

    void publish_telemetry(){
        std_msgs::msg::String telemetry_message;
        std::stringstream tel_message;
        tel_message << battery_level;
        telemetry_message.data = tel_message.str();
        //RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", telemetry_message.data.c_str());
        telemetry_publisher->publish(telemetry_message);
    }
    
};

int main(int argc, char * argv[])
{
    
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<drone_node>());
    rclcpp::shutdown();
    
    return 0;
}