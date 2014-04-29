/*
 * RosEventGlue.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: matthias
 */

#include "mcr_data_glue/ros/RosEventGlue.h"

#include "mcr_data_glue/ros/Event_ROS.h"

RosEventGlue RosEventGlue::instance;

EventSource& RosEventGlue::ros_event_source(
		std::string topic_name) {

	RosEventSource* event_source = new RosEventSource(topic_name);
	ros_event_sources.push_back(event_source);

	return event_source->event_source;
}

EventTarget& RosEventGlue::ros_event_sink(
		std::string topic_name) {

	RosEventSink* event_sink = new RosEventSink(topic_name);
	ros_event_sinks.push_back(event_sink);

	return event_sink->event_target;
}
