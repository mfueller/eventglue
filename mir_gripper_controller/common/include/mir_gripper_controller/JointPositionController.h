/*
 * GripperController.h
 *
 *  Created on: Mar 24, 2014
 *      Author: matthias
 */

#ifndef JOINT_POSITION_CONTROLLER_H_
#define JOINT_POSITION_CONTROLLER_H_

#include <iostream>
#include <string>
#include <vector>

#include "mcr_robinson/EventGlue.h"

#include <kdl/jntarray.hpp>


namespace mir_industrial {
namespace manipulation {



class JointPositionController {
protected:

	KDL::JntArray target;
	std::vector<std::string> joint_names;

	enum State {STARTED, IDLE, ACTIVE};

	State state;

public:

	//EVENT_OUT(JointPositionController, event_done);
	EventPortInput event_out;

	DataPortOutput<KDL::JntArray>::type pout_jntarray;

	JointPositionController();

	virtual ~JointPositionController();

	//EVENT_IN(JointPositionController, e_start);
	void e_in(std::string event);

	void pin_target_position(KDL::JntArray joint_positions);

	void pin_joint_names(std::vector<std::string> joint_names);

	void step();

	bool init();
};

} /* namespace manipulation */
} /* namespace mir_industrial */

#endif /* GRIPPERCONTROLLER_H_ */
