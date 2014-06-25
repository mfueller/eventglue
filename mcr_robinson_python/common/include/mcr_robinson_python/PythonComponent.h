/*
 * World.h
 *
 *  Created on: Jun 23, 2014
 *      Author: matthias
 */

#ifndef ROBINSON_PYTHON_COMPONENT_H_
#define ROBINSON_PYTHON_COMPONENT_H_

#include "Robinson.h"

class PythonComponentWrapper {
protected:
	boost::python::object* component;

public:
	PythonComponentWrapper(boost::python::object* component) {
		this->component = component;
	}

	void update() {
		try {
			component->attr("update")();
		} catch (boost::python::error_already_set) {
			PyErr_Print();
		}
	}

	void init() {
		try {
			component->attr("init")();
		} catch (boost::python::error_already_set) {
			PyErr_Print();
		}
	}

	void shutdown() {
		try {
			component->attr("shutdown")();
		} catch (boost::python::error_already_set) {
			PyErr_Print();
		}
	}
};

#endif /* ROBINSON_PYTHON_COMPONENT_H_ */
