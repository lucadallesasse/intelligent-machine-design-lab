cmake_minimum_required(VERSION 3.5)
project(traj_interpolator)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(irobot_create_msgs REQUIRED)
find_package(custom_msgs REQUIRED)

# Add your package's source files and headers here
add_executable(${PROJECT_NAME}_node
  src/draw_traj.cpp
)

# Add any additional dependencies specific to your package
ament_target_dependencies(${PROJECT_NAME}
  rclcpp
  std_msgs
  irobot_create_msgs
  custom_msgs
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

