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

#include "mcr_robinson/message_converter/MessageConverter.h"
#include "mcr_robinson_ros/message_converter/ros_msgs.h"

#define DATAPORT_OUTPUT_ROS(ROS_TOPIC, IN_TOPIC, TOPIC) \
		RosEventGlue::port_from_ros_topic<ROS_TOPIC, IN_TOPIC>(TOPIC)

#define DATAPORT_INPUT_ROS(ROS_TOPIC, IN_TOPIC, TOPIC) \
		RosEventGlue::port_to_ros_topic<ROS_TOPIC, IN_TOPIC>(TOPIC)

template <typename ROS_TYPE, typename MY_TYPE>
class DataPortInputROS : public DataPortInput<MY_TYPE>::type {
	std::string topic_name;
	ros::Publisher publisher;

public:

	//typename PortSink<MY_TYPE>::type ros_publisher;

	DataPortInputROS(std::string topic_name) :
		DataPortInput<MY_TYPE>::type(boost::bind(&DataPortInputROS<ROS_TYPE, MY_TYPE>::callback, this, _1)) {
		std::cout << "RosPortSink::RosPortSink(topic): advertises: " << topic_name << std::endl;

		ros::NodeHandle n("~");
		this->topic_name = topic_name;
		this->publisher = n.advertise<ROS_TYPE>(this->topic_name, 1);
		//ros_publisher = boost::bind(&RosPortSink<ROS_TYPE, MY_TYPE>::callback, this, _1);

	}

	~DataPortInputROS() {
		std::cout << "RosOutPort::~RosOutPort()"<<std::endl;
		this->publisher.shutdown();
	}

	void callback(MY_TYPE event) {
		ROS_TYPE msg = MessageConverter<MY_TYPE, ROS_TYPE>::convert(event);
		this->publisher.publish(msg);
	}

};


template <typename ROS_TYPE, typename MY_TYPE>
class DataPortOutputROS : public DataPortOutput<MY_TYPE>::type {
	std::string topic_name;
	ros::Subscriber subscriber;
public:

	//typename PortSource<MY_TYPE>::type ros_topic_signal;

	DataPortOutputROS(std::string topic_name) {
		std::cout << "RosInPort::RosInPort(topic, name): registered to: " << topic_name << std::endl;
		ros::NodeHandle n("~");
		this->topic_name = topic_name;
		this->subscriber = n.subscribe(this->topic_name, 1,
				&DataPortOutputROS::event_callback, this);
	}

	~DataPortOutputROS() {
		std::cout << "RosInPort::~RosInPort()"<<std::endl;
		this->subscriber.shutdown();
	}

	void event_callback(ROS_TYPE event) {
		MY_TYPE msg_new = MessageConverter<ROS_TYPE, MY_TYPE>::convert(event);
		(*this)(msg_new);
	}


};

#endif
