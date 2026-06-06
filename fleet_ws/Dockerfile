FROM ros:jazzy

WORKDIR /fleet_ws

COPY src/ ./src/

RUN /bin/bash -c "source /opt/ros/jazzy/setup.bash && colcon build"

CMD ["/bin/bash", "-c", "source /opt/ros/jazzy/setup.bash && source /fleet_ws/install/setup.bash && ros2 launch drone_fleet fleet.launch.py"]