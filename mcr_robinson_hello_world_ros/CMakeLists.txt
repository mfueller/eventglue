cmake_minimum_required(VERSION 2.8.3)
project(mcr_robinson_hello_world_ros)

###### only required for the python example
set(Python_ADDITIONAL_VERSIONS 3.2)
find_package(Boost COMPONENTS system filesystem unit_test_framework python-py32 REQUIRED)
find_package(PythonLibs REQUIRED)
######


find_package(catkin REQUIRED COMPONENTS roscpp mcr_robinson_hello_world mcr_robinson_ros mcr_robinson_python)


## debugging...
set( CMAKE_CXX_FLAGS "-Wno-enum-compare " )
set( CMAKE_BUILD_TYPE Debug)


# python example
catkin_python_setup()


catkin_package(
  CATKIN_DEPENDS
    roscpp
    rospy
    mcr_robinson_python
)

include_directories(
  ros/include
   ${EIGEN_INCLUDE_DIRS}
   ${mcr_robinson_INCLUDE_DIRS}
   ${mcr_robinson_ros_INCLUDE_DIRS}
   ${mcr_robinson_hello_world_INCLUDE_DIRS}

#### required for the python example
   ${mcr_robinson_python_INCLUDE_DIRS}
   ${Boost_INCLUDE_DIRS}
   ${PYTHON_INCLUDE_DIRS}
####
)

link_directories(
  ${catkin_LIBRARY_DIRS}
  ${mcr_robinson_LIBRARY_DIRS}
  ${mcr_robinson_hello_world_DIRS} 
)

add_executable(hello_world_node
  ros/src/HelloWorldNode.cpp
)

target_link_libraries(hello_world_node
  ${catkin_LIBRARIES}
  ${mcr_robinson_ros_LIBRARIES}
  ${mcr_robinson_hello_world_LIBRARIES} 
)


add_executable(hello_world_node_python
  ros/src/HelloPythonNode.cpp
)

target_link_libraries(hello_world_node_python
  ${catkin_LIBRARIES}
  ${mcr_robinson_ros_LIBRARIES}
  ${mcr_robinson_hello_world_LIBRARIES} 
  
### required for the python example  
  ${mcr_robinson_python_LIBRARIES}
  mcr_robinson_python
  ${Boost_LIBRARIES}
  ${PYTHON_LIBRARIES}
##
)


install(PROGRAMS
  ros/scripts/gripper_command_controller
  ros/scripts/gripper_command_controller_basic
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY ros/launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/ros/launch
)





