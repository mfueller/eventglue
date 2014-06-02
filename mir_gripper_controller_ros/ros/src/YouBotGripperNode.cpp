/*
 * YouBotGripperControllerNode.cpp
 *
 *  Created on: Mar 24, 2014
 *      Author: matthias
 */


#include "YouBotGripperNode.h"


#include <iostream>

#include <brics_actuator/JointPositions.h>
#include <std_msgs/String.h>

#include "ros/ros.h"

#include "mcr_robinson_ros/RosEventGlue.h"

namespace mir_industrial {
namespace manipulation {

YouBotGripperNode::YouBotGripperNode() {


	// connect the position controller
	joint_position_controller = new JointPositionController();

	joint_position_coordinator = new JointPositionCoordinator();

	joint_position_monitor = new JointPositionMonitorProxy();

	position_command_wrapper = new JointPositionCommandWrapper();

	//coordinator <-> monitor proxy
	EVENT_SOURCE(joint_position_coordinator->event_cmd_joint_monitors_out)
		>> EVENT_SOURCE(joint_position_monitor->event_in_target);

	EVENT_SOURCE(joint_position_monitor->event_out)
		>> EVENT_SINK(&JointPositionCoordinator::e_cb_monitor_in, joint_position_coordinator);


	//coordinator <-> joint controller
	EVENT_SOURCE(joint_position_coordinator->event_cmd_joint_ctl_out)
		>> EVENT_SINK(&JointPositionController::e_in, joint_position_controller);
	EVENT_SOURCE(joint_position_controller->event_out)
			>> EVENT_SINK(&JointPositionCoordinator::e_cb_jointctl_in, joint_position_coordinator);

	// Coordinator is allowed to communicate with ROS
	ROS_EVENT_SOURCE("coordinator/event/in")
			>> EVENT_SINK(&JointPositionCoordinator::e_cmd_in, joint_position_coordinator);

	EVENT_SOURCE(joint_position_coordinator->event_status_out)
			>> ROS_EVENT_SINK("coordinator/event/out");

	// connect ports (>> overloading fails due to template deduction problem)
    ROS_PORT_SOURCE (sensor_msgs::JointState, KDL::JntArray, "joint_controller/port/pin_joint_state")
			.connect(PORT_SINK(&JointPositionController::pin_target_position, joint_position_controller));



}



YouBotGripperNode::~YouBotGripperNode() {
	delete joint_position_controller;
	delete joint_position_coordinator;
	delete joint_position_monitor;
}



void YouBotGripperNode::update() {

	this->joint_position_controller->step();

}

} /* namespace manipulation */
} /* namespace mir_industrial */



int main( int argc, char* argv[] )
{

	ros::init(argc, argv, "youbot_gripper_controller_node");
	ros::NodeHandle n("~");

	mir_industrial::manipulation::YouBotGripperNode gripper_ctl_node
			= mir_industrial::manipulation::YouBotGripperNode();

	ros::Rate loop_rate(20);

	while(ros::ok()) {
		gripper_ctl_node.update();
		ros::spinOnce();
		loop_rate.sleep();
	}


	return -1;
}


