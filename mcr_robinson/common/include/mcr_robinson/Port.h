#ifndef EVENTGLUE_PORT_H_
#define EVENTGLUE_PORT_H_


#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>

#define DATAPORT_OUTPUT(CMD) \
		CMD

#define DATAPORT_INPUT(CLASS, OBJECT) \
		boost::bind(CLASS, OBJECT, _1)


#define DataPortInput(type_def, name) \
		void dataport_input_##name(type_def name)

#define DataPortOutput(type_def, name) \
		DataPortOutput<type_def>::type dataport_output_##name





template <class T>
class DataPortInput
{
public:
    typedef boost::function<void (T)> type;
};


template <class T>
class DataPortOutput{
public:
    typedef boost::signals2::signal<void (T)> type;

};


template <class T>
inline typename DataPortOutput<T>::type& operator>>(typename DataPortOutput<T>::type& lhs, const typename DataPortInput<T>::type& rhs) {
	lhs.connect(rhs);
	return lhs;
};



#endif
