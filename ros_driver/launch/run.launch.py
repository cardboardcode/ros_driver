# Copyright (C) Bey Hao Yun - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# Written by Bey Hao Yun <beyhy94@gmail.com>, August 2021

from launch import LaunchDescription
import launch_ros.actions


def generate_launch_description():
    return LaunchDescription([
        launch_ros.actions.Node(
            package='ros_driver',
            node_executable='main',
            output='screen',
            remappings=[('/ros_driver_node/pcl_input', '/camera/pointcloud')]
            ),
    ])
