#include "rclcpp/rclcpp.h"
#include <cmath>
#include "robot_traj/msg/target.h" 
#include <tf/transform_datatypes.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>



using namespace std::chrono_literals;

class InterpolatorNode : public rclcpp::Node
{
public:
  InterpolatorNode() : Node("draw_traj")

  {
    // Create the subscriber to receive the input message
    subscriber_ = this->create_subscription<robot_traj::msg::target>("target_pose", rclcpp::SensorDataQoS(), std::bind(&InterpolatorNode::messageCallback, this, std::placeholders::_1));

    // Create the publisher to send the interpolated path
    publisher_ = this->create_publisher<nav_msgs::msg::Odometry>("command", 10);
  }

private:
  void messageCallback(const robot_traj::msg::target::SharedPtr msg)
  {
    // Store the target pose and orientation angle from the input message
    target_x = msg->target_pose->x;
    target_y = msg->target_pose->y;
    target_orientation_ = msg->target_orientation;

    // Compute the distance and angle to the target pose
    double distance = std::sqrt(target_x * target_x + target_y * target_y);
    double angle = std::atan2(target_y, target_x);

    // Publish the interpolated path
    publishInterpolatedPath(distance, angle);

    // Rotate to the target orientation
    rotateToTargetOrientation(target_orientation);
  }

  void publishInterpolatedPath(double distance, double angle)
  {
    // Compute the number of steps for interpolation
    int num_steps = static_cast<int>(std::ceil(distance / step_size_));

    // Compute the step values
    double dx = distance * std::cos(angle) / num_steps;
    double dy = distance * std::sin(angle) / num_steps;

    // Create the interpolated path message
    nav_msgs::msg::Odometry path_msg;
    // Set the header fields
    path_msg.header.frame_id = "path";
    path_msg.header.stamp = node->get_clock()->now();
    path_msg.pose.pose.position.x = 0.0;
    path_msg.pose.pose.position.y = 0.0;
    path_msg.pose.pose.position.z = 0.0;

    // Publish the interpolated path in steps
    for (int i = 0; i <= num_steps; ++i) {
      path_msg.pose.pose.position.x += dx;
      path_msg.pose.pose.position.y += dy;
      publisher_->publish(path_msg);
      rclcpp::sleep_for(step_duration_);
    }
  }

  void rotateToTargetOrientation(float32 target_orientation)
  {
    // Convert target orientation to quaternion
    tf2::Quaternion quaternion;
    quaternion.setRPY(0, 0, target_orientation);
    // Print the quaternion representation
    //RCLCPP_INFO(this->get_logger(), "Quaternion (x, y, z, w): (%f, %f, %f, %f)", quaternion.x(), quaternion.y(), quaternion.z(), quaternion.w());
    // Create the rotated pose message
    nav_msgs::msg::Odometry rotated_pose_msg;
    rotated_pose_msg.header.frame_id = "orientation";
    rotated_pose_msg.header.stamp = node->get_clock()->now();
    rotated_pose_msg.pose.pose.orientation.x = quaternion.x;
    rotated_pose_msg.pose.pose.orientation.y = quaternion.y;
    rotated_pose_msg.pose.pose.orientation.z = quaternion.z;
    rotated_pose_msg.pose.pose.orientation.w = quaternion.w;

    // Publish the rotated pose
    publisher_->publish(rotated_pose_msg);
  }


  private:
  rclcpp::Subscription<obot_traj::msg::target>::SharedPtr subscriber_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr publisher_;
  const double step_size_ = 0.1; // Interpolation step size (adjust as needed)
  const std::chrono::milliseconds step_duration_ = 100ms; // Interpolation step duration (adjust as needed)
};


int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<InterpolatorNode>());
  rclcpp::shutdown();
  return 0;
}