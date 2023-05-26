#include "rclcpp/rclcpp.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include "custom_msg/msg/target.hpp" 
#include <nav_msgs/msg/odometry.hpp>
#include "geometry_msgs/msg/twist.hpp"
#include "geometry_msgs/msg/pose2_d.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include <unistd.h>
#include <chrono>


#define MAX_LIN_VEL 0.1
#define MAX_ANG_VEL 0.1
#define MAX_LIN_ACC 0.05
#define MAX_ANG_ACC 0.05
#define FREQUENCY 10.0

class InterpolatorNode : public rclcpp::Node
{
public:
  InterpolatorNode() : Node("draw_traj")  

  {
    // Create the subscriber to receive the input message
    subscriber = this->create_subscription<custom_msg::msg::Target>("/target_pose", rclcpp::SensorDataQoS(), std::bind(&InterpolatorNode::targetPoseCallback, this, std::placeholders::_1));

    // Create the subscriber to receive the odometry message
    m_odom_subscription = this->create_subscription<nav_msgs::msg::Odometry>("odom",rclcpp::SensorDataQoS(),std::bind(&InterpolatorNode::odom_callback, this, std::placeholders::_1));

    // Create a publisher for the cmd_vel topic
    publisher = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    // Initialize robot's current pose and orientation 
    reached_pose_.x = 0.0; 
    reached_pose_.y = 0.0; 
    reached_pose_.theta = 0.0; 

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

  geometry_msgs::msg::Pose2D odom_callback(const nav_msgs::msg::Odometry::ConstSharedPtr msg){

    current_pose_.x = msg->pose.pose.position.x - reached_pose_.x; 
    current_pose_.y = msg->pose.pose.position.y - reached_pose_.y; 

    // Extract the yaw angle from the quaternion
    double roll, pitch, yaw;
    tf2::Quaternion tf_quaternion(msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
    tf2::Matrix3x3(tf_quaternion).getRPY(roll, pitch, yaw);

    current_pose_.theta = yaw - reached_pose_.theta;

    RCLCPP_INFO(this->get_logger(), "Current_x %f , Current_y  %f, Current_theta %f", current_pose_.x, current_pose_.y, current_pose_.theta);

    return current_pose_;
  }

  // Function to generate a trapezoidal velocity profile
  std::vector<double> generateVelocityProfile(double distance, double maxVelocity, double acceleration, double frequency){
    // Calculate the time required to reach the target velocity during acceleration and deceleration phases (we assumed equal acceleration and deceleration)
    double max_accelerationTime = maxVelocity / acceleration;

    double accelerationDistance = 0.5 * acceleration * max_accelerationTime * max_accelerationTime;

    // Calculate the remaining distance at constant speed
    double remaining_distance = distance - 2*accelerationDistance;

    double constantVelocityTime = 0.0;
    double totalTime = 0.0;
    double accelerationTime = 0.0;

    // Calculate the distance covered during the acceleration and deceleration phases
    if(remaining_distance > 0){
  
      // Calculate the time required for the constant velocity phase
      constantVelocityTime = remaining_distance / maxVelocity;
      accelerationTime = max_accelerationTime;
      
    }else{
      constantVelocityTime = 0.0;
      accelerationTime = sqrt(distance/acceleration);

    }

    totalTime = 2*accelerationTime + constantVelocityTime;

    // Calculate the number of points needed in the trajectory
    int numPoints = static_cast<int>(std::ceil(totalTime * frequency));

    //RCLCPP_INFO(this->get_logger(), "totalTime %f , numPoints %i", totalTime, numPoints);

    // Calculate the time increment between points
    double dt = 1.0 / frequency;
    RCLCPP_INFO(this->get_logger(), "dt %f", dt);

    // Create a vector to store the velocities
    std::vector<double> velocities;
    velocities.resize(numPoints);

    // Generate the trapezoidal velocity profile
    for (int i = 0; i < numPoints; ++i) {
        double t = i * dt;  // Time

        // Calculate the velocity at time t based on the trapezoidal profile
        double velocity = 0.0;

        if (t <= accelerationTime) {
            velocity = acceleration * t;  // Acceleration phase
        } else if (t > accelerationTime && (t <= accelerationTime + constantVelocityTime)) {
            velocity = maxVelocity;  // Constant velocity phase
        } else {
            double decelerationTimeOffset = t - (totalTime - accelerationTime);
            velocity = maxVelocity - acceleration * decelerationTimeOffset;  // Deceleration phase
        }

        velocities[i] = velocity;
    }
    RCLCPP_INFO(this->get_logger(), "Size of velocities %ld", velocities.size());
    return velocities;
  }

  geometry_msgs::msg::Pose2D targetPoseCallback(const custom_msg::msg::Target::SharedPtr msg) 
  { 
    target_reached_ = false;

    if (!target_reached_) 
    { 
      double target_x = msg->target_pose.x; 
      double target_y = msg->target_pose.y; 
      double target_theta = (msg->target_orientation)/180.0*M_PI; 

      double distance = std::hypot(target_x, target_y);  
      double rotation = atan2(target_y, target_x);

      //Generate the velocities (linear and angular)
      // Turn the robot in the direction of the target point
      if(rotation != 0.0){ 
        turn(rotation); 
      }
      
      // Move in a straight line to the target pose 
      if((target_x != 0.0) | (target_y != 0.0)){
        moveStraight(distance); 
      }

      // Turn to the desired orientation 
      double rotation_final = target_theta - rotation; 

      RCLCPP_INFO(this->get_logger(), "Distanza %f , rotation initial %f, rotation final %f", distance, rotation, rotation_final);
      if(rotation_final != 0.0){
        turn(rotation_final); 
      }

      //Check the reached position and apply the closed control
      double distance_closed = std::hypot(target_x - current_pose_.x, target_y - current_pose_.y);  
      double rotation_closed = atan2(target_y - current_pose_.y, target_x - current_pose_.x);
      double rotation_final_closed = target_theta - current_pose_.theta;

      while(distance_closed > 0.1){
        turn(rotation_closed);
        moveStraight(distance_closed); 
      }

      while(abs(rotation_final_closed) > 0.1){
        turn(rotation_final_closed);
      }

      // Set the target reached flag to true 
      target_reached_ = true; 

      reached_pose_.x +=  target_x;
      reached_pose_.y +=  target_y;
      reached_pose_.theta +=  target_theta;
    }
    return reached_pose_;
  } 
  

  void moveStraight(double distance) 
  { 
    std::vector<double> linear_vel_x = generateVelocityProfile(distance, MAX_LIN_VEL, MAX_LIN_ACC, FREQUENCY); 

    // Publish the linear velocity commands
    auto twist_msg = std::make_unique<geometry_msgs::msg::Twist>();  
    
    double elapsed_total_time = 0.0; 

    for(size_t i = 0; i < linear_vel_x.size(); ++i){

      auto start = std::chrono::high_resolution_clock::now();
      twist_msg->linear.x = linear_vel_x[i];
      publisher->publish(*twist_msg); 
      auto end = std::chrono::high_resolution_clock::now();
      
      std::chrono::duration<double> elapsed_time = end - start;

      // Calculate the remaining time to sleep to achieve the desired frequency
      std::chrono::duration<double> sleep_duration = std::chrono::duration<double>(1/FREQUENCY);
      std::this_thread::sleep_for(sleep_duration);
      elapsed_total_time += 1/FREQUENCY;
      std::string message = "Elapsed time: " + std::to_string(elapsed_total_time);
      RCLCPP_INFO(this->get_logger(), message.c_str());
    } 

    // Stop the robot after reaching the target pose 
    twist_msg->linear.x = 0.0; 
    publisher->publish(*twist_msg); 
  } 

  void turn(double target_theta) 
  { 
    std::vector<double> omega_z = generateVelocityProfile(target_theta, MAX_ANG_VEL, MAX_ANG_ACC, FREQUENCY);

    RCLCPP_INFO(this->get_logger(), "Distanza %f , velocità %f", target_theta, MAX_ANG_VEL);
  
    // Publish the angular velocity commands until the desired orientation is reached 
    auto twist_msg = std::make_unique<geometry_msgs::msg::Twist>(); 

    double elapsed_total_time = 0.0; 

    for(size_t i = 0; i < omega_z.size(); ++i){

      auto start = std::chrono::high_resolution_clock::now();
      twist_msg->angular.z = omega_z[i]; 
      publisher->publish(*twist_msg); 
      auto end = std::chrono::high_resolution_clock::now();
      
      std::chrono::duration<double> elapsed_time = end - start;

      // Calculate the remaining time to sleep to achieve the desired frequency
      std::chrono::duration<double> sleep_duration = std::chrono::duration<double>(1/FREQUENCY);
      std::this_thread::sleep_for(sleep_duration);
      elapsed_total_time += 1/FREQUENCY;
      std::string message = "Elapsed time: " + std::to_string(elapsed_total_time);
      RCLCPP_INFO(this->get_logger(), message.c_str());
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
  geometry_msgs::msg::Pose2D reached_pose_;
  double linear_velocity_; 
  double angular_velocity_; 

  //using HazardMsg = irobot_create_msgs::msg::HazardDetectionVector;

  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr m_odom_subscription;

};


int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  // Create a Rate object with the desired loop rate (e.g., 10 Hz)
  //rclcpp::Rate loop_rate(FREQUENCY); // 10 Hz
  
  while (rclcpp::ok())
  {
    // Process any pending messages or callbacks
    rclcpp::spin(std::make_shared<InterpolatorNode>());
    
    // Sleep to maintain the desired loop rate
    //loop_rate.sleep();
  }  
  rclcpp::shutdown();
  return 0;
}