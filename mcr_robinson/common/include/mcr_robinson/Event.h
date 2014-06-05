#ifndef EVENTGLUE_EVENT_H_
#define EVENTGLUE_EVENT_H_

#include "Port.h"

#include <string.h>

#define EVENT_INPUT(CLASS, OBJECT) \
		boost::bind(CLASS, OBJECT)

#define EVENT_OUTPUT(CMD) \
		CMD

typedef boost::function<void ()> 			EventPortInput ;

typedef boost::signals2::signal<void ()> 	EventPortOutput ;


#define EventPortInput(name) \
		void eventport_input_##name()

#define EventPortOutput(name) \
		EventPortOutput eventport_output_##name


inline EventPortOutput& operator>>(EventPortOutput& lhs, EventPortInput const& rhs) {
	lhs.connect(rhs);
	return lhs;
}



#endif
