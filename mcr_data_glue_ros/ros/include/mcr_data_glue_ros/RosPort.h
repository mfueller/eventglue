#ifndef EVENTGLUE_PORT_ROS_H_
#define EVENTGLUE_PORT_ROS_H_

#include <string.h>
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

#define ROS_PORT_SOURCE(ROS_TOPIC, IN_TOPIC, TOPIC) \
		RosEventGlue::instance.port_from_ros_topic<ROS_TOPIC, IN_TOPIC>(TOPIC)


#define PORT_SOURCE(CMD) \
		CMD

#define PORT_SINK(CLASS, OBJECT) \
		boost::bind(CLASS, OBJECT, _1)


// non template class for storing pointer into vector
class RosPort {

};


template <typename ROS_TYPE, typename MY_TYPE>
class RosPortSink : public RosPort {
	std::string topic_name;
	ros::Publisher publisher;

public:

	typename InPort<MY_TYPE>::type ros_publisher;

	RosPortSink(std::string topic_name) {
		std::cout << "RosPortSink::RosPortSink(topic): advertises: " << topic_name << std::endl;

		ros::NodeHandle n("~");
		this->topic_name = topic_name;
		this->publisher = n.advertise<ROS_TYPE>(this->topic_name, 1);
		ros_publisher = boost::bind(&RosPortSink<ROS_TYPE, MY_TYPE>::callback, this, _1);

	}

	~RosPortSink() {
		std::cout << "RosOutPort::~RosOutPort()"<<std::endl;
		this->publisher.shutdown();
	}

	void callback(MY_TYPE event) {
		ROS_TYPE msg = MessageConverter<MY_TYPE, ROS_TYPE>::convert(event);
		this->publisher.publish(msg);
	}

};


template <typename ROS_TYPE, typename MY_TYPE>
class RosPortSource : public RosPort {
	std::string topic_name;
	ros::Subscriber subscriber;
public:

	typename OutPort<MY_TYPE>::type ros_topic_signal;

	RosPortSource(std::string topic_name) {
		std::cout << "RosInPort::RosInPort(topic, name): registered to: " << topic_name << std::endl;
		ros::NodeHandle n("~");
		this->topic_name = topic_name;
		this->subscriber = n.subscribe(this->topic_name, 1,
				&RosPortSource::event_callback, this);
	}

	~RosPortSource() {
		std::cout << "RosInPort::~RosInPort()"<<std::endl;
		this->subscriber.shutdown();
	}

	void event_callback(ROS_TYPE event) {
		MY_TYPE msg_new = MessageConverter<ROS_TYPE, MY_TYPE>::convert(event);
		this->ros_topic_signal(msg_new);
	}


};

#endif
