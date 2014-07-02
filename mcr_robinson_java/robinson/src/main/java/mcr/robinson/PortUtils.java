package mcr.robinson;

import java.lang.reflect.Method;
import java.util.Vector;

import mcr.robinson.annotations.DataInputPort;
import mcr.robinson.annotations.EventInputPort;

public class PortUtils {

	
	public Method eventMethod(Class<?> classdef, String portname, String event) {

		Vector<Class> classes = new Vector<Class>();

		classes.add(classdef);

		Class[] iClasses = classdef.getInterfaces();
		for (Class c : iClasses) {
			classes.add(c);
		}
		Class sClass = classdef.getSuperclass();
		classes.add(sClass);

		for (Class interfaceClass : classes) {
			for (Method m : interfaceClass.getMethods()) {
				if (m.isAnnotationPresent(EventInputPort.class)) {
					EventInputPort port = m.getAnnotation(EventInputPort.class);

					if (port.name().equals(portname) && port.event().equals(event)) {
						return m;
					}
				}
			}
		}

		System.err.println("No Port " + portname + " and/or event " + event + " found in class " + classdef);
		return null;
	}
	
	
	public Method dataMethod(Object object, String portname) {

		Vector<Class> classes = new Vector<Class>();

		classes.add(object.getClass());

		Class[] iClasses = object.getClass().getInterfaces();
		for (Class c : iClasses) {
			classes.add(c);
		}
		Class sClass = object.getClass().getSuperclass();
		classes.add(sClass);

		for (Class interfaceClass : classes) {
			for (Method m : interfaceClass.getMethods()) {
				if (m.isAnnotationPresent(DataInputPort.class)) {
					DataInputPort port = m.getAnnotation(DataInputPort.class);

					if (port.name().equals(portname)) {
						return m;
					}
				}
			}
		}

		System.err.println("No Port " + portname + " found in object " + object);
		return null;
	}

	DataInputPort getDataInputPort(Class<?> classInterface, String portname) {

		for (Method m : classInterface.getMethods()) {
			if (m.isAnnotationPresent(DataInputPort.class)) {
				DataInputPort port = m.getAnnotation(DataInputPort.class);

				if (port.name().equals(portname)) {
					return port;
				}
			}
		}
		return null;
	}

	EventInputPort getEventInputPort(Class<?> classInterface, String portname, String event) {

		for (Method m : classInterface.getMethods()) {
			if (m.isAnnotationPresent(EventInputPort.class)) {
				EventInputPort port = m.getAnnotation(EventInputPort.class);

				if (port.name().equals(portname) && port.event().equals(event)) {
					return port;
				}
			}
		}
		return null;
	}

}
