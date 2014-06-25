#ifndef HELLO_WORLD_IMPL_H_
#define HELLO_WORLD_IMPL_H_

#include "IHelloWorld.h"

namespace mcr_robinson
{
namespace helloworld
{

class HelloWorldImpl : public IHelloWorld
{
    protected:

        enum State {STARTED, IDLE, ACTIVE, SHUTDOWN};

        State state;

        std::string name;

    public:

        HelloWorldImpl();

        virtual ~HelloWorldImpl();

        EventPortOutput(done);

        EventPortInput(start);

        EventPortInput(stop);

        EventPortInput(update);

        DataPortInput(std::string, name);

        DataPortOutput(std::string, answer);

        virtual bool init();

        virtual void update();

        virtual void shutdown();
};

} /* namespace mcr_robinson */
} /* namespace helloworld */

#endif /* HELLO_WORLD_H_ */
