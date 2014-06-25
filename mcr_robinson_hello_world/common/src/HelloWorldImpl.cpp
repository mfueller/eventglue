#include "mcr_robinson_hello_world/HelloWorldImpl.h"

namespace mcr_robinson
{
namespace helloworld
{

int counter = 0;

HelloWorldImpl::HelloWorldImpl()
{
    state = STARTED;
    std::cout << "HelloWorld started" << std::endl;
}

HelloWorldImpl::~HelloWorldImpl()
{
}


bool HelloWorldImpl::init()
{
    this->state = IDLE;
    std::cout << "HelloWorld init done" << std::endl;
    return true;
}

void HelloWorldImpl::update()
{

    if (this->state == ACTIVE) {
        std::stringstream ss;
        ss << "Hello " << this->name << " " << counter++ << std::endl;
        std::cout << " HelloWorld sending: " << ss.str() << std::endl;
        dataport_output_answer(ss.str());
        eventport_output_done();
    }
}

void HelloWorldImpl::shutdown()
{
    this->state = SHUTDOWN;
}

void HelloWorldImpl::eventport_input_start()
{
    this->state = ACTIVE;
}

void HelloWorldImpl::eventport_input_stop()
{
    this->state = IDLE;
}

void HelloWorldImpl::eventport_input_update()
{
    this->update();
}

void HelloWorldImpl::dataport_input_name(std::string name)
{
    this->name = name;
    std::cout << "HelloWorld got name " << name << std::endl;
}


} /* namespace manipulation */
} /* namespace mir_industrial */


