#ifndef EVENTGLUE_ROSEVENTGLUE_H_
#define EVENTGLUE_ROSEVENTGLUE_H_

#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signal.hpp>
#include <boost/any.hpp>

#include <map>
#include <vector>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <kdl/jntarray.hpp>

#include "mcr_robinson/message_converter/MessageConverter.h"
#include "mcr_robinson_ros/message_converter/ros_msgs.h"

#include <iostream>

#include "mcr_robinson/EventGlue.h"

#include "RosPort.h"


#define ROS_EVENT_SOURCE(TOPIC) \
		RosEventGlue::ros_event_source(TOPIC)

#define ROS_EVENT_SINK(TOPIC) \
		RosEventGlue::ros_event_sink(TOPIC)


typedef RosPortSource<std_msgs::String, std::string> RosEventSource;
typedef RosPortSink<std_msgs::String, std::string> RosEventSink;






#endif
