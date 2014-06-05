/*
 * GripperControllerCoordinator.h
 *
 *  Created on: Mar 24, 2014
 *      Author: matthias
 */

#ifndef JOINT_POSITIONCOORDINATOR_H_
#define JOINT_POSITIONCOORDINATOR_H_

#include <string>
#include <vector>
#include <kdl/jntarray.hpp>

#include "mcr_robinson/EventGlue.h"

namespace mir_industrial {
namespace manipulation {

class JointPositionCoordinator {
public:

	//EVENT_OUT(JointPositionCoordinator, event_status_done);
	EventPortInput event_status_out;

	//EVENT_OUT(JointPositionCoordinator, event_cmd_joint_ctl_start);
	EventPortInput event_cmd_joint_ctl_out;

	//EVENT_OUT(JointPositionCoordinator, event_cmd_joint_monitors_start);
	EventPortInput event_cmd_joint_monitors_out;

	JointPositionCoordinator();

	virtual ~JointPositionCoordinator();

	void e_cmd_in(std::string event);

	void e_cb_jointctl_in(std::string event);

	void e_cb_monitor_in(std::string event);

};

} /* namespace manipulation */
} /* namespace mir_industrial */

#endif /* GRIPPERCONTROLLERCOORDINATOR_H_ */
