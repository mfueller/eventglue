#include "mcr_robinson_hello_world/HelloWorldImpl.h"

#include <iostream>

#include <std_msgs/String.h>

#include "ros/ros.h"

#include "mcr_robinson_ros/RosEventGlue.h"

#include "mcr_robinson/ComponentContainer.h"

#include "mcr_robinson_python/Robinson.h"
#include "mcr_robinson_python/RobinsonPythonInterpreter.h"
#include "mcr_robinson_python/PythonComponent.h"

#define DATAPORT_INPUT_PYTHON(TYPE, COMPONENT, PORTNAME) \
	PythonEventGlue::dataPortInputPython<TYPE>(COMPONENT, PORTNAME)

#define DATAPORT_OUTPUT_PYTHON(TYPE, COMPONENT, PORTNAME) \
	PythonEventGlue::dataPortOutputPython<TYPE>(COMPONENT, PORTNAME)

int main(int argc, char *argv[]) {

	ros::init(argc, argv, "hello_world_node");
	ros::NodeHandle n("~");

	RobinsonPythonInterpreter* pythonInterpreter =
			new RobinsonPythonInterpreter();

	// which component should be loaded
	boost::python::object* py_hello_world = pythonInterpreter->loadComponent(
			"HelloWorld", "mcr_robinson_hello_world.HelloWorldComponent");

	// connect the ports
	DATAPORT_OUTPUT_ROS(std_msgs::String, std::string, "pin_name").connect(
			DATAPORT_INPUT_PYTHON(std::string, py_hello_world, "pin_name")
	);

	DATAPORT_OUTPUT_PYTHON(std::string, py_hello_world, "pout_answer").connect(
			DATAPORT_INPUT_ROS(std_msgs::String, std::string, "pout_answer")
	);

	// we need a wrapper for the ComponentContainer
	PythonComponentWrapper* compWrapper = new PythonComponentWrapper(
			py_hello_world);

	ComponentContainer<PythonComponentWrapper>* container =
			new ComponentContainer<PythonComponentWrapper>(compWrapper);

	// Connect events to container
	EVENT_OUTPUT_ROS("event_in", "e_start").connect(
			EVENT_INPUT(&ComponentContainer<PythonComponentWrapper>::eventport_input_start, container)
	);

	EVENT_OUTPUT_ROS("event_in", "e_stop").connect(
			EVENT_INPUT(&ComponentContainer<PythonComponentWrapper>::eventport_input_stop, container)
	);

	//Connect data ports to container

	// trigger update event on incomming data
	DataPortEvent<std::string>* data_trigger = new DataPortEvent<std::string>(
			EVENT_INPUT(
					&ComponentContainer<PythonComponentWrapper>::update_on_data,
					container));

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
	delete compWrapper;
	delete data_trigger;

	return 0;
}

//python = new RobinsonPythonInterpreter();

