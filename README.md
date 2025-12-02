# my_circle_pkg

## Overview

my_circle_pkg is a ROS2 Kilted package that makes a turtle move in a circle in turtlesim. The node:

Publishes geometry_msgs/Twist messages to "turtle1/cmd_vel" at a fixed rate, using user-defined linear (velocity) and angular (angular_velocity) speeds.

Subscribes to "turtle1/cmd_vel" to print the velocity commands it sends, showing real-time feedback.

The node calculates the circle’s radius and circumference using:
```bash
radius = velocity / angular_velocity
circumference = 2 * pi * radius
```
It uses standard ROS2 message types, a timer for periodic publishing, and ROS2 parameters for dynamic input.

The project includes:

- `circle_node`: ROS2 publisher node.
- `Dockerfile`: Containerizes the ROS2 node.
- `run_docker.sh`: Bash script to build and run the Docker container.

---

## Requirements

- ROS2 Kilted installed
- Docker
- X11 GUI

---

## Presentation Steps

### ---------- without Docker------------

### Terminal 1

```bash
cd ~/onboarding2_ws
colcon build
source install/setup.bash
```
### Terminal 2
```bash
ros2 run turtlesim turtlesim_node
```
### Terminal 1
```bash
ros2 run my_circle_pkg circle_node --ros-args -p velocity:=5.5 -p angular_velocity:=2.0
```

### ---------- With Docker -----------#

### Terminal 1

```bash
cd ~/onboarding2_ws
chmod +x run_docker.sh
./run_docker.sh
```
### Terminal 1 inside the container

```bash
export LIBGL_ALWAYS_SOFTWARE=1
ros2 run turtlesim turtlesim_node
```
### Terminal 2

```bash
docker exec -it my_circle_container bash
source /opt/ros/kilted/setup.bash
source /onboarding2_ws/install/setup.bash
ros2 run my_circle_pkg circle_node --ros-args -p velocity:=5.5 -p angular_velocity:=2.0
```
### Project Structure
```bash
onboarding2_ws/
├── src/
│   └── my_circle_pkg/
│       ├── src/
│       │   └── circle_node.cpp
│       ├── CMakeLists.txt
│       └── package.xml
├── Dockerfile
├── run_docker.sh
└── README.md
```