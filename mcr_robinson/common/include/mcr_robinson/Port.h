#ifndef EVENTGLUE_PORT_H_
#define EVENTGLUE_PORT_H_


#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>

#define PORT_SOURCE(CMD) \
		CMD

#define PORT_SINK(CLASS, OBJECT) \
		boost::bind(CLASS, OBJECT, _1)

template <class T>
class PortSink
{
public:
    typedef boost::function<void (T)> type;
};


template <class T>
class PortSource
{
public:
    typedef boost::signals2::signal<void (T)> type;

};


template <class T>
inline typename PortSource<T>::type& operator>>(typename PortSource<T>::type& lhs, const typename PortSink<T>::type& rhs) {
	lhs.connect(rhs);
	return lhs;
};



#endif
