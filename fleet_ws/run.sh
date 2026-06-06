#!/bin/bash

docker build -t drone_fleet_image .

docker run -it --rm -v "$(pwd)/src:/fleet_ws/src" drone_fleet_image