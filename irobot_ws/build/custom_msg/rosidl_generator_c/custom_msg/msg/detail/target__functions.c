// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_msg:msg/Target.idl
// generated code does not contain a copyright notice
#include "custom_msg/msg/detail/target__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `target_pose`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
custom_msg__msg__Target__init(custom_msg__msg__Target * msg)
{
  if (!msg) {
    return false;
  }
  // target_pose
  if (!geometry_msgs__msg__Vector3__init(&msg->target_pose)) {
    custom_msg__msg__Target__fini(msg);
    return false;
  }
  // target_orientation
  return true;
}

void
custom_msg__msg__Target__fini(custom_msg__msg__Target * msg)
{
  if (!msg) {
    return;
  }
  // target_pose
  geometry_msgs__msg__Vector3__fini(&msg->target_pose);
  // target_orientation
}

bool
custom_msg__msg__Target__are_equal(const custom_msg__msg__Target * lhs, const custom_msg__msg__Target * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // target_pose
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->target_pose), &(rhs->target_pose)))
  {
    return false;
  }
  // target_orientation
  if (lhs->target_orientation != rhs->target_orientation) {
    return false;
  }
  return true;
}

bool
custom_msg__msg__Target__copy(
  const custom_msg__msg__Target * input,
  custom_msg__msg__Target * output)
{
  if (!input || !output) {
    return false;
  }
  // target_pose
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->target_pose), &(output->target_pose)))
  {
    return false;
  }
  // target_orientation
  output->target_orientation = input->target_orientation;
  return true;
}

custom_msg__msg__Target *
custom_msg__msg__Target__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_msg__msg__Target * msg = (custom_msg__msg__Target *)allocator.allocate(sizeof(custom_msg__msg__Target), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_msg__msg__Target));
  bool success = custom_msg__msg__Target__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
custom_msg__msg__Target__destroy(custom_msg__msg__Target * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    custom_msg__msg__Target__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
custom_msg__msg__Target__Sequence__init(custom_msg__msg__Target__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_msg__msg__Target * data = NULL;

  if (size) {
    data = (custom_msg__msg__Target *)allocator.zero_allocate(size, sizeof(custom_msg__msg__Target), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_msg__msg__Target__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_msg__msg__Target__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
custom_msg__msg__Target__Sequence__fini(custom_msg__msg__Target__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_msg__msg__Target__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

custom_msg__msg__Target__Sequence *
custom_msg__msg__Target__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_msg__msg__Target__Sequence * array = (custom_msg__msg__Target__Sequence *)allocator.allocate(sizeof(custom_msg__msg__Target__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = custom_msg__msg__Target__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
custom_msg__msg__Target__Sequence__destroy(custom_msg__msg__Target__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    custom_msg__msg__Target__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
custom_msg__msg__Target__Sequence__are_equal(const custom_msg__msg__Target__Sequence * lhs, const custom_msg__msg__Target__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!custom_msg__msg__Target__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
custom_msg__msg__Target__Sequence__copy(
  const custom_msg__msg__Target__Sequence * input,
  custom_msg__msg__Target__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(custom_msg__msg__Target);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    custom_msg__msg__Target * data =
      (custom_msg__msg__Target *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!custom_msg__msg__Target__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          custom_msg__msg__Target__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!custom_msg__msg__Target__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
