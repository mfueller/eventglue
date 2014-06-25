#include "mcr_robinson_hello_world/HelloWorldImpl.h"

namespace mcr_robinson {
namespace helloworld {

int counter = 0;

HelloWorldImpl::HelloWorldImpl() {
	std::cout << "HelloWorldImpl()" << std::endl;
}

HelloWorldImpl::~HelloWorldImpl() {
	std::cout << "~HelloWorldImpl()" << std::endl;
}

void HelloWorldImpl::update() {
	std::cout << "HelloWorldImpl::update()" << std::endl;

	std::stringstream ss;
	ss << "Hello " << this->name << " " << counter++ << std::endl;
	std::cout << " HelloWorldImpl sending: " << ss.str() << std::endl;

	dataport_output_answer(ss.str());
	eventport_output_done();

}

bool HelloWorldImpl::init() {
	std::cout << "HelloWorldImpl::init()" << std::endl;
	return true;
}

void HelloWorldImpl::shutdown() {
	std::cout << "HelloWorldImpl::shutdown()" << std::endl;

}

void HelloWorldImpl::dataport_input_name(std::string name) {
	std::cout << "HelloWorldImpl::dataport_input_name()" << std::endl;

	this->name = name;
	std::cout << "HelloWorld got name " << name << std::endl;
}

} /* namespace manipulation */
} /* namespace mir_industrial */

