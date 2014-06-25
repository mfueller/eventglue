cmake_minimum_required(VERSION 2.8.3)
project(mcr_robinson)

#find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs brics_actuator)
#find_package(eigen REQUIRED)
#find_package(orocos_kdl REQUIRED)

#catkin_python_setup()
set( CMAKE_CXX_FLAGS "-Wno-enum-compare " )
set( CMAKE_BUILD_TYPE Debug)
catkin_package(
  CATKIN_DEPENDS
  INCLUDE_DIRS
    common/include
)

include_directories(
  common/include
)

link_directories(
  ${catkin_LIBRARY_DIRS}
)


#install(TARGETS mcr_robinson
#  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)

install(DIRECTORY common/include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)





