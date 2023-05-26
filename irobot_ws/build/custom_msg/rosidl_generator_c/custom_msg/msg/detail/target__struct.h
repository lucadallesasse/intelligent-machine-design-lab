// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_msg:msg/Target.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSG__MSG__DETAIL__TARGET__STRUCT_H_
#define CUSTOM_MSG__MSG__DETAIL__TARGET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'target_pose'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/Target in the package custom_msg.
/**
  * Target.msg
 */
typedef struct custom_msg__msg__Target
{
  geometry_msgs__msg__Vector3 target_pose;
  float target_orientation;
} custom_msg__msg__Target;

// Struct for a sequence of custom_msg__msg__Target.
typedef struct custom_msg__msg__Target__Sequence
{
  custom_msg__msg__Target * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_msg__msg__Target__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_MSG__MSG__DETAIL__TARGET__STRUCT_H_
