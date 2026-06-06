#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <deque>
#include <sstream>
#include <chrono>

using namespace std::chrono_literals;

class health_monitor : public rclcpp::Node{
    private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr alpha_telemetry_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr beta_telemetry_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr gamma_telemetry_subscriber;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr fleet_warning_publisher;

    std::deque<float> alpha_battery_levels{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::deque<float> beta_battery_levels{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::deque<float> gamma_battery_levels{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr fleet_summary_publisher;
    rclcpp::TimerBase::SharedPtr fleet_summary_timer;

    public:
    health_monitor() : Node("health_monitor"){
        alpha_telemetry_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/alpha/telemetry", 10, [this](const std_msgs::msg::String& msg){this->watch_alpha_telemetry(msg);});
        beta_telemetry_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/beta/telemetry", 10, [this](const std_msgs::msg::String& msg){this->watch_beta_telemetry(msg);});
        gamma_telemetry_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/gamma/telemetry", 10, [this](const std_msgs::msg::String& msg){this->watch_gamma_telemetry(msg);});
    
        fleet_warning_publisher = this->create_publisher<std_msgs::msg::String>("/fleet/health_warning", 10);

        fleet_summary_publisher = this->create_publisher<std_msgs::msg::String>("/fleet/health_summary", 10);
        fleet_summary_timer = this->create_wall_timer(10s, [this](){this->publish_health_summary();});
    }

    private:
    void watch_alpha_telemetry(const std_msgs::msg::String& msg){
        std::stringstream tel_message(msg.data);
        float new_bat;
        tel_message >> new_bat;
        float drain_rate = (alpha_battery_levels.back() - new_bat)/2;

        alpha_battery_levels.pop_front();
        alpha_battery_levels.push_back(new_bat);
        
        if (drain_rate > 1.5) {
            std_msgs::msg::String warning_message;
            warning_message.data = "alpha bad battery drain";
            fleet_warning_publisher->publish(warning_message);

            RCLCPP_INFO(this->get_logger(), "I heard: '%f' and bad drain rate", new_bat);
        } else {
            RCLCPP_INFO(this->get_logger(), "I heard: '%f' and normal drain rate", new_bat);
        }
    }
    void watch_beta_telemetry(const std_msgs::msg::String& msg){
        std::stringstream tel_message(msg.data);
        float new_bat;
        tel_message >> new_bat;
        float drain_rate = (beta_battery_levels.back() - new_bat)/2;

        beta_battery_levels.pop_front();
        beta_battery_levels.push_back(new_bat);
        
        if (drain_rate > 1.5) {
            std_msgs::msg::String warning_message;
            warning_message.data = "beta bad battery drain";
            fleet_warning_publisher->publish(warning_message);

            RCLCPP_INFO(this->get_logger(), "I heard: '%f' and bad drain rate", new_bat);
        } else {
            RCLCPP_INFO(this->get_logger(), "I heard: '%f' and normal drain rate", new_bat);
        }
    }
    void watch_gamma_telemetry(const std_msgs::msg::String& msg){
        std::stringstream tel_message(msg.data);
        float new_bat;
        tel_message >> new_bat;
        float drain_rate = (gamma_battery_levels.back() - new_bat)/2;

        gamma_battery_levels.pop_front();
        gamma_battery_levels.push_back(new_bat);
        
        if (drain_rate > 1.5) {
            std_msgs::msg::String warning_message;
            warning_message.data = "gamma bad battery drain";
            fleet_warning_publisher->publish(warning_message);

            RCLCPP_INFO(this->get_logger(), "I heard: '%f' and bad drain rate", new_bat);
        } else {
            RCLCPP_INFO(this->get_logger(), "I heard: '%f' and normal drain rate", new_bat);
        }
    }

    void publish_health_summary(){
        std_msgs::msg::String health_summary_message;
        health_summary_message.data = "Table for health summary";
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", health_summary_message.data.c_str());
        fleet_summary_publisher->publish(health_summary_message);
    }
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<health_monitor>());
    rclcpp::shutdown();
    
    return 0;
}