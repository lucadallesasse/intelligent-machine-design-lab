// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from custom_msg:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSG__MSG__DETAIL__TARGET__TRAITS_HPP_
#define CUSTOM_MSG__MSG__DETAIL__TARGET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "custom_msg/msg/detail/target__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'target_pose'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace custom_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const Target & msg,
  std::ostream & out)
{
  out << "{";
  // member: target_pose
  {
    out << "target_pose: ";
    to_flow_style_yaml(msg.target_pose, out);
    out << ", ";
  }

  // member: target_orientation
  {
    out << "target_orientation: ";
    rosidl_generator_traits::value_to_yaml(msg.target_orientation, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Target & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: target_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_pose:\n";
    to_block_style_yaml(msg.target_pose, out, indentation + 2);
  }

  // member: target_orientation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_orientation: ";
    rosidl_generator_traits::value_to_yaml(msg.target_orientation, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Target & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace custom_msg

namespace rosidl_generator_traits
{

[[deprecated("use custom_msg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const custom_msg::msg::Target & msg,
  std::ostream & out, size_t indentation = 0)
{
  custom_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use custom_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const custom_msg::msg::Target & msg)
{
  return custom_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<custom_msg::msg::Target>()
{
  return "custom_msg::msg::Target";
}

template<>
inline const char * name<custom_msg::msg::Target>()
{
  return "custom_msg/msg/Target";
}

template<>
struct has_fixed_size<custom_msg::msg::Target>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Vector3>::value> {};

template<>
struct has_bounded_size<custom_msg::msg::Target>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Vector3>::value> {};

template<>
struct is_message<custom_msg::msg::Target>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CUSTOM_MSG__MSG__DETAIL__TARGET__TRAITS_HPP_
