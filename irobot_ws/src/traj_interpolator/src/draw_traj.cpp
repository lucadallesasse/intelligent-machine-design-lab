#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include <iostream>
#include <vector>
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
#define MAX_ANG_VEL 0.3
#define MAX_LIN_ACC 0.1
#define MAX_ANG_ACC 0.1
#define FREQUENCY 15.0

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

    times = 15;

    // Initialize the flag indicating if the target pose has been reached 
    target_reached_ = false; 
  }

private:

  // Function to generate a trapezoidal velocity profile
  std::vector<double> generateTrapezoidalProfile(double distance, double maxVelocity, double acceleration, double frequency)
  {
    // Calculate the time required to reach the target velocity during acceleration and deceleration phases (we assumed equal acceleration and deceleration)
    double accelerationTime = maxVelocity / acceleration;

    double accelerationDistance = 0.5 * acceleration * accelerationTime * accelerationTime;

    // Calculate the remaining distance at constant speed
    double remaining_distance = distance - 2*accelerationDistance;

    double constantVelocityTime = 0.0;

    // Calculate the distance covered during the acceleration and deceleration phases
    if(remaining_distance > 0){
  
      // Calculate the time required for the constant velocity phase
      constantVelocityTime = remaining_distance / maxVelocity;

    }else{

      accelerationTime = sqrt(distance/acceleration);
    }

  
    // Calculate the number of points needed in the trajectory
    int numPoints = static_cast<int>(std::ceil(totalTime * frequency));

    // Calculate the time increment between points
    double dt = 1.0 / frequency;

    // Create a vector to store the velocities
    std::vector<double> velocities;

    // Generate the trapezoidal velocity profile
    for (int i = 0; i < numPoints; ++i) {
        double t = i * dt;  // Time

        // Calculate the velocity at time t based on the trapezoidal profile
        double velocity = 0.0;

        if (t <= accelerationTime) {
            velocity = acceleration * t;  // Acceleration phase
        } else if (t <= accelerationTime + constantVelocityTime) {
            velocity = maxVelocity;  // Constant velocity phase
        } else if (t <= totalTime) {
            double decelerationTimeOffset = t - (totalTime - decelerationTime);
            velocity = maxVelocity - acceleration * decelerationTimeOffset;  // Deceleration phase
        }

        velocities.push_back(velocity);
    }

    return velocities;
}

  std::vector<double> generateVelocities(double max_velocity, double trajectory_duration, double sample_frequency){

    // Define the time vector for the trajectory
    double dt = 1.0 / sample_frequency;
    std::vector<double> time_vec;

    for (double t = 0.0; t <= trajectory_duration; t += dt) {
        time_vec.push_back(t);
    }

    // Define the trajectory points
    double start_value = 0.0;
    double end_value = max_velocity;
    std::vector<double> trajectory_points(time_vec.size());
    std::fill(trajectory_points.begin(), trajectory_points.end(), end_value);
    trajectory_points.front() = start_value;

    // Generate spline interpolator
    gtsam::Spline2 spline = gtsam::Spline2::Approximate(
        time_vec, trajectory_points, max_velocity, 0.0, 0.0);

    // Compute velocities at each time step
    std::vector<double> velocities;
    for (double t : time_vec) {
        velocities.push_back(spline.velocity(t));
    }

    return velocities;
}

  void targetPoseCallback(const custom_msg::msg::Target::SharedPtr msg) 
  { 
    target_reached_ = false;

    if (!target_reached_) 
    { 
      double target_x = msg->target_pose.x; 
      double target_y = msg->target_pose.y; 
      double target_theta = (msg->target_orientation)/180.0*M_PI; 

      double distance = std::hypot(target_x - current_pose_.x, target_y - current_pose_.y); 
      double duration_trans = abs(distance / linear_velocity_); 
      double rotation = atan2(target_y - current_pose_.y, target_x - current_pose_.x);
      double duration_rot = abs(rotation / angular_velocity_); 

      //Generate the velocities (linear and angular) according to the spline interpolation
      std::vector<double> velocities = generateVelocities(max_velocity, trajectory_duration, FREQUENCY);

      // Turn the robot in the direction of the target point
      if(rotation != 0.0){ 
        turn(rotation,duration_rot); 
      }
      
      // Move in a straight line to the target pose 
      if((target_x != 0.0) | (target_y != 0.0)){
        moveStraight(distance, duration_trans); 
      }

      // Turn to the desired orientation 
      double rotation_final = target_theta - rotation;
      double duration_rot2 = abs(rotation_final / angular_velocity_); 

      RCLCPP_INFO(this->get_logger(), "Distanza %f , rotation initial %f, rotation final %f", distance, rotation, rotation_final);
      if(rotation_final != 0.0){
        turn(rotation_final,duration_rot2); 
      }

      // Set the target reached flag to true 
      target_reached_ = true; 
    } 
  } 
  

  void moveStraight(double distance, double duration) 
  { 
    double linear_vel_x = distance / duration; 

    std::string message = "Duration trans: " + std::to_string(duration);
    RCLCPP_INFO(this->get_logger(), message.c_str());

    // Publish the linear velocity commands
    auto twist_msg = std::make_unique<geometry_msgs::msg::Twist>(); 
    twist_msg->linear.x = linear_vel_x; 
    
    double elapsed_total_time = -times/FREQUENCY; 

    while (elapsed_total_time <= duration + times/FREQUENCY) 
    { 
      auto start = std::chrono::high_resolution_clock::now();
      publisher->publish(*twist_msg); 
      auto end = std::chrono::high_resolution_clock::now();
      
      std::chrono::duration<double> elapsed_time = end - start;

      // Calculate the remaining time to sleep to achieve the desired frequency
      std::chrono::duration<double> sleep_duration = std::chrono::duration<double>(1/FREQUENCY) - elapsed_time;
      std::this_thread::sleep_for(sleep_duration);
      elapsed_total_time += 1/FREQUENCY;
      std::string message = "Elapsed time: " + std::to_string(elapsed_total_time);
      RCLCPP_INFO(this->get_logger(), message.c_str()); 
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

    double elapsed_total_time = -times/FREQUENCY; 

    while (elapsed_total_time <= duration + times/FREQUENCY) 
    { 
      auto start = std::chrono::high_resolution_clock::now();
      publisher->publish(*twist_msg); 
      auto end = std::chrono::high_resolution_clock::now();
      
      std::chrono::duration<double> elapsed_time = end - start;

      // Calculate the remaining time to sleep to achieve the desired frequency
      std::chrono::duration<double> sleep_duration = std::chrono::duration<double>(1/FREQUENCY) - elapsed_time;
      std::this_thread::sleep_for(sleep_duration);
      elapsed_total_time += 1/FREQUENCY;
      std::string message = "Elapsed time: " + std::to_string(elapsed_total_time);
      RCLCPP_INFO(this->get_logger(), message.c_str());
    }   

    std::string message = "Duration rot: " + std::to_string(duration);
    RCLCPP_INFO(this->get_logger(), message.c_str());

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
  int times;

};


int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  // Create a Rate object with the desired loop rate (e.g., 10 Hz)
  rclcpp::Rate loop_rate(FREQUENCY); // 10 Hz
  
  while (rclcpp::ok())
  {
    // Process any pending messages or callbacks
    rclcpp::spin(std::make_shared<InterpolatorNode>());
    
    // Sleep to maintain the desired loop rate
    loop_rate.sleep();
  }  
  rclcpp::shutdown();
  return 0;
}