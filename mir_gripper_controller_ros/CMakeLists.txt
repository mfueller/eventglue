cmake_minimum_required(VERSION 2.8.3)
project(mir_gripper_controller_ros)

find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs brics_actuator mir_gripper_controller)
find_package(eigen REQUIRED)
find_package(orocos_kdl REQUIRED)

set( CMAKE_CXX_FLAGS "-Wno-enum-compare " )

catkin_python_setup()

catkin_package(
  CATKIN_DEPENDS
    roscpp
    mir_manipulation_msgs
    rospy
    sensor_msgs
    brics_actuator
)

include_directories(
  ros/include
   ${EIGEN_INCLUDE_DIRS}
   ${mcr_data_glue_INCLUDE_DIRS}
   ${mir_gripper_controller_INCLUDE_DIRS}
   
)

link_directories(
  ${catkin_LIBRARY_DIRS}
  ${orocos_kdl_LIBRARY_DIRS}
  ${mcr_data_glue_LIBRARY_DIRS}
  ${mir_gripper_controller_DIRS} 
)

add_executable(gripper_controller_node
  ros/src/YouBotGripperNode.cpp
  ros/src/JointPositionMonitorProxy.cpp
)

target_link_libraries(gripper_controller_node
  ${catkin_LIBRARIES}
  ${orocos_kdl_LIBRARIES}  
  ${mcr_data_glue_LIBRARIES}
  ${mir_gripper_controller_LIBRARIES} 
)


install(PROGRAMS
  ros/scripts/gripper_command_controller
  ros/scripts/gripper_command_controller_basic
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY ros/launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/ros/launch
)





