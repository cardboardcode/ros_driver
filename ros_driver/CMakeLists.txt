cmake_minimum_required(VERSION 3.5)
project(ros_driver)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(PCL REQUIRED PATHS /dep/pcl-pcl-1.8.1/local/)
find_package(pcl_conversions REQUIRED)

add_definitions(${PCL_DEFINITIONS})

set(PCL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/deps/pcl/local/include/pcl-1.8;/usr/include/eigen3;/usr/include;/usr/include/ni;/usr/include/openni2;/opt/ensenso/development/c/include;/usr/include/vtk-6.3;/usr/include/freetype2;/usr/lib/x86_64-linux-gnu/openmpi/include/openmpi;/usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/opal/mca/event/libevent2022/libevent;/usr/lib/x86_64-linux-gnu/openmpi/include/openmpi/opal/mca/event/libevent2022/libevent/include;/usr/lib/x86_64-linux-gnu/openmpi/include;/usr/include/python2.7;/usr/include/x86_64-linux-gnu;/usr/include/hdf5/openmpi;/usr/include/libxml2;/usr/include/jsoncpp;/usr/include/tcl")

include_directories(
  include
  ${PCL_INCLUDE_DIRS}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(main src/ros_driver.cpp src/ensenso_grabber.cpp)
ament_target_dependencies(main rclcpp sensor_msgs pcl_conversions)
target_link_libraries(main ${PCL_LIBRARIES})

install(TARGETS
  main
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
