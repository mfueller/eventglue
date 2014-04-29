/*
 * YouBotGripperControllerNode.h
 *
 *  Created on: Mar 24, 2014
 *      Author: matthias
 */

#ifndef YOUBOTGRIPPERRNODE_H_
#define YOUBOTGRIPPERRNODE_H_

#include "ros/ros.h"

#include "mir_gripper_controller/JointPositionController.h"
#include "mir_gripper_controller/JointPositionCoordinator.h"
#include "mcr_data_glue/EventGlue.h"
#include "mcr_data_glue/ros/Event_ROS.h"

#include "JointPositionMonitorProxy.h"

namespace mir_industrial {
namespace manipulation {

/*
template <typename T>
typename OutPort<T>::type& operator>>(typename OutPort<T>::type& lhs, typename InPort<T>::type const& rhs) {
	lhs.connect(rhs);
	return lhs;
}
*/


class YouBotGripperNode {
protected:
	//RosEventGlue* event_tool;
	JointPositionController* joint_position_controller;

	JointPositionCoordinator* joint_position_coordinator;

	JointPositionMonitorProxy* joint_position_monitor;

	ros::Publisher pub_cmd_values;

	std::vector<std::string> joint_names;

public:
	YouBotGripperNode();

	virtual ~YouBotGripperNode();

	virtual void commandJointPositions(KDL::JntArray joint_positions);

	void setJointNames(std::vector<std::string> joint_names);

	bool init();

	void update();

};

} /* namespace manipulation */
} /* namespace mir_industrial */

#endif /* YOUBOTGRIPPERCONTROLLERNODE_H_ */
