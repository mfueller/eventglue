package helloworld;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Vector;

import mcr.robinson.DataOutputPort;
import mcr.robinson.EventOutputPort;
import mcr.robinson.annotations.DataInputPort;
import mcr.robinson.annotations.DataOutputPortInfo;
import mcr.robinson.annotations.EventInputPort;
import mcr.robinson.annotations.EventOutputPortInfo;
import mcr.robinson.annotations.Init;
import mcr.robinson.annotations.Shutdown;
import mcr.robinson.annotations.Update;





public abstract class IHelloWorld {

	@DataOutputPortInfo(name="pout_answer", type = String.class)
	public DataOutputPort<String> pout_answer = new DataOutputPort<String>();
	
	@EventOutputPortInfo(name="event_out", event="e_done")
	public EventOutputPort event_out_done = new EventOutputPort();
			
	@DataInputPort(name="name")
	public abstract void pin_name(String name);
	
	@EventInputPort(name="event_in", event="hello")
	public abstract void event_in_hello();
	
	@Update
	public abstract void update();
	
	@Init
	public abstract void init();
	
	@Shutdown
	public abstract void shutdown();
	
}
