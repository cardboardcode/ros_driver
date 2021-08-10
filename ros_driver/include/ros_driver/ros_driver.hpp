// Copyright (C) Bey Hao Yun - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Bey Hao Yun <beyhy94@gmail.com>, August 2021

#ifndef ROS2_CPP_PCL_NODE_HPP_
#define ROS2_CPP_PCL_NODE_HPP_

#include <chrono>
#include <thread>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/point_cloud2.hpp"
#include "pcl_conversions/pcl_conversions.h"

#include "pcl/point_types.h"
#include <pcl/io/ensenso_grabber.h>

using namespace std::chrono_literals;

class ROSDriver : public rclcpp::Node
{
public:
  /*! \brief A Constructor function*/
  ROSDriver(void);

  /*! \brief A EnsensoGrabber that connects to the N35 hardware.*/
  pcl::EnsensoGrabber::Ptr ensenso_ptr;

private:
  /*! \brief A subscriber member variable to receive 3D PointCloud2.*/
  mutable rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pcl_sub;
  /*! \brief A publisher member variable to output processed 3D PointCloud2*/
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pcl_pub;

  // Non-ROS subscriber function for get pointcloud data from Ensenso N35.
  void grabberCallback(const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud);

};

ROSDriver::ROSDriver(void)
: Node("ros_driver_node")
{
  // Connect to Ensenso Camera at port 0.
  ensenso_ptr.reset(new pcl::EnsensoGrabber);
  ensenso_ptr->openTcpPort();
  ensenso_ptr->openDevice();

  // Start Camera using grabberCallback function.
  boost::function<void(const pcl::PointCloud<pcl::PointXYZ>::Ptr&)> f = boost::bind(&ROSDriver::grabberCallback, this, _1);
  ensenso_ptr->registerCallback(f);
  ensenso_ptr->start();

  // Creating publisher
  pcl_pub = this->create_publisher<sensor_msgs::msg::PointCloud2>(
    "/ros_driver_node/pcl_output",
    10);

}

/** @brief Process and/or display Ensenso grabber clouds
 * @param[in] cloud Ensenso cloud */
void ROSDriver::grabberCallback (const pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud)
{
  sensor_msgs::msg::PointCloud2 output_pcl;
  pcl::toROSMsg(*cloud, output_pcl);
  output_pcl.header.frame_id = "ensenso_optical_frame";
  pcl_pub->publish(output_pcl);
}

#endif  // ROS2_CPP_BASE_NODE_HPP_
