#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_srvs/srv/trigger.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

class fleet_manager: public rclcpp::Node{
    private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr alpha_status_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr beta_status_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr gamma_status_subscriber;

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr alpha_alert_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr beta_alert_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr gamma_alert_subscriber;

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr alpha_mission_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr beta_mission_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr gamma_mission_subscriber;

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr alpha_telemetry_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr beta_telemetry_subscriber;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr gamma_telemetry_subscriber;
    
    rclcpp::TimerBase::SharedPtr fleet_report_timer;

    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr instant_report_service;

    public:
    fleet_manager(): Node("fleet_manager"){
        alpha_status_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/alpha/status", 10, [this](const std_msgs::msg::String & msg){this->read_alpha_status(msg);});
        beta_status_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/beta/status", 10, [this](const std_msgs::msg::String & msg){this->read_beta_status(msg);});
        gamma_status_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/gamma/status", 10, [this](const std_msgs::msg::String & msg){this->read_gamma_status(msg);});

        alpha_alert_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/alpha/alert", 10, [this](const std_msgs::msg::String & msg){this->read_alpha_alert(msg);});
        beta_alert_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/beta/alert", 10, [this](const std_msgs::msg::String & msg){this->read_beta_alert(msg);});
        gamma_alert_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/gamma/alert", 10, [this](const std_msgs::msg::String & msg){this->read_gamma_alert(msg);});

        alpha_mission_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/alpha/mission_complete", 10, [this](const std_msgs::msg::String & msg){this->read_alpha_mission(msg);});
        beta_mission_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/beta/mission_complete", 10, [this](const std_msgs::msg::String & msg){this->read_beta_mission(msg);});
        gamma_mission_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/gamma/mission_complete", 10, [this](const std_msgs::msg::String & msg){this->read_gamma_mission(msg);});

        alpha_telemetry_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/alpha/telemetry", 10, [this](const std_msgs::msg::String & msg){this->read_alpha_telemetry(msg);});
        beta_telemetry_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/beta/telemetry", 10, [this](const std_msgs::msg::String & msg){this->read_beta_telemetry(msg);});
        gamma_telemetry_subscriber = this->create_subscription<std_msgs::msg::String>("/drone/gamma/telemetry", 10, [this](const std_msgs::msg::String & msg){this->read_gamma_telemetry(msg);});
    
        fleet_report_timer = this->create_wall_timer(5s, [this](){this->print_report_table();});

        instant_report_service = this->create_service<std_srvs::srv::Trigger>("/fleet/status_report", [this](const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response){this->handle_instant_report_service(request, response);});
    }

    private:

    void handle_instant_report_service(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response){
        this->print_report_table();
        std::cout << "This came from the service not timer" << std::endl;

        response->success=true;
        response->message = "printed to console";

        (void) request;
    }

    void print_report_table(){
        std::cout << "Printing report table, now" << std::endl;
    }

    // statuses
    void read_alpha_status(const std_msgs::msg::String & msg) {
        (void) msg;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    void read_beta_status(const std_msgs::msg::String & msg) {
        (void) msg;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    void read_gamma_status(const std_msgs::msg::String & msg) {
        (void) msg;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }

    // alerts
    void read_alpha_alert(const std_msgs::msg::String & msg) {
        (void) msg;
        std::cout << "(0.0.0) alpha dead" << std::endl;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    void read_beta_alert(const std_msgs::msg::String & msg) {
        (void) msg;
        std::cout << "(0.0.0) beta dead" << std::endl;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    void read_gamma_alert(const std_msgs::msg::String & msg) {
        (void) msg;
        std::cout << "(0.0.0) gamma dead" << std::endl;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }

    // missions
    void read_alpha_mission(const std_msgs::msg::String & msg) {
        (void) msg;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    void read_beta_mission(const std_msgs::msg::String & msg) {
        (void) msg;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    void read_gamma_mission(const std_msgs::msg::String & msg) {
        (void) msg;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }

    // telemetrys
    void read_alpha_telemetry(const std_msgs::msg::String & msg) {
        (void) msg;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    void read_beta_telemetry(const std_msgs::msg::String & msg) {
        (void) msg;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    void read_gamma_telemetry(const std_msgs::msg::String & msg) {
        (void) msg;
        // RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }


};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<fleet_manager>());
    rclcpp::shutdown();
    
    return 0;
}