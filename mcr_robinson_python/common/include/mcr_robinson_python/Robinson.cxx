/*
 * World.h
 *
 *  Created on: Jun 23, 2014
 *      Author: matthias
 */


#include <boost/python.hpp>

#include <boost/function.hpp>
#include <boost/signals2.hpp>

using namespace boost::python;

#include "Robinson.h"

BOOST_PYTHON_MODULE(mcr_robinson_python)
{

    class_<DataPortOutputPython<std::string>, boost::noncopyable>("DataPortOutputPython_String")
            .def("callback", &DataPortOutputPython<std::string>::callback)
        ;

    class_<DataPortInputPython<std::string>, boost::noncopyable>("DataPortInputPython_String")
                  .def("callback", &DataPortInputPython<std::string>::callback)
              ;

//    class_<DataPortInputPython<Person>, boost::noncopyable>("DataPortInputPython_Person")
//                  .def("callback", &DataPortInputPython<Person>::callback)
//              ;

    //boost::python::to_python_converter<Person, Person_to_python_str>();
    //class_<Person>("Person")
    //		.def_readwrite("name", &Person::name)
    //		.def_readwrite("year", &Person::year);
}


