cmake_minimum_required(VERSION 2.8.3)
project(mcr_robinson_hello_world)

find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs brics_actuator mcr_robinson)
find_package(eigen REQUIRED)
find_package(orocos_kdl REQUIRED)

set( CMAKE_CXX_FLAGS "-Wno-enum-compare " )
set( CMAKE_BUILD_TYPE Debug)

catkin_package(
  CATKIN_DEPENDS
    roscpp
    mir_manipulation_msgs
    rospy
    sensor_msgs
    brics_actuator
    mcr_robinson
  INCLUDE_DIRS
    common/include
  LIBRARIES
    helloworld
)

include_directories(
  ros/include
  common/include
  ${EIGEN_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS} 
 )

link_directories(
  ${catkin_LIBRARY_DIRS}
  ${orocos_kdl_LIBRARY_DIRS}
)

add_library(helloworld
  common/src/HelloWorld.cpp
)

target_link_libraries(helloworld
  ${catkin_LIBRARIES}
  ${orocos_kdl_LIBRARIES}  
)

install(DIRECTORY common/include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  PATTERN ".svn" EXCLUDE
)







