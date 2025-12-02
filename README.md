# my_circle_pkg

## Overview

`my_circle_pkg` is a ROS2 Kilted package that publishes `geometry_msgs/Twist` messages to move a turtle in a circle in `turtlesim`.  
The project includes:

- `circle_node`: ROS2 publisher node.
- `Dockerfile`: Containerizes the ROS2 node.
- `run_docker.sh`: Bash script to build and run the Docker container.

---

## Requirements

- ROS2 Kilted installed
- Docker
- X11 for GUI (to run turtlesim)

---

## Presentation Steps

### 1. Native ROS2 Demo (without Docker)

1. Open a terminal.  
2. Source ROS2 Kilted:


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
ros2 run my_circle_pkg circle_node
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
# export LIBGL_ALWAYS_SOFTWARE=1 # no need
ros2 run turtlesim turtlesim_node
```
### Terminal 2

```bash
docker exec -it my_circle_container bash
source /opt/ros/kilted/setup.bash
source /onboarding2_ws/install/setup.bash
ros2 run my_circle_pkg circle_node
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