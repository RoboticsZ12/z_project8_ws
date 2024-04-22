#include "viperxcontroller/viperx_controller.hpp"

void ViperXController::getPose(std::shared_ptr<rclcpp::Node> node, const Eigen::Vector3d& position, const Eigen::Quaterniond& orientation)
{    
    auto const logger = rclcpp::get_logger("hello_moveit");

    // Create the MoveIt MoveGroup Interface
    using moveit::planning_interface::MoveGroupInterface;
    auto move_group_interface = MoveGroupInterface(node, "interbotix_arm");

    // Generate a vector of target poses
    std::vector<geometry_msgs::msg::Pose> target_poses = [&]{
        std::vector<geometry_msgs::msg::Pose> poses;
        geometry_msgs::msg::Pose pose;
        double position_increment = 0.03;
        const double angle_increment = M_PI / 18; // 10 degree increment

        for(int i = 0; i < 5; i++)
        {
            pose.position.x = 0.28 + position_increment * i;
            pose.position.y = -0.05 + position_increment * i;
            pose.position.z = 0.25 + position_increment * i;

            double current_angle = 90 * M_PI / 180 + angle_increment * i; // Simplify conversion and use
            double axis = sqrt(1.0 / 3.0); // Common axis computation for all

            pose.orientation.w = cos(current_angle / 2);
            pose.orientation.x = axis * sin(current_angle / 2);
            pose.orientation.y = axis * sin(current_angle / 2);
            pose.orientation.z = axis * sin(current_angle / 2);

            poses.push_back(pose);
        }

    // FLIP THE DIRECTION POSE
    if(int i = 5)
    {
        for(int i = 5; i > 0; i--)
        {
            pose.position.x = 0.28 + position_increment * i;
            pose.position.y = -0.05 + position_increment * i;
            pose.position.z = 0.25 + position_increment * i;

            double current_angle = 90 * M_PI / 180 + angle_increment * i; // Simplify conversion and use
            double axis = sqrt(1.0 / 3.0); // Common axis computation for all

            pose.orientation.w = cos(current_angle / 2);
            pose.orientation.x = axis * sin(current_angle / 2);
            pose.orientation.y = axis * sin(current_angle / 2);
            pose.orientation.z = axis * sin(current_angle / 2);

            poses.push_back(pose);
        }
    }
        return poses;
    }();

    // Set and execute each target pose
    for (const auto& target_pose : target_poses) {
        move_group_interface.setPoseTarget(target_pose);

        moveit::planning_interface::MoveGroupInterface::Plan plan;
        bool success = static_cast<bool>(move_group_interface.plan(plan));
        if (success) {
            move_group_interface.execute(plan);
        } else {
            RCLCPP_ERROR(logger, "Planning failed!");
        }
    }
}
