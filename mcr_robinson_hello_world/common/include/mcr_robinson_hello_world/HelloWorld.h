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

	EventSource event_out;

	void event_in(std::string event);

	void pin_name(std::string name);

	PortSource<std::string>::type pout_answer;


	bool init();

	void update();

	void shutdown();
};

} /* namespace mcr_robinson */
} /* namespace helloworld */

#endif /* HELLO_WORLD_H_ */
