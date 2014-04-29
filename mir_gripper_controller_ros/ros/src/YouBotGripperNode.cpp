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

#include "mcr_data_glue/ros/RosEventGlue.h"





//template<class CPP_TYPE>
//inline typename OutPort<CPP_TYPE>::type& operator>>(typename OutPort<CPP_TYPE>::type& lhs, typename InPort<CPP_TYPE>::type const& rhs) {
//	lhs.connect(rhs);
//	return lhs;
//}
//
//template<>
//inline typename OutPort<>::type& operator>>(typename OutPort<>::type& lhs, typename InPort<>::type const& rhs) {
//	lhs.connect(rhs);
//	return lhs;
//}

//inline OutPort<KDL::JntArray>::type& operator>>(OutPort<KDL::JntArray>::type& lhs, InPort<KDL::JntArray>::type const& rhs) {
//	lhs.connect(rhs);
//	return lhs;
//}

	/*
	event_tool->port_from_ros_topic<sensor_msgs::JointState, KDL::JntArray>("joint_controller/port/pin_joint_state")
			>> boost::bind(&JointPositionController::pin_target_position, joint_position_controller, _1);
*/

namespace mir_industrial {
namespace manipulation {

/*

OutPort<KDL::JntArray>::type& operator>>(OutPort<KDL::JntArray>::type& lhs, InPort<KDL::JntArray>::type const& rhs) {
	lhs.connect(rhs);
	return lhs;
}

OutPort<std::vector<std::string> >::type& operator>>(OutPort<std::vector<std::string> >::type& lhs, InPort<std::vector<std::string> >::type const& rhs) {
	lhs.connect(rhs);
	return lhs;
}

*/
YouBotGripperNode::YouBotGripperNode() {


	// connect the position controller
	joint_position_controller = new JointPositionController();

	joint_position_coordinator = new JointPositionCoordinator();

	joint_position_monitor = new JointPositionMonitorProxy();


	// internal wireing
	RosEventGlue::instance.ros_event_sink("joint_position_monitor/event/out");

	//coordinator <-> monitor proxy
	//EVENT_SOURCE(joint_position_coordinator->event_cmd_joint_monitors_out)
	//	>> EVENT_SINK(&JointPositionMonitorProxy::e_in, joint_position_monitor);
	//EVENT_SOURCE(joint_position_monitor->event_out)
	//	>> EVENT_SINK(&JointPositionCoordinator::e_cb_monitor_in, joint_position_coordinator);
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


	//connect controller to and from ROS


	//OutPort<KDL::JntArray>::type& t = ROS_PORT_SOURCE ("joint_controller/port/pin_joint_state", sensor_msgs::JointState, KDL::JntArray);
	//InPort<KDL::JntArray>::type in = PORT_SINK(&JointPositionController::pin_target_position, joint_position_controller);

	//operator>> <KDL::JntArray>(
	//		ROS_PORT_SOURCE ("joint_controller/port/pin_joint_state", sensor_msgs::JointState, KDL::JntArray),
	//		PORT_SINK(&JointPositionController::pin_target_position, joint_position_controller));

	///test<std::string>(std::string("Hello"));
    //ROS_PORT_SOURCE ("joint_controller/port/pin_joint_state", sensor_msgs::JointState, KDL::JntArray)
	//	>> PORT_SINK(&JointPositionController::pin_target_position, joint_position_controller);

//    joint_position_controller->pout_jntarray
//    	+= boost::bind(&YouBotGripperNode::commandJointPositions, this, _1);


    	//PORT_SINK(, this);

	//t.connect(in);

	//.connect(
	//
	//);
	/*
	event_tool->port_from_ros_topic<sensor_msgs::JointState, KDL::JntArray>("joint_controller/port/pin_joint_state")
			>> boost::bind(&JointPositionController::pin_target_position, joint_position_controller, _1);

	event_tool->port_from_ros_topic<sensor_msgs::JointState, std::vector<std::string> >("joint_controller/port/pin_joint_state")
			>> boost::bind(&JointPositionController::pin_joint_names, joint_position_controller, _1);

	event_tool->port_from_ros_topic<sensor_msgs::JointState, std::vector<std::string> >("joint_controller/port/pin_joint_state")
			>> boost::bind(&YouBotGripperNode::setJointNames, this, _1);
	*/


}


bool YouBotGripperNode::init() {
	ros::NodeHandle node("~");

	pub_cmd_values = node.advertise<brics_actuator::JointPositions>("position_command", 1);


}
YouBotGripperNode::~YouBotGripperNode() {
	delete joint_position_controller;
	//delete event_tool;
}

void YouBotGripperNode::setJointNames(std::vector<std::string> joint_names) {
	this->joint_names = joint_names;
}

void YouBotGripperNode::commandJointPositions(KDL::JntArray joint_positions) {
	brics_actuator::JointPositions pos;

	for (std::size_t i = 0; i < joint_positions.data.rows(); i++) {
		brics_actuator::JointValue v1;
		v1.joint_uri = this->joint_names[i];
		v1.value = joint_positions(0);
		v1.unit = "m";
		pos.positions.push_back(v1);
	}

	this->pub_cmd_values.publish(pos);
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

	gripper_ctl_node.init();

	ros::Rate loop_rate(20);

	while(ros::ok()) {
		gripper_ctl_node.update();
		ros::spinOnce();
		loop_rate.sleep();
	}


	return -1;
}


