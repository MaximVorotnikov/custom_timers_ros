cmake_minimum_required(VERSION 3.8)
project(custom_timers_ros)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(ament_cmake REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(rclcpp REQUIRED)

set(deps ament_cmake sensor_msgs nav_msgs geometry_msgs visualization_msgs rclcpp)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

set(lib_sources include/custom_timers_ros/ros_timers.hpp src/ros_timers.cpp)
## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)
add_library(custom_timers_ros_lib ${lib_sources})
ament_target_dependencies(custom_timers_ros_lib geometry_msgs nav_msgs sensor_msgs visualization_msgs rclcpp) # Добавление зависимостей
############################################################
include_directories(include)

ament_export_targets(custom_timers_ros_lib HAS_LIBRARY_TARGET)

install(
    DIRECTORY include/${PROJECT_NAME}
    DESTINATION include
)

install(
    TARGETS custom_timers_ros_lib
    EXPORT custom_timers_ros_lib
    LIBRARY DESTINATION ${COLCON_GLOBAL_LIB_DESTINATION}
    ARCHIVE DESTINATION ${COLCON_GLOBAL_LIB_DESTINATION}
    RUNTIME DESTINATION  ${COLCON_GLOBAL_BIN_DESTINATION}
    INCLUDES DESTINATION include
)

ament_package()

