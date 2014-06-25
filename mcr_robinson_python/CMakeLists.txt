cmake_minimum_required(VERSION 2.8.3)
project(mcr_robinson_python)

set(Python_ADDITIONAL_VERSIONS 3.2)

find_package(eigen REQUIRED)

catkin_python_setup()


set( CMAKE_CXX_FLAGS "-Wno-enum-compare " )
set( CMAKE_BUILD_TYPE Debug)
SET(BUILD_SHARED_LIBS ON)


find_package(Boost COMPONENTS system filesystem unit_test_framework python-py32 REQUIRED)
find_package(PythonLibs REQUIRED)
set(CMAKE_CXX_FLAGS "-Wall")

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
   ${Boost_INCLUDE_DIRS}
   ${PYTHON_INCLUDE_DIRS}
)

file(GLOB_RECURSE CXX_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/common/include/*.cxx
)

ADD_LIBRARY(mcr_robinson_python SHARED ${CXX_FILES})
TARGET_LINK_LIBRARIES(mcr_robinson_python ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

link_directories(
  ${catkin_LIBRARY_DIRS}
  ${orocos_kdl_LIBRARY_DIRS}
)


install(DIRECTORY common/include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)





