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

#include "JointPositionCommandWrapper.h"

#include "mcr_data_glue/EventGlue.h"

#include "JointPositionMonitorProxy.h"

namespace mir_industrial {
namespace manipulation {

class YouBotGripperNode {
protected:

	JointPositionController* joint_position_controller;

	JointPositionCoordinator* joint_position_coordinator;

	JointPositionMonitorProxy* joint_position_monitor;

	JointPositionCommandWrapper* position_command_wrapper;

public:
	YouBotGripperNode();

	virtual ~YouBotGripperNode();

	void update();

};

} /* namespace manipulation */
} /* namespace mir_industrial */

#endif /* YOUBOTGRIPPERCONTROLLERNODE_H_ */
