#ifndef EVENTGLUE_PORT_H_
#define EVENTGLUE_PORT_H_


#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signal.hpp>

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
    typedef boost::signal<void (T)> type;

    /*
    typename InPort<T>::type& operator+= (typename InPort<T>::type const& rhs) {
		this->connect(rhs);
		return rhs;
	};
	*/
};




#endif
