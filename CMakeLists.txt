cmake_minimum_required(VERSION 2.8.3)
project(measure_acceleration)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  sensor_msgs
  nav_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES MeasureLinearAcc MeasureAngularAcc
#  CATKIN_DEPENDS geometry_msgs roscpp rospy sensor_msgs std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include ${catkin_INCLUDE_DIRS}
# include
  ${catkin_INCLUDE_DIRS}
)

add_library(MeasureLinearAcc
  src/MeasureLinearAcc.cpp
  src/MeasureAcceleration.cpp
)
add_dependencies(MeasureLinearAcc ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(MeasureLinearAcc
  ${catkin_LIBRARIES}
)

add_executable(measure_linear_acceleration
  src/measure_linear_acceleration.cpp
)
add_dependencies(measure_linear_acceleration ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} MeasureLinearAcc)
target_link_libraries(measure_linear_acceleration
  ${catkin_LIBRARIES}
  MeasureLinearAcc
)

add_library(MeasureAngularAcc
  src/MeasureAngularAcc.cpp
  src/MeasureAcceleration.cpp
)
add_dependencies(MeasureAngularAcc ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(MeasureAngularAcc
  ${catkin_LIBRARIES}
)

add_executable(measure_angular_acceleration
  src/measure_angular_acceleration.cpp
)
add_dependencies(measure_angular_acceleration ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} MeasureAngularAcc)
target_link_libraries(measure_angular_acceleration
  ${catkin_LIBRARIES}
  MeasureAngularAcc
)