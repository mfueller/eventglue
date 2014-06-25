cmake_minimum_required(VERSION 2.8.3)
project(mcr_robinson_ros)

find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs brics_actuator mcr_robinson)
find_package(eigen REQUIRED)
find_package(orocos_kdl REQUIRED)

catkin_python_setup()
set( CMAKE_CXX_FLAGS "-Wno-enum-compare " )

catkin_package(
  CATKIN_DEPENDS
    roscpp
    rospy
    sensor_msgs
    brics_actuator
  INCLUDE_DIRS
    ros/include
)

include_directories(
  ros/include
  ${mcr_data_glue_INCLUDE_DIRS}
   ${EIGEN_INCLUDE_DIRS}
)

link_directories(
  ${catkin_LIBRARY_DIRS}
  ${orocos_kdl_LIBRARY_DIRS}
)

#add_library(mcr_robinson_ros
#  ros/src/RosEventGlue.cpp
#)

#target_link_libraries(mcr_robinson_ros
#  ${catkin_LIBRARIES}
#  ${orocos_kdl_LIBRARIES}  
#)

#install(TARGETS mcr_robinson
#  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)

install(DIRECTORY ros/include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)





