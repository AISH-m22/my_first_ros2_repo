FROM ros:kilted


#installing colcon & turtle

RUN apt-get update && apt-get install -y \
    python3-colcon-common-extensions \
    ros-kilted-turtlesim \
    && rm -rf /var/lib/apt/lists/*

#just same as cd bla bla

WORKDIR /onboarding2_ws

#copying my pkg into ws

COPY . src/my_circle_pkg



#source ros and build

RUN /bin/bash -c "source /opt/ros/kilted/setup.bash && colcon build"

#source workspace when container starts

CMD ["bash", "-c", "source /onboarding2_ws/install/setup.bash && bash"]


