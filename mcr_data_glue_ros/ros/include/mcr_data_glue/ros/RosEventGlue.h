#ifndef ROSEVENTGLUE_H_
#define ROSEVENTGLUE_H_

#include "Event_ROS.h"
#include "Port_ROS.h"


class RosEventGlue {
protected:
	std::vector<RosEventSource*> ros_event_sources;
	std::vector<RosEventSink*> ros_event_sinks;

	std::vector<RosPort*> ros_in_ports;
	std::vector<RosPort*> ros_out_ports;

public:

	static RosEventGlue instance;

	EventSource& ros_event_source(std::string topic_name);

	EventTarget& ros_event_sink(std::string topic_name);

	template<typename ROS_TYPE, typename MY_TYPE>
		typename OutPort<MY_TYPE>::type& port_from_ros_topic(std::string topic_name);

	template<typename ROS_TYPE, typename MY_TYPE>
		typename InPort<MY_TYPE>::type& port_to_ros_topic(std::string topic_name);


	/*
	template<typename TYPE>
		void register_events(TYPE* object, std::string target_namespace = "") {
		this->register_event_sources(object, target_namespace);
		this->register_event_targets(object, target_namespace);
	};
	*/
	/*
	template<typename TYPE>
	void register_event_sources(TYPE* object, std::string target_namespace = "", std::string topic_name = "/event/out") {

		typename EventRegistry<TYPE>::return_type list = EventRegistry<TYPE>::getEventSources();

		std::cout << "List size: " << list.size() << std::endl;
		for (int i=0; i< list.size(); i++) {
			std::cout << "##### Got Source Event: " << list[i]->event_name << std::endl;

			std::stringstream ss;
			ss << target_namespace << "/" << topic_name;
			//list[i]->get(object) >> this->ros_event_sink(ss.str(), list[i]->event_name);
			list[i]->get(object).connect(this->ros_event_sink(ss.str(), list[i]->event_name));
		}

	};

	template<typename TYPE>
	void register_event_targets(TYPE* object, std::string target_namespace = "", std::string topic_name = "/event/in") {

		typename EventRegistry<TYPE>::return_type_target list = EventRegistry<TYPE>::getEventTargets();
		for (int i=0; i< list.size(); i++) {
			std::cout << "##### Got Target Event: " << list[i]->event_name << std::endl;
			std::stringstream ss;
			ss << target_namespace << "/" << topic_name;


			ros_event_source(ss.str(), list[i]->event_name).connect(list[i]->get(object));
		}

	};
	*/
};

template<typename ROS_TYPE, typename MY_TYPE>
typename InPort<MY_TYPE>::type& RosEventGlue::port_to_ros_topic(std::string topic_name) {

	RosPortSink<ROS_TYPE, MY_TYPE>* in_port = new RosPortSink<ROS_TYPE, MY_TYPE>(topic_name);

	ros_out_ports.push_back(in_port);

	return in_port->ros_publisher;
}


template<typename ROS_TYPE, typename MY_TYPE>
typename OutPort<MY_TYPE>::type& RosEventGlue::port_from_ros_topic(std::string topic_name) {

	RosPortSource<ROS_TYPE, MY_TYPE>* in_port = new RosPortSource<ROS_TYPE, MY_TYPE>(topic_name);

	ros_in_ports.push_back(in_port);

	return in_port->ros_topic_signal;
}



#endif
