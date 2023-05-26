// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_msg:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSG__MSG__DETAIL__TARGET__STRUCT_HPP_
#define CUSTOM_MSG__MSG__DETAIL__TARGET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'target_pose'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__custom_msg__msg__Target __attribute__((deprecated))
#else
# define DEPRECATED__custom_msg__msg__Target __declspec(deprecated)
#endif

namespace custom_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Target_
{
  using Type = Target_<ContainerAllocator>;

  explicit Target_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target_pose(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_orientation = 0.0f;
    }
  }

  explicit Target_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target_pose(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->target_orientation = 0.0f;
    }
  }

  // field types and members
  using _target_pose_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _target_pose_type target_pose;
  using _target_orientation_type =
    float;
  _target_orientation_type target_orientation;

  // setters for named parameter idiom
  Type & set__target_pose(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->target_pose = _arg;
    return *this;
  }
  Type & set__target_orientation(
    const float & _arg)
  {
    this->target_orientation = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_msg::msg::Target_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_msg::msg::Target_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_msg::msg::Target_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_msg::msg::Target_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_msg::msg::Target_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_msg::msg::Target_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_msg::msg::Target_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_msg::msg::Target_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_msg::msg::Target_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_msg::msg::Target_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_msg__msg__Target
    std::shared_ptr<custom_msg::msg::Target_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_msg__msg__Target
    std::shared_ptr<custom_msg::msg::Target_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Target_ & other) const
  {
    if (this->target_pose != other.target_pose) {
      return false;
    }
    if (this->target_orientation != other.target_orientation) {
      return false;
    }
    return true;
  }
  bool operator!=(const Target_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Target_

// alias to use template instance with default allocator
using Target =
  custom_msg::msg::Target_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_msg

#endif  // CUSTOM_MSG__MSG__DETAIL__TARGET__STRUCT_HPP_
