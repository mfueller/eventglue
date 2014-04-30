#ifndef EVENTGLUE_PORT_H_
#define EVENTGLUE_PORT_H_


#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>

template <class T>
class InPort
{
public:
    typedef boost::function<void (T)> type;
};


template <class T>
class OutPort
{
public:
    typedef boost::signals2::signal<void (T)> type;

};


template <class T>
inline typename OutPort<T>::type& operator>>(typename OutPort<T>::type& lhs, const typename InPort<T>::type& rhs) {
	lhs.connect(rhs);
	return lhs;
};



#endif
