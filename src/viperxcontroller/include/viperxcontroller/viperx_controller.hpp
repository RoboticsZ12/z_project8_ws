#pragma once

#include <eigen3/Eigen/Geometry>
#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>

#include <vector>
#include <sstream>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <cmath> // part of rclcpp package
// #include <geometry_msgs/msg/Pose.hpp> // part of the rclcpp package

class ViperXController
{
public:
    // void getPose(const Eigen::Vector3d& position);
    // void getPose(const Eigen::Vector3d& position, const Eigen::Quaterniond& orientation);
    void getPose(std::shared_ptr<rclcpp::Node> node, const Eigen::Vector3d& position, const Eigen::Quaterniond& orientation);
};
