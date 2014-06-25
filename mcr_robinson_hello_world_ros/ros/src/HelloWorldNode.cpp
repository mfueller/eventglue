
#include "mcr_robinson_hello_world/HelloWorldImpl.h"

#include <iostream>

#include <std_msgs/String.h>

#include "ros/ros.h"

#include "mcr_robinson_ros/RosEventGlue.h"

#include "mcr_robinson/ComponentContainer.h"

int main(int argc, char *argv[]) {

	ros::init(argc, argv, "hello_world_node");
	ros::NodeHandle n("~");

	mcr_robinson::helloworld::IHelloWorld* hello_world =
			new mcr_robinson::helloworld::HelloWorldImpl();


	// Connect ports from hello world component
	EVENT_OUTPUT(hello_world->eventport_output_done).connect(
			EVENT_INPUT_ROS("event_out", "e_done"));

	DATAPORT_OUTPUT_ROS(std_msgs::String, std::string, "pin_name").connect(
			DATAPORT_INPUT(&mcr_robinson::helloworld::IHelloWorld::dataport_input_name, hello_world)
	);

	std::cout << "empty: " << hello_world->dataport_output_answer.empty() << std::endl;
	DATAPORT_OUTPUT(hello_world->dataport_output_answer).connect(
			DATAPORT_INPUT_ROS(std_msgs::String, std::string, "pout_answer"));
	std::cout << "empty: " << hello_world->dataport_output_answer.empty() << std::endl;




	ComponentContainer<mcr_robinson::helloworld::IHelloWorld>* container =
				new ComponentContainer<mcr_robinson::helloworld::IHelloWorld>(hello_world);

	// Connect events to container
	EVENT_OUTPUT_ROS("event_in", "e_start").connect(
			EVENT_INPUT(&ComponentContainer<mcr_robinson::helloworld::IHelloWorld>::eventport_input_start, container)
	);

	EVENT_OUTPUT_ROS("event_in", "e_stop").connect(
			EVENT_INPUT(&ComponentContainer<mcr_robinson::helloworld::IHelloWorld>::eventport_input_stop, container)
	);

	//Connect data ports to container

	// trigger update event on incomming data
	DataPortEvent<std::string>* data_trigger = new DataPortEvent<std::string>(
					EVENT_INPUT(&ComponentContainer<mcr_robinson::helloworld::IHelloWorld>::update_on_data,container));

	DATAPORT_OUTPUT_ROS(std_msgs::String, std::string, "pin_name").connect(
			*data_trigger
	);


	// choose the operating mode
	container->setMode(ON_DATA_EVENT);
	//container->setMode(ON_UPDATE_EVENT);

	ros::Rate loop_rate(20);

	while (ros::ok()) {

		// call the update cycle every iteration
		container->update_cycle();

		ros::spinOnce();
		loop_rate.sleep();
	}




	delete container;
	delete hello_world;
	delete data_trigger;

	return 0;
}

//python = new RobinsonPythonInterpreter();
//py_hello_world = python->loadComponent("HelloWorld",
//		"mcr_robinson_hello_world.HelloWorldComponent");

