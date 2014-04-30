#ifndef EVENTGLUE_EVENT_H_
#define EVENTGLUE_EVENT_H_

#include "Port.h"

#include <string.h>

#define EVENT_SINK(CLASS, OBJECT) \
		boost::bind(CLASS, OBJECT, _1)

#define EVENT_SOURCE(CMD) \
		CMD

typedef InPort<std::string>::type EventTarget;
typedef OutPort<std::string>::type EventSource;


inline EventSource& operator>>(EventSource& lhs, EventTarget const& rhs) {
	lhs.connect(rhs);
	return lhs;
}



#endif
