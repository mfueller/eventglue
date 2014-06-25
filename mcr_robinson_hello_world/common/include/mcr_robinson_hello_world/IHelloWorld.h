#ifndef HELLO_WORLD_H_
#define HELLO_WORLD_H_

#include <string>

#include "mcr_robinson/EventGlue.h"

namespace mcr_robinson
{
namespace helloworld
{

class IHelloWorld
{
    protected:

        std::string name;

    public:

        IHelloWorld() {}

        virtual ~IHelloWorld() {}

        EventPortOutput(done);

        DataPortInput(std::string, name) = 0;

        DataPortOutput(std::string, answer);

        virtual bool init() = 0;

        virtual void update() = 0;

        virtual void shutdown() = 0;
};

} /* namespace mcr_robinson */
} /* namespace helloworld */

#endif /* HELLO_WORLD_H_ */
