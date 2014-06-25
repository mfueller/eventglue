/*
 * World.h
 *
 *  Created on: Jun 23, 2014
 *      Author: matthias
 */

#ifndef ROBINSON_H_
#define ROBINSON_H_

#include <boost/python.hpp>

#include <boost/function.hpp>
#include <boost/signals2.hpp>

//FIXME: remove this
#pragma GCC diagnostic ignored "-fpermissive"

template<class T>
class DataPortOutputPython: public boost::signals2::signal<void(T)> {
private:

	boost::python::object component;
	std::string portname;
	boost::python::object python_connector_object;
	boost::python::object python_callback_handle;

public:

	DataPortOutputPython() {

	}

	DataPortOutputPython(boost::python::object component,
			std::string portname) {
		this->component = component;
		this->portname = portname;

		python_connector_object = boost::python::object(boost::ref(this));

		python_callback_handle = python_connector_object.attr("callback");
		this->component.attr(portname.c_str()).attr("connect")(
				python_callback_handle);
	}

	void callback(T msg) {
		std::cout << "DataPortOutputPython::callback()" << std::endl;
		(*this)(msg);
	}

};

template<class T>
class DataPortInputPython: public boost::function<void(T)> {
public:

	boost::python::object component;
	std::string portname;
	DataPortInputPython() :
			component(0) {
		this->portname = "DEFAULT_PORTNAME";
	}

	DataPortInputPython(boost::python::object component, std::string portname) :
			boost::function<void(T)>(
					boost::bind(&DataPortInputPython::callback, this, _1)), component(
					0) {
		this->component = component; //.attr(portname.c_str());
		this->portname = portname;
	}

	void callback(T msg) {
		try {
			component.attr(portname.c_str())(msg);
		} catch (boost::python::error_already_set) {
			PyErr_Print();
		}

	}
};

class PythonEventGlue {

public:

	template<typename MY_TYPE>
	static DataPortInputPython<MY_TYPE>& dataPortInputPython(
			boost::python::object* object, std::string portname) {
		try {
			DataPortInputPython<MY_TYPE>* port =
					new DataPortInputPython<MY_TYPE>(*object, portname);

			return *port;
		} catch (boost::python::error_already_set) {
			PyErr_Print();
		}
	}

	template<typename MY_TYPE>
	static DataPortOutputPython<MY_TYPE>& dataPortOutputPython(
			boost::python::object* object, std::string portname) {
		try {
			DataPortOutputPython<MY_TYPE>* port = new DataPortOutputPython<
					MY_TYPE>(*object, portname);

			return *port;
		} catch (boost::python::error_already_set) {
			PyErr_Print();
		}
	}

};

#endif /* WORLD_H_ */
