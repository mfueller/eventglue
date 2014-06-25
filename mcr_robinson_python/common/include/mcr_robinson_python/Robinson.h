/*
 * World.h
 *
 *  Created on: Jun 23, 2014
 *      Author: matthias
 */

#ifndef ROBINSON_H_
#define ROBINSON_H_


#include <boost/function.hpp>
#include <boost/signals2.hpp>

#include <boost/python.hpp>

//FIXME: remove this
#pragma GCC diagnostic ignored "-fpermissive"


//class Person {
//public:
//	std::string name;
//	int year;
//
//};

/*
struct Person_to_python_str
{
    static PyObject* convert(Person const& s)
      {
    	boost::python::object* o = new boost::python::object();

    	o->attr("name") = s.name;
    	o->attr("year") = s.year;

    	return o->ptr();
      }
};
*/


template<class T>
class DataPortOutputPython : public boost::signals2::signal<void (T)> {
private:

	boost::python::object component;
	std::string portname;
	boost::python::object python_connector_object;
	boost::python::object python_callback_handle;

public:

	DataPortOutputPython() {

	}

	DataPortOutputPython(boost::python::object component, std::string portname) {
		this->component = component;
		this->portname = portname;

		python_connector_object = boost::python::object(boost::ref(this));

		python_callback_handle = python_connector_object.attr("callback");
		this->component.attr(portname.c_str()).attr("connect")(python_callback_handle);
	}

	void callback(T msg) {
		std::cout << "DataPortOutputPython::callback()" << std::endl;
		(*this)(msg);
	}


};


template<class T>
class DataPortInputPython : public boost::function<void (T)> {
public:

	boost::python::object component;
	std::string portname;
	DataPortInputPython() : component(0) {
		this->portname = "DEFAULT_PORTNAME";
	}

	DataPortInputPython(boost::python::object component, std::string portname) :
		boost::function<void(T)>(boost::bind(&DataPortInputPython::callback, this, _1)), component(0) {
		this->component = component;//.attr(portname.c_str());
		this->portname = portname;
	}

	void callback(T msg) {
		component.attr(portname.c_str())(msg);
	}
};

#endif /* WORLD_H_ */
