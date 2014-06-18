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

inline EventPortOutput &operator>>(EventPortOutput &lhs, EventPortInput const &rhs)
{
    lhs.connect(rhs);
    return lhs;
}


template<class MY_TYPE>
class DataPortEvent : public DataPortInput<MY_TYPE>::type
{
    public:
        EventPortInput event;

        DataPortEvent(EventPortInput event) : event(event),
            DataPortInput<MY_TYPE>::type(boost::bind(&DataPortEvent<MY_TYPE>::callback, this, _1))
        {

        }

        void callback(MY_TYPE data)
        {
            event();
        }

};


#endif
