#include "rclcpp/rclcpp.h"
#include <cmath>
#include "robot_traj/msg/target.h" 
#include <nav_msgs/Odometry.h>
#include <std_msgs/Float64.h>
#include "geometry_msgs/msg/twist.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"


class InterpolatorNode : public rclcpp::Node
{
public:
  InterpolatorNode() : Node("draw_traj")

  {
    // Create the subscriber to receive the input message
    subscriber1 = this->create_subscription<robot_traj::msg::target>("target_pose", rclcpp::SensorDataQoS(), std::bind(&InterpolatorNode::messageCallback, this, std::placeholders::_1));
    // Subscriber to get to receive odometry information
    subscriber2 = node->create_subscription<nav_msgs::msg::Odometry>("/odom", 10, odomCallback);

    // Create a publisher for the cmd_vel topic
    publisher = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 1);
  }

private:
  void odomCallback(const nav_msgs::msg::Odometry::SharedPtr msg)
  {
    // Retrieve position
    double current_x = msg->pose.pose.position.x;
    double current_y = msg->pose.pose.position.y;
    double current_z = msg->pose.pose.position.z;

    // Retrieve orientation
    double qx = msg->pose.pose.orientation.x;
    double qy = msg->pose.pose.orientation.y;
    double qz = msg->pose.pose.orientation.z;
    double qw = msg->pose.pose.orientation.w;

    tf2::Quaternion quaternion(qx, qy, qz, qw);
    tf2::Matrix3x3 matrix(quaternion);

    double roll, pitch, yaw;
    matrix.getRPY(roll, pitch, yaw);

    // Print the position and orientation
    RCLCPP_INFO(rclcpp::get_logger("odom_listener"), "Position: (%f, %f, %f)", x, y, z);
  }

  void messageCallback(const robot_traj::msg::target::SharedPtr msg)
  {
    // Store the target pose and orientation angle from the input message
    double target_x = msg->target_pose->x;
    double target_y = msg->target_pose->y;
    double target_orientation = msg->target_orientation;

    double dx = target_x - current_x;
    double dy = target_y - current_y;

    // Compute the distance and angle to the target pose
    double distance = std::sqrt(dx * dx + dy * dy);
    double angle = target_orientation - yaw;

    if(distance >= 0.01){
      publishLinearVelocites(true);
    }else{
      publishLinearVelocites(false);
    }

    if(angle >= 0.01){
      publishAngularVelocites(true);
    }else{
      publishAngularVelocites(false);
    }
  }

  void publishLinearVelocites(bool check)
  {
    // Create a Twist message and populate it with the desired values
    twist_msg = std::make_shared<geometry_msgs::msg::Twist>();
    
    if(check == true){
      //Calculate the linear velocities
      float64 vx = linear_vel;
      float64 vy = linear_vel;
      float64 vz = 0.0f;
      
      twist_msg->linear.x = vx;  // Set the linear velocity along the x-axis
      twist_msg->linear.y = vy;  // Set the linear velocity along the y-axis
      twist_msg->linear.z = vz;  // Set the linear velocity along the z-axis  
    }else{
      twist_msg->linear.x = 0.0f;  // Set the linear velocity along the x-axis
      twist_msg->linear.y = 0.0f;  // Set the linear velocity along the y-axis
      twist_msg->linear.z = 0.0f;  // Set the linear velocity along the z-axis
    }  

    twist_msg->angular.x = 0.0f; // Set the angular velocity around the x-axis
    twist_msg->angular.y = 0.0f; // Set the angular velocity around the y-axis
    twist_msg->angular.z = 0.0f; // Set the angular velocity around the z-axis

    // Publish the Twist message repeatedly
    publisher->publish(twist_msg);
  }

  void publishAngularVelocites(bool check)
  {
    // Create a Twist message and populate it with the desired values
    rotated_twist_msg = std::make_shared<geometry_msgs::msg::Twist>();
    rotated_twist_msg->linear.x = 0.0f;  // Set the linear velocity along the x-axis
    rotated_twist_msg->linear.y = 0.0f;  // Set the linear velocity along the y-axis
    rotated_twist_msg->linear.z = 0.0f;  // Set the linear velocity along the z-axis

    if(check == true){
      //Calculate the angular velocities
      float64 wx = 0.0f;
      float64 wy = 0.0f;
      float64 wz = angular_vel;

      rotated_twist_msg->angular.x = wx; // Set the angular velocity around the x-axis
      rotated_twist_msg->angular.y = wy; // Set the angular velocity around the y-axis
      rotated_twist_msg->angular.z = wz; // Set the angular velocity around the z-axis
    }else{
      rotated_twist_msg->angular.x = 0.0f; // Set the angular velocity around the x-axis
      rotated_twist_msg->angular.y = 0.0f; // Set the angular velocity around the y-axis
      rotated_twist_msg->angular.z = 0.0f; // Set the angular velocity around the z-axis
    }

    // Publish the Twist message repeatedly
    publisher->publish(twist_msg);
  }

  private:
  rclcpp::Subscription<obot_traj::msg::target>::SharedPtr subscriber1;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscriber2;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;
  const double step_size_ = 0.1; // Interpolation step size (adjust as needed)
  const float64 linear_vel = 1;
  const float64 angular_vel = 1;
};


int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<InterpolatorNode>());
  rclcpp::shutdown();
  return 0;
}