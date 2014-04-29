#ifndef ROS_MSGS_CONVERTER_H_
#define ROS_MSGS_CONVERTER_H_

#include <string.h>

#include <vector>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <kdl/jntarray.hpp>


template <>
inline std::string MessageConverter<std_msgs::String, std::string>::convert(std_msgs::String msg) {
	std::string msg_new;
	msg_new = msg.data;
	return msg_new;
}
template <>
inline std_msgs::String MessageConverter<std::string, std_msgs::String>::convert(std::string msg) {
	std_msgs::String msg_new;
	msg_new.data = msg;
	return msg_new;
}



template <>
inline KDL::JntArray MessageConverter<sensor_msgs::JointState, KDL::JntArray>::convert(sensor_msgs::JointState msg) {
	KDL::JntArray msg_new(msg.position.size());

	for (std::size_t i = 0; i < msg.position.size(); i++) {
		msg_new.data[i] = msg.position[i];
	}
	return msg_new;
}

template <>
inline sensor_msgs::JointState MessageConverter<KDL::JntArray, sensor_msgs::JointState>::convert(KDL::JntArray msg) {
	sensor_msgs::JointState msg_new;
	msg_new.position.resize(msg.data.rows());

	for (std::size_t i = 0; i < msg.data.rows(); i++) {
		msg_new.position[i] = msg.data[i];
	}

	return msg_new;
}



template <>
inline std::vector<std::string> MessageConverter<sensor_msgs::JointState, std::vector<std::string> >::convert(sensor_msgs::JointState msg) {
	std::vector<std::string> msg_new(msg.position.size());

	for (std::size_t i = 0; i < msg.position.size(); i++) {
		msg_new[i] = msg.name[i];
	}
	return msg_new;
}

template <>
inline sensor_msgs::JointState MessageConverter<std::vector<std::string>, sensor_msgs::JointState>::convert(std::vector<std::string> msg) {
	sensor_msgs::JointState msg_new;
	msg_new.position.resize(msg.size());

	for (std::size_t i = 0; i < msg.size(); i++) {
		msg_new.name[i] = msg[i];
	}

	return msg_new;
}


#endif
