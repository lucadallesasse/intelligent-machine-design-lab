# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_traj_interpolator_closedloop_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED traj_interpolator_closedloop_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(traj_interpolator_closedloop_FOUND FALSE)
  elseif(NOT traj_interpolator_closedloop_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(traj_interpolator_closedloop_FOUND FALSE)
  endif()
  return()
endif()
set(_traj_interpolator_closedloop_CONFIG_INCLUDED TRUE)

# output package information
if(NOT traj_interpolator_closedloop_FIND_QUIETLY)
  message(STATUS "Found traj_interpolator_closedloop: 0.0.0 (${traj_interpolator_closedloop_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'traj_interpolator_closedloop' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${traj_interpolator_closedloop_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(traj_interpolator_closedloop_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_include_directories-extras.cmake;ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${traj_interpolator_closedloop_DIR}/${_extra}")
endforeach()
