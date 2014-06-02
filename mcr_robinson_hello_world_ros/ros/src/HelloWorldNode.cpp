#include "HelloWorldNode.h"


#include <iostream>

#include <std_msgs/String.h>

#include "ros/ros.h"

#include "mcr_robinson_ros/RosEventGlue.h"

HelloWorldNode::HelloWorldNode() {


	hello_world = new mcr_robinson::helloworld::HelloWorld();

	ROS_EVENT_SOURCE("event_in") >>
			EVENT_SINK(&mcr_robinson::helloworld::HelloWorld::event_in, hello_world);

	EVENT_SOURCE(hello_world->event_out) >>
			ROS_EVENT_SINK("event_out");

	ROS_PORT_SOURCE (std_msgs::String, std::string, "pin_name")
				.connect(
						PORT_SINK(&mcr_robinson::helloworld::HelloWorld::pin_name, hello_world)
						);

	PORT_SOURCE(hello_world->pout_answer)
				.connect(
						ROS_PORT_SINK(std_msgs::String, std::string, "pout_answer")
						);

	std::cout << "HelloWorldNode constructed" << std::endl;

}



HelloWorldNode::~HelloWorldNode() {
	delete hello_world;
}

void HelloWorldNode::update() {
	// call all used components
	// will be replaced by the scheduler
	this->hello_world->update();
}

void HelloWorldNode::init() {
	// call all used components
	// will be replaced by the scheduler
	this->hello_world->init();
}


void HelloWorldNode::shutdown() {
	// call all used components
	// will be replaced by the scheduler
	this->hello_world->shutdown();
}


int main( int argc, char* argv[] )
{

	ros::init(argc, argv, "hello_world_node");
	ros::NodeHandle n("~");

	HelloWorldNode hello_world_node;

	// will be replaced by scheduler
	ros::Rate loop_rate(20);

	hello_world_node.init();

	while(ros::ok()) {
		hello_world_node.update();
		ros::spinOnce();
		loop_rate.sleep();
	}

	hello_world_node.shutdown();


	return 0;
}


