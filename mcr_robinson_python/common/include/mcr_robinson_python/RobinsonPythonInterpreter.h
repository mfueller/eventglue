/*
 * RobinsonPythonInterpreter.h
 *
 *  Created on: Jun 24, 2014
 *      Author: matthias
 */

#ifndef ROBINSONPYTHONINTERPRETER_H_
#define ROBINSONPYTHONINTERPRETER_H_

#include <boost/python.hpp>

#include <sstream>

using namespace boost::python;

class RobinsonPythonInterpreter {
protected:
	object* _module;
	object _main_module;
	object _main_dict;
public:
	RobinsonPythonInterpreter() {
		Py_Initialize();

		_module = new object(handle<>(borrowed(PyImport_AddModule("__main__"))));
		_main_module = import("__main__");
		_main_dict = _main_module.attr("__dict__");

	}

	virtual ~RobinsonPythonInterpreter() {
		Py_Finalize();
	}

	object& main_dict() {
		return _main_dict;
	}

	object* loadComponent(std::string name, std::string ns) {
		std::stringstream ss_ns;
		ss_ns << "import " << ns;

		std::stringstream ss_comp;
		ss_comp << ns << "." << name << "()";;

		try {

			boost::python::exec(ss_ns.str().c_str(), this->main_dict());

			boost::python::object* py_obj = new boost::python::object();

			*py_obj = eval(ss_comp.str().c_str(), this->main_dict());

			return py_obj;

		} catch (error_already_set) {
			PyErr_Print();
		}

		return 0;

	}
};

#endif /* ROBINSONPYTHONINTERPRETER_H_ */
