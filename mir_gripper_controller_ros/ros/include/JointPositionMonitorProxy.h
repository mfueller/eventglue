/*
 * JointPositionMonitorProxy.h
 *
 *  Created on: Apr 17, 2014
 *      Author: matthias
 */

#ifndef JOINTPOSITIONMONITORPROXY_H_
#define JOINTPOSITIONMONITORPROXY_H_

#include "mcr_data_glue/EventGlue.h"

#include <kdl/jntarray.hpp>

#include "mcr_data_glue/ros/RosEventGlue.h"

namespace mir_industrial {
namespace manipulation {

class JointPositionMonitorProxy {

	//PortOut<>
public:

	EventTarget& event_in_target;
	EventSource& event_out;
	OutPort<KDL::JntArray>::type& pin_joint_position;

	JointPositionMonitorProxy():
			event_in_target(ROS_EVENT_SINK("joint_position_monitor/event/out")),
			event_out(ROS_EVENT_SOURCE("joint_position_monitor/event/in")),
			pin_joint_position(ROS_PORT_SOURCE(sensor_msgs::JointState, KDL::JntArray, "joint_position_monitor/port/in/joint_position"))
	{}


	virtual ~JointPositionMonitorProxy() {}

};

} /* namespace manipulation */
} /* namespace mir_industrial */

#endif /* JOINTPOSITIONMONITORPROXY_H_ */
