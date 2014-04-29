/*
 * GripperController.cpp
 *
 *  Created on: Mar 24, 2014
 *      Author: matthias
 */

#include "mir_gripper_controller/JointPositionController.h"

namespace mir_industrial {
namespace manipulation {


JointPositionController::JointPositionController() {
	state = STARTED;
}

JointPositionController::~JointPositionController() {
	//OutPort();
}


void JointPositionController::step() {

	if (this->state == ACTIVE) {

		std::cout << "JointPositionController::step()/ACTIVE" << std::endl;

		if (this->joint_names.size() == 0) {
			std::cerr << "JointPositionController::step(): No joint names are defined" << std::endl;
		}

		if (this->target.data.rows() == 0) {
					std::cerr << "JointPositionController::step(): No joint positions are defined" << std::endl;
		}

		if (this->joint_names.size() != this->target.data.rows()) {
			std::cerr << "JointPositionController::step(): size of given joint names and joint positions are not equal" << std::endl;

			this->event_out("e_error");
		}
		std::cout << "JointPositionController::step(): writing joint positions" << std::endl;
		this->pout_jntarray(this->target);

		std::cout << "JointPositionController::step(): event->done" << std::endl;
		this->event_out("e_done");
		this->state = IDLE;
	} else if (this->state == STARTED) {
		this->init();
	}
}


void JointPositionController::e_in(std::string event) {
	/*
	std::cout << "JointPositionController::e_start()" << std::endl;

	if (this->state < IDLE) {
		std::cout << "JointPositionController::e_start(): state is not IDLE" << std::endl;
		return;
	}
	std::cout << "JointPositionController::e_start(): switched to ACTIVE" << std::endl;

	this->state = ACTIVE;
	*/
}


/*
void JointPositionController::e_stop() {
	std::cout << "JointPositionController::e_stop()" << std::endl;

	if (this->state != ACTIVE) {
		return;
	}

	this->state = IDLE;
}
*/

void JointPositionController::pin_target_position(KDL::JntArray joint_positions) {
	std::cout << "JointPositionController::pin_target_position()" << std::endl;

	this->target = joint_positions;
}

void JointPositionController::pin_joint_names(
		std::vector<std::string> joint_names) {
	std::cout << "JointPositionController::pin_joint_names()" << std::endl;

	this->joint_names = joint_names;
}

bool JointPositionController::init() {
	if (this->event_out.empty()) {
		std::cout << "No event source for e_done connected" << std::endl;
		return false;
	}

	if (this->pout_jntarray.empty()) {
		//FIXME: clean up
		//std::cout << "No outport for jntarray connected" << std::endl;
		//return false;
	}

	state = IDLE;
	std::cout << "JointPositionController::init(): state IDLE" << std::endl;

	return true;
}


} /* namespace manipulation */
} /* namespace mir_industrial */


