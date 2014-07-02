package mcr.robinson;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import mcr.robinson.annotations.DataInputPort;

public class DataInputSlot<OWN_TYPE> implements IDataSlot<OWN_TYPE> {
	
	Object object;
	String portName;
	Method method;
	public DataInputSlot(Object object, String portName) {
		this.portName = portName;
		this.object = object;
		
		method = new PortUtils().dataMethod(object, portName);
		
	}
	
	public DataInputSlot(Object object, Method m) {
		this.object = object;
		
		this.method = m;
	}
	
	
	@Override
	public void receive(OWN_TYPE msg) {
		try {
			this.method.invoke(this.object, msg);
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (IllegalArgumentException e) {
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			e.printStackTrace();
		}
	}
	
}
