cmake_minimum_required(VERSION 2.8.3)
project(mcr_data_glue)

find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs brics_actuator)
find_package(eigen REQUIRED)
find_package(orocos_kdl REQUIRED)

#catkin_python_setup()
set( CMAKE_CXX_FLAGS "-Wno-enum-compare " )

catkin_package(
  CATKIN_DEPENDS
    roscpp
    rospy
    sensor_msgs
    brics_actuator
  INCLUDE_DIRS
    common/include
)

include_directories(
  common/include
   ${EIGEN_INCLUDE_DIRS}
)

link_directories(
  ${catkin_LIBRARY_DIRS}
  ${orocos_kdl_LIBRARY_DIRS}
)


#install(TARGETS mcr_data_glue
#  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)

install(DIRECTORY common/include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)





