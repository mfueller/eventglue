#ifndef HELLO_WORLD_NODE_H
#define HELLO_WORLD_NODE_H

#include "mcr_robinson_python/RobinsonPythonInterpreter.h"

#include "ros/ros.h"

#include "mcr_robinson_hello_world/HelloWorld.h"

#include "mcr_robinson/EventGlue.h"

class HelloWorldNode
{
    protected:

	RobinsonPythonInterpreter* python;

	boost::python::object* py_hello_world;

    public:
        mcr_robinson::helloworld::HelloWorld *hello_world;

        HelloWorldNode();

        virtual ~HelloWorldNode();

        void update();

        void init();

        void shutdown();

};

#endif /* YOUBOTGRIPPERCONTROLLERNODE_H_ */
