#include "mcr_robinson_hello_world/HelloWorld.h"

namespace mcr_robinson {
namespace helloworld {


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
		ss << "Hello " << this->name << std::endl;
		std::cout << "HelloWorld sending: " << ss.str() << std::endl;
		pout_answer(ss.str());

	}
}

void HelloWorld::shutdown() {
	this->state = SHUTDOWN;
}

void HelloWorld::event_in(std::string event) {
	std::cout << "HelloWorld Receiving event " << event << std::endl;

	if (event.compare("e_start") == 0) {
		this->state = ACTIVE;
		std::cout << "HelloWorld active" << std::endl;
	} else if (event.compare("e_stop") == 0) {
		this->state = IDLE;
		std::cout << "HelloWorld idle" << std::endl;
	}
}

void HelloWorld::pin_name(std::string name) {
	this->name = name;
	std::cout << "HelloWorld got name " << name << std::endl;
}



} /* namespace manipulation */
} /* namespace mir_industrial */


