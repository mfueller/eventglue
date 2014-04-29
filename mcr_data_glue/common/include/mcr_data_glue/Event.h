#ifndef EVENTGLUE_EVENT_H_
#define EVENTGLUE_EVENT_H_

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>

#include <string.h>

#define EVENT_SINK(CLASS, OBJECT) \
		boost::bind(CLASS, OBJECT, _1)

#define EVENT_SOURCE(CMD) \
		CMD


typedef boost::function<void (std::string)> EventTarget;
typedef boost::signals2::signal<void (std::string)> EventSource;





inline EventSource& operator>>(EventSource& lhs, EventTarget const& rhs) {
	lhs.connect(rhs);
	return lhs;
}



#endif
