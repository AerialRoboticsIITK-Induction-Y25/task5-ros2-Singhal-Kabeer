# Require a relatively modern CMake version
cmake_minimum_required(VERSION 3.20)

# Define the project name
project(DroneFleet)

# Enforce C++17 (required for clean std::tuple usage)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Point the compiler to your header files
include_directories(include)

# Automatically find all .cpp files in the src/ directory
file(GLOB SOURCES "src/*.cpp")

# Generate the final executable named 'drone_sim'
add_executable(drone_sim ${SOURCES})