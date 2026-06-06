cmake_minimum_required(VERSION 3.8)
project(drone_fleet)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#set(PART1_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../part1)
#include_directories(
#  include
#  ${PART1_DIR}/include
#)
#set(PART1_SOURCES
#  ${PART1_DIR}/src/vehicle.cpp
#  ${PART1_DIR}/src/drone.cpp
#  ${PART1_DIR}/src/autonomous_drone.cpp
#  ${PART1_DIR}/src/mission_drone.cpp
#)


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)

#add_executable(drone_node src/drone_node.cpp ${PART1_SOURCES})
add_executable(drone_node src/drone_node.cpp)
ament_target_dependencies(drone_node rclcpp std_msgs)

install(TARGETS
  drone_node
  DESTINATION lib/${PROJECT_NAME}
)

#add_executable(fleet_manager src/fleet_manager.cpp ${PART1_SOURCES})
add_executable(fleet_manager src/fleet_manager.cpp)
ament_target_dependencies(fleet_manager rclcpp std_msgs std_srvs)

install(TARGETS
  fleet_manager
  DESTINATION lib/${PROJECT_NAME}
)

#add_executable(health_monitor src/health_monitor.cpp ${PART1_SOURCES})
add_executable(health_monitor src/health_monitor.cpp)
ament_target_dependencies(health_monitor rclcpp std_msgs)

install(TARGETS
  health_monitor
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
