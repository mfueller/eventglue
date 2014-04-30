/*
 * JointPositionCommandWrapper.h
 *
 *  Created on: Apr 29, 2014
 *      Author: matthias
 */

#ifndef JOINTPOSITIONCOMMANDWRAPPER_H_
#define JOINTPOSITIONCOMMANDWRAPPER_H_

#include "ros/ros.h"
#include "kdl/jntarray.hpp"

#include <vector>
#include <string>

#include "brics_actuator/JointPositions.h"

namespace mir_industrial {
namespace manipulation {

class JointPositionCommandWrapper {
protected:

	ros::Publisher pub_cmd_values;

	std::vector<std::string> joint_names;

public:
	JointPositionCommandWrapper();
	virtual ~JointPositionCommandWrapper();

	void setJointNames(std::vector<std::string> joint_names);

	void commandJointPositions(KDL::JntArray joint_positions);

	void init();

};

} /* namespace manipulation */
} /* namespace mir_industrial */

#endif /* JOINTPOSITIONCOMMANDWRAPPER_H_ */
