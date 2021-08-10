// Copyright (C) Bey Hao Yun - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Bey Hao Yun <beyhy94@gmail.com>, August 2021

#include <memory>

// ROS2 LIB
#include "rclcpp/rclcpp.hpp"

// EPD_UTILS LIB
#include "ros_driver/ros_driver.hpp"

int main(int argc, char * argv[])
{
  setlinebuf(stdout);
  rclcpp::init(argc, argv);

  auto ros2_node = std::make_shared<ROSDriver>();

  rclcpp::spin(ros2_node);
  ros2_node->ensenso_ptr->closeDevice();
  rclcpp::shutdown();
  return 0;
}
