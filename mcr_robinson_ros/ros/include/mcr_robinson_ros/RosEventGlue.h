#ifndef ROSEVENTGLUE_H_
#define ROSEVENTGLUE_H_

#include "RosEvent.h"
#include "RosPort.h"


class RosEventGlue {

public:

	static EventPortOutput& ros_event_source(std::string topic_name, std::string event_name) {

		EventPortOutputROS* event_source = new EventPortOutputROS(topic_name, event_name);
		//ros_event_sources.push_back(event_source);

		return *event_source;
	}

	static EventPortInput& ros_event_sink(std::string topic_name, std::string event_name) {

		EventPortInputROS* event_sink = new EventPortInputROS(topic_name, event_name);
		//ros_event_sinks.push_back(event_sink);

		return *event_sink;
	}


	template<typename ROS_TYPE, typename MY_TYPE>
		static typename DataPortOutput<MY_TYPE>::type& port_from_ros_topic(std::string topic_name) {

		DataPortOutputROS<ROS_TYPE, MY_TYPE>* in_port = new DataPortOutputROS<ROS_TYPE, MY_TYPE>(topic_name);

		//ros_in_ports.push_back(in_port);

		return *in_port;
	}

	template<typename ROS_TYPE, typename MY_TYPE>
		static typename DataPortInput<MY_TYPE>::type& port_to_ros_topic(std::string topic_name) {

		DataPortInputROS<ROS_TYPE, MY_TYPE>* in_port(new DataPortInputROS<ROS_TYPE, MY_TYPE>(topic_name));

		//ros_out_ports.push_back(in_port);

		return *in_port;
	}

};




#endif
