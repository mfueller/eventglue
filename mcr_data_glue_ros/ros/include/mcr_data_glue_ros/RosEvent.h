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

#include "mcr_data_glue/message_converter/MessageConverter.h"
#include "mcr_data_glue_ros/message_converter/ros_msgs.h"

#include <iostream>

#include "mcr_data_glue/EventGlue.h"

#include "RosPort.h"


#define ROS_EVENT_SOURCE(TOPIC) \
		RosEventGlue::instance.ros_event_source(TOPIC)

#define ROS_EVENT_SINK(TOPIC) \
		RosEventGlue::instance.ros_event_sink(TOPIC)


typedef RosPortSource<std_msgs::String, std::string> RosEventSource;
typedef RosPortSink<std_msgs::String, std::string> RosEventSink;


//class RosEventSource {
//	std::string topic_name;
//	ros::Subscriber subscriber;
//public:
//	EventSource event_source;
//
//
//	RosEventSource(std::string topic_name) {
//		std::cout << "RosEventSource::RosEventSource(topic, name): registered to: " << topic_name << ":" << std::endl;
//
//		ros::NodeHandle n("~");
//		this->topic_name = topic_name;
//
//		this->subscriber = n.subscribe(this->topic_name, 1,
//				&RosEventSource::event_callback, this);
//
//	}
//
//	~RosEventSource() {
//		std::cout << "RosEventSource::~RosEventSource()"<<std::endl;
//
//		this->subscriber.shutdown();
//	}
//
//	void event_callback(std_msgs::String event) {
//		event_source(std::string(event.data));
//	}
//
//};
//
//
//
//
//class RosEventSink {
//	std::string topic_name;
//	ros::Publisher publisher;
//public:
//	EventTarget event_target;
//
//	RosEventSink(std::string topic_name) {
//		std::cout << "RosEventSink::RosEventSink(topic, name): publishes to: " << topic_name << ":" << std::endl;
//
//		ros::NodeHandle n("~");
//		this->topic_name = topic_name;
//
//		this->publisher = n.advertise<std_msgs::String>(this->topic_name, 1);
//
//		event_target = boost::bind(	&RosEventSink::send_event, this, _1);
//	}
//
//	~RosEventSink() {
//		std::cout << "RosEventSink::~RosEventSink()"<<std::endl;
//		this->publisher.shutdown();
//	}
//
//	void send_event(std::string event) {
//		std::cout << "RosEventSink::send_event()"<<std::endl;
//
//		std_msgs::String msg;
//		msg.data = event;
//		this->publisher.publish(msg);
//	}
//
//};






#endif
