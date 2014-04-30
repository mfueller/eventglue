#ifndef ROSEVENTGLUE_H_
#define ROSEVENTGLUE_H_

#include "RosEvent.h"
#include "RosPort.h"


class RosEventGlue {
protected:
	std::vector<RosEventSource*> ros_event_sources;
	std::vector<RosEventSink*> ros_event_sinks;

	std::vector<RosPort*> ros_in_ports;
	std::vector<RosPort*> ros_out_ports;

public:

	static RosEventGlue instance;

	EventSource& ros_event_source(std::string topic_name) {

		RosEventSource* event_source = new RosEventSource(topic_name);
		ros_event_sources.push_back(event_source);

		return event_source->ros_topic_signal;
	}

	EventTarget& ros_event_sink(std::string topic_name) {

		RosEventSink* event_sink = new RosEventSink(topic_name);
		ros_event_sinks.push_back(event_sink);

		return event_sink->ros_publisher;
	}


	template<typename ROS_TYPE, typename MY_TYPE>
		typename OutPort<MY_TYPE>::type& port_from_ros_topic(std::string topic_name) {

		RosPortSource<ROS_TYPE, MY_TYPE>* in_port = new RosPortSource<ROS_TYPE, MY_TYPE>(topic_name);

		ros_in_ports.push_back(in_port);

		return in_port->ros_topic_signal;
	}

	template<typename ROS_TYPE, typename MY_TYPE>
		typename InPort<MY_TYPE>::type& port_to_ros_topic(std::string topic_name) {

		RosPortSink<ROS_TYPE, MY_TYPE>* in_port = new RosPortSink<ROS_TYPE, MY_TYPE>(topic_name);

		ros_out_ports.push_back(in_port);

		return in_port->ros_publisher;
	}

};




#endif
