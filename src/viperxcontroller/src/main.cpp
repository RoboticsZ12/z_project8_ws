#include "viperxcontroller/viperx_controller.hpp"
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <eigen3/Eigen/Dense> // Ensure this path is correct
#include <eigen3/Eigen/Geometry> // Ensure this path is correct

int main(int argc, char * argv[])
{
    // Initialize ROS and create the Node
    rclcpp::init(argc, argv);
    auto const node = std::make_shared<rclcpp::Node>(
        "hello_moveit",
        rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true)
    );

    // Create a ROS logger
    auto const logger = rclcpp::get_logger("hello_moveit");
    RCLCPP_INFO(logger, "Node initialized.");

    // Create the MoveIt MoveGroup Interface
    using moveit::planning_interface::MoveGroupInterface;
    MoveGroupInterface move_group_interface(node, "interbotix_arm");

    // Instantiate ViperXController
    ViperXController viperXcontroller;

    Eigen::Vector3d position(.1, .4, .23);
    Eigen::Quaterniond orientation(2.0, 5.5, 1.0, 1.0);
    orientation.normalize(); // Normalize the quaternion

    viperXcontroller.getPose(node, position, orientation);
    RCLCPP_INFO(logger, "Current pose retrieved and set.");

    rclcpp::spin(node);

    // Shutdown ROS
    rclcpp::shutdown();
    RCLCPP_INFO(logger, "Node shutdown.");
    return 0;
}
