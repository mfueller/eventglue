
#include "HelloWorldNode.h"

#include "mcr_robinson_hello_world/HelloWorldImpl.h"

#include <iostream>

#include <std_msgs/String.h>

#include "ros/ros.h"

#include "mcr_robinson_ros/RosEventGlue.h"

HelloWorldNode::HelloWorldNode()
{

	python = new RobinsonPythonInterpreter();
	//boost::python::exec("import libmcr_robinson_python as robinson", nm);


	try {
		//boost::python::exec("from mcr_robinson_hello_world.HelloWorldComponent import HelloWorld", python->main_dict());
		//boost::python::object pythonComponent = eval("HelloWorld()", python->main_dict());


	} catch (error_already_set) {
		PyErr_Print();
	}

    hello_world = new mcr_robinson::helloworld::HelloWorldImpl();

    py_hello_world = python->loadComponent("HelloWorld", "mcr_robinson_hello_world.HelloWorldComponent");

    EVENT_OUTPUT_ROS("event_in", "e_start")
    .connect(
        EVENT_INPUT(&mcr_robinson::helloworld::IHelloWorld::eventport_input_start, hello_world)
    );

    EVENT_OUTPUT_ROS("event_in", "e_stop")
    .connect(
        EVENT_INPUT(&mcr_robinson::helloworld::IHelloWorld::eventport_input_stop, hello_world)
    );

    EVENT_OUTPUT(hello_world->eventport_output_done)
    .connect(
        EVENT_INPUT_ROS("event_out", "e_done")
    );

    DATAPORT_OUTPUT_ROS(std_msgs::String, std::string, "pin_name")
    .connect(
        DATAPORT_INPUT(&mcr_robinson::helloworld::IHelloWorld::dataport_input_name, hello_world)
    );

    DATAPORT_OUTPUT(hello_world->dataport_output_answer)
    .connect(
        DATAPORT_INPUT_ROS(std_msgs::String, std::string, "pout_answer")
    );



    // trigger update event on incomming data
    DataPortEvent<std::string> *data_trigger = new DataPortEvent<std::string>(
        EVENT_INPUT(&mcr_robinson::helloworld::IHelloWorld::eventport_input_update, hello_world));

    DATAPORT_OUTPUT_ROS(std_msgs::String, std::string, "pin_name")
    .connect(
        *data_trigger
    );
    //FIXME: delete data_trigger after shutdown



    std::cout << "HelloWorldNode constructed" << std::endl;

}



HelloWorldNode::~HelloWorldNode()
{
    delete hello_world;
    delete python;
}

void HelloWorldNode::update()
{
    // call all used components
    // will be replaced by the scheduler
    //this->hello_world->update();
}

void HelloWorldNode::init()
{
    // call all used components
    // will be replaced by the scheduler
    this->hello_world->init();
}


void HelloWorldNode::shutdown()
{
    // call all used components
    // will be replaced by the scheduler
    this->hello_world->shutdown();
}


int main(int argc, char *argv[])
{

    ros::init(argc, argv, "hello_world_node");
    ros::NodeHandle n("~");

    HelloWorldNode hello_world_node;

    // will be replaced by scheduler
    ros::Rate loop_rate(20);

    hello_world_node.init();

    while (ros::ok()) {
        hello_world_node.update();
        ros::spinOnce();
        loop_rate.sleep();
    }

    hello_world_node.shutdown();

    return 0;
}


