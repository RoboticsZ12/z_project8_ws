cmake_minimum_required(VERSION 3.8)
project(viperx)

# FIND THE NECESSARY PACKAGES
find_package(rclcpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(ament_cmake REQUIRED)
# find_package(rosidl_defautl_generators REQUIRED)

# EXECUTABLES
add_executable(viperctrl src/main.cpp src/viperx_controller.cpp)

# DEPENDENCIES
ament_target_dependencies(
    viperctrl 
    rclcpp 
    Eigen3 
    moveit_ros_planning_interface
)

#target_link_directories(viperctrl PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/lib
#)

target_include_directories(viperctrl PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# INSTALL
install(TARGETS
    viperctrl
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
