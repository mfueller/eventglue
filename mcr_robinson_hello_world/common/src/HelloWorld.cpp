#include "mcr_robinson_hello_world/HelloWorld.h"

namespace mcr_robinson {
namespace helloworld {

int counter = 0;

HelloWorld::HelloWorld() {
	state = STARTED;
	std::cout << "HelloWorld started" << std::endl;
}

HelloWorld::~HelloWorld() {
}


bool HelloWorld::init() {
	this->state = IDLE;
	std::cout << "HelloWorld init done" << std::endl;
	return true;
}

void HelloWorld::update() {

	if (this->state == ACTIVE) {
		std::stringstream ss;
		ss << "Hello " << this->name << " " << counter++ << std::endl;
		std::cout << " HelloWorld sending: " << ss.str() << std::endl;
		dataport_output_answer(ss.str());
		eventport_output_done();
	}
}

void HelloWorld::shutdown() {
	this->state = SHUTDOWN;
}

void HelloWorld::eventport_input_start() {
	this->state = ACTIVE;
}

void HelloWorld::eventport_input_stop() {
	this->state = IDLE;
}

void HelloWorld::eventport_input_update() {
	this->update();
}

void HelloWorld::dataport_input_name(std::string name) {
	this->name = name;
	std::cout << "HelloWorld got name " << name << std::endl;
}


} /* namespace manipulation */
} /* namespace mir_industrial */


