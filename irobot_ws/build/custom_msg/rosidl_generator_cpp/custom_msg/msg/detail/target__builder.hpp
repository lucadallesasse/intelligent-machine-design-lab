// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_msg:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSG__MSG__DETAIL__TARGET__BUILDER_HPP_
#define CUSTOM_MSG__MSG__DETAIL__TARGET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_msg/msg/detail/target__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_msg
{

namespace msg
{

namespace builder
{

class Init_Target_target_orientation
{
public:
  explicit Init_Target_target_orientation(::custom_msg::msg::Target & msg)
  : msg_(msg)
  {}
  ::custom_msg::msg::Target target_orientation(::custom_msg::msg::Target::_target_orientation_type arg)
  {
    msg_.target_orientation = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_msg::msg::Target msg_;
};

class Init_Target_target_pose
{
public:
  Init_Target_target_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Target_target_orientation target_pose(::custom_msg::msg::Target::_target_pose_type arg)
  {
    msg_.target_pose = std::move(arg);
    return Init_Target_target_orientation(msg_);
  }

private:
  ::custom_msg::msg::Target msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_msg::msg::Target>()
{
  return custom_msg::msg::builder::Init_Target_target_pose();
}

}  // namespace custom_msg

#endif  // CUSTOM_MSG__MSG__DETAIL__TARGET__BUILDER_HPP_
