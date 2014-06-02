/*
 * JointPositionMonitorProxy.h
 *
 *  Created on: Apr 17, 2014
 *      Author: matthias
 */

#ifndef JOINTPOSITIONMONITORPROXY_H_
#define JOINTPOSITIONMONITORPROXY_H_

#include "mcr_robinson/EventGlue.h"

#include <kdl/jntarray.hpp>

#include "mcr_robinson_ros/RosEventGlue.h"


namespace mir_industrial {
namespace manipulation {

class JointPositionMonitorProxy {

public:

	EventTarget& event_in_target;
	EventSource& event_out;
	PortSource<KDL::JntArray>::type& pin_joint_position;

	JointPositionMonitorProxy():
			event_in_target(ROS_EVENT_SINK("joint_position_monitor/event/in")),
			event_out(ROS_EVENT_SOURCE("joint_position_monitor/event/out")),
			pin_joint_position(ROS_PORT_SOURCE(sensor_msgs::JointState, KDL::JntArray, "/test"))
	{}


	virtual ~JointPositionMonitorProxy() {}

};

} /* namespace manipulation */
} /* namespace mir_industrial */

#endif /* JOINTPOSITIONMONITORPROXY_H_ */
