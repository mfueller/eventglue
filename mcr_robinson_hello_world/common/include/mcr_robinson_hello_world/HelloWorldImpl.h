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

        std::string name;

public:

        HelloWorldImpl();

        virtual ~HelloWorldImpl();

        // output ports shouldnt be added a second time
        //EventPortOutput(done);

        DataPortInput(std::string, name);

        // output ports shouldnt be added a second time
        //DataPortOutput(std::string, answer);

        virtual bool init();

        virtual void update();

        virtual void shutdown();
};

} /* namespace mcr_robinson */
} /* namespace helloworld */

#endif /* HELLO_WORLD_IMPL_H_ */
