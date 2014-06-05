#ifndef HELLO_WORLD_H_
#define HELLO_WORLD_H_

#include <string>

#include "mcr_robinson/EventGlue.h"

#include <kdl/jntarray.hpp>


namespace mcr_robinson {
namespace helloworld {

class HelloWorld {
protected:

	enum State {STARTED, IDLE, ACTIVE, SHUTDOWN};

	State state;

	std::string name;

public:

	HelloWorld();

	virtual ~HelloWorld();

	EventPortOutput(done);

	EventPortInput(start);

	EventPortInput(stop);

	EventPortInput(update);

	DataPortInput(std::string, name);

	DataPortOutput(std::string, answer);

	bool init();

	void update();

	void shutdown();
};

} /* namespace mcr_robinson */
} /* namespace helloworld */

#endif /* HELLO_WORLD_H_ */
