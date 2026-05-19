cmake_minimum_required(VERSION 3.8)
project(gripper_controller)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(gripper src/gripper.cpp)
ament_target_dependencies(gripper rclcpp std_msgs)
install(TARGETS gripper DESTINATION lib/${PROJECT_NAME})

ament_package()