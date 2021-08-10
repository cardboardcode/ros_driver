#!/usr/bin/env bash

# Copyright (C) Bey Hao Yun - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Bey Hao Yun <beyhy94@gmail.com>, August 2021

# Function: Source all required setup.bash and build the ROS2 package.
# Static Analysis: shellcheck build_local.bash -x -e SC1091


function select_ros2_distro(){
  # List out all ROS2 distros installed on current workstation.
  ros_distro_array=(/opt/ros/*/)
  ros2_distro_library=("eloquent" "foxy" "galactic")
  arrVar=()
  for dir in "${ros_distro_array[@]}";
  do
    for distro in "${ros2_distro_library[@]}";
    do
      if [ "$distro" == "$(basename "$dir")" ]; then
        arrVar+=("$(basename "$dir")");
      fi
    done
  done
  unset ros_distro_array ros2_distro_library

  # echo "${#arrVar[@]}" # Check length of number of ROS2 distro found.
  # If zero ROS2 distro are detected, report warning and exit with status code 1.
  if [ "${#arrVar[@]}" == 0 ]; then
    echo "No ROS2 installation detected. Please install at least one."
    exit 1
  fi

  # Gets user input and selects user-designated ROS2 distro.
  echo "Which ROS2 distro would you like to use?"
  select dir in "${arrVar[@]}";
  do
    # Returns ROS2 distro version name in a variable.
    ROS2_DISTRO=${dir}
    break;
  done

  unset arrVar dir

  echo "You selected ${ROS2_DISTRO}"'!';
}

select_ros2_distro

# Build ROS2 package.
if [ -d  "build/" ]; then
  sudo rm -rf build/
fi
if [ -d  "install/" ]; then
  sudo rm -rf install/
fi
if [ -d  "log/" ]; then
  sudo rm -rf log/
fi
echo "Building and Sourcing ROS2 package..."
source "/opt/ros/${ROS2_DISTRO}/setup.bash"
colcon build && source install/setup.bash
# TODO (cardboardcode): Put in safeguard against failed colcon build.

unset ROS2_DISTRO
