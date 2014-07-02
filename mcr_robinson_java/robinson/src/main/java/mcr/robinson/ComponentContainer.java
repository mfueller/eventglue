package mcr.robinson;

import java.lang.reflect.Method;

import mcr.robinson.annotations.EventInputPort;
import mcr.robinson.annotations.EventOutputPortInfo;
import mcr.robinson.annotations.Init;
import mcr.robinson.annotations.Shutdown;
import mcr.robinson.annotations.Update;


public class ComponentContainer {

	public enum State {IDLE, ACTIVE}
	
	public enum Mode {CYCLIC, ON_EVENT}
	
	Object component;
	
	Class<?> interfaceClass;
	
	@EventOutputPortInfo(name="event_out", event="e_update")
	EventOutputPort event_update = new EventOutputPort();
	
	@EventOutputPortInfo(name="event_out", event="e_init")
	EventOutputPort event_init = new EventOutputPort();
	
	@EventOutputPortInfo(name="event_out", event="e_shutdown")
	EventOutputPort event_shutdown = new EventOutputPort();
	
	State state;
	Mode mode;
	boolean init;
	public ComponentContainer(Class<?> interfaceClass, Object component) {
		this.component = component;
		this.state = State.IDLE;
		this.init = false;
		this.mode = Mode.CYCLIC;
		this.interfaceClass = interfaceClass;
		
		for (Method m : interfaceClass.getMethods()) {
			
			if (m.isAnnotationPresent(Update.class)) {
				this.event_update.connect(new EventInputSlot(this.component, m));
			}
			if (m.isAnnotationPresent(Init.class)) {
				this.event_init.connect(new EventInputSlot(this.component, m));
			}
			if (m.isAnnotationPresent(Shutdown.class)) {
				this.event_shutdown.connect(new EventInputSlot(this.component, m));
			}
			
		}
	}


	@Override
	protected void finalize() throws Throwable {
		super.finalize();
		this.event_shutdown.emit();
	}
	
	public void setMode(Mode mode) {
		this.mode = mode;
	}
	
	protected void update() {
		if (this.state == State.ACTIVE) {
			this.event_update.emit();
		}
	}
	
	@EventInputPort(name="event_in", event="e_start")
	public void event_input_start() {
		System.out.println("ComponentContainer.event_input_start");
		this.state = State.ACTIVE;
		
		if (this.init == false) {
			this.event_init.emit();
			this.init = true;
		}
	}
	
	@EventInputPort(name="event_in", event="e_stop")
	public void event_input_stop() {
		System.out.println("ComponentContainer.event_input_stop");
		this.state = State.IDLE;
	}
	
	@EventInputPort(name="event_in", event="update")
	public void event_input_update() {
		if (this.mode == Mode.ON_EVENT) {
			this.update();
		}
	}
	
	
	public void update_cycle() {
		if (this.mode == Mode.CYCLIC) {
			this.update();
		}
	}
	
}
