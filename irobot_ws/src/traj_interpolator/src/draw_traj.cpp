#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include "custom_msg/msg/target.hpp" 
#include <nav_msgs/msg/odometry.hpp>
#include <std_msgs/msg/float64.hpp>
#include "geometry_msgs/msg/twist.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "geometry_msgs/msg/pose2_d.hpp"
#include <unistd.h>
#include <chrono>


#define MAX_LIN_VEL 0.2
#define MAX_ANG_VEL 0.8

class InterpolatorNode : public rclcpp::Node
{
public:
  InterpolatorNode() : Node("draw_traj")  

  {
    // Create the subscriber to receive the input message
    subscriber = this->create_subscription<custom_msg::msg::Target>("/target_pose", rclcpp::SensorDataQoS(), std::bind(&InterpolatorNode::targetPoseCallback, this, std::placeholders::_1));

    // Create a publisher for the cmd_vel topic
    publisher = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 1);

    // Initialize robot's current pose and orientation 
    current_pose_.x = 0.0; 
    current_pose_.y = 0.0; 
    current_pose_.theta = 0.0; 

    // Set the desired symbol drawing speed 
    linear_velocity_ = MAX_LIN_VEL;   // Adjust the linear velocity as per your requirements 
    angular_velocity_ = MAX_ANG_VEL;  // Adjust the angular velocity as per your requirements 

    // Initialize the flag indicating if the target pose has been reached 
    target_reached_ = false; 
  }

private:

  void targetPoseCallback(const custom_msg::msg::Target::SharedPtr msg) 
  { 
    target_reached_ = false;

    if (!target_reached_) 
    { 
      // Calculate the interpolation path 
      double target_x = msg->target_pose.x; 
      double target_y = msg->target_pose.y; 
      double target_theta = (msg->target_orientation)/180*M_PI; 

      double distance = std::hypot(target_x - current_pose_.x, target_y - current_pose_.y); 
      double duration_trans = abs(distance / linear_velocity_); 
      double rotation = atan2(target_y - current_pose_.y, target_x - current_pose_.x);
      double duration_rot = abs(rotation / angular_velocity_); 

      // Turn the robot in the direction of the target point
      if((target_x != 0.0) | (target_y != 0.0)){ 
        turn(rotation,duration_rot); 
      }
      
      // Move in a straight line to the target pose 
      if((target_x != 0.0) | (target_y != 0.0)){
        moveStraight(distance, duration_trans); 
      }

      // Turn to the desired orientation 
      double rotation_final = target_theta - rotation;
      double duration_rot2 = abs(rotation_final / angular_velocity_); 
      turn(rotation_final,duration_rot2); 

      // Set the target reached flag to true 
      target_reached_ = true; 
    } 
  } 
  

  void moveStraight(double distance, double duration) 
  { 
    double linear_vel_x = distance / duration; 

    // Publish the linear velocity commands
    auto twist_msg = std::make_unique<geometry_msgs::msg::Twist>(); 
    twist_msg->linear.x = linear_vel_x; 
    
    double elapsed_time = 0.0; 

    while (elapsed_time <= duration*std::pow(10, 6)) 
    { 
      auto start = std::chrono::high_resolution_clock::now();
      publisher->publish(*twist_msg); 
      usleep(200);
      auto end = std::chrono::high_resolution_clock::now();
      
      std::chrono::duration<double, std::micro> duration = end - start;
      elapsed_time += duration.count(); 
    } 

    // Stop the robot after reaching the target pose 
    twist_msg->linear.x = 0.0; 
    publisher->publish(*twist_msg); 
  } 

  void turn(double target_theta, double duration) 
  { 
    double angular_vel_z = target_theta / duration; 
  
    // Publish the angular velocity commands until the desired orientation is reached 
    auto twist_msg = std::make_unique<geometry_msgs::msg::Twist>(); 
    twist_msg->angular.z = angular_vel_z; 

    double elapsed_time = 0.0; 

    while (elapsed_time <= duration*std::pow(10, 6)) 
    { 
      auto start = std::chrono::high_resolution_clock::now();
      publisher->publish(*twist_msg); 
      usleep(200);
      auto end = std::chrono::high_resolution_clock::now();
      
      std::chrono::duration<double, std::micro> duration = end - start;
      elapsed_time += duration.count();
    } 

    // Stop the robot after reaching the desired orientation 
    twist_msg->angular.z = 0.0; 
    publisher->publish(*twist_msg); 
  
  } 

  private:
  rclcpp::Subscription<custom_msg::msg::Target>::SharedPtr subscriber;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher;

  bool target_reached_; 
  geometry_msgs::msg::Pose2D current_pose_; 
  double linear_velocity_; 
  double angular_velocity_; 

};


int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<InterpolatorNode>());
  rclcpp::shutdown();
  return 0;
}


  


 