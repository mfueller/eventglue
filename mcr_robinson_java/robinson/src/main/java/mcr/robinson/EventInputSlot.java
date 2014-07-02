package mcr.robinson;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Vector;

import mcr.robinson.annotations.EventInputPort;

public class EventInputSlot implements IEventSlot {
	
	Object object;
	String portName;
	String event;
	Method method;
	
	public EventInputSlot(Object object, String portName, String event) {
		this.portName = portName;
		this.object = object;
		this.event = event;
		
		method = new PortUtils().eventMethod(object.getClass(), portName, event);
		
	}
	
	public EventInputSlot(Object object, Method m) {
		this.object = object;
		this.method = m;
	}
	
	
	
	@Override
	public void receive() {
		try {
			this.method.invoke(this.object);
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
	}
	
}
