package mcr.robinson.ros;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

import mcr.robinson.DataInputSlot;
import mcr.robinson.DataOutputPort;
import mcr.robinson.EventInputSlot;
import mcr.robinson.EventOutputPort;
import mcr.robinson.annotations.DataInputPort;
import mcr.robinson.annotations.DataOutputPortInfo;
import mcr.robinson.annotations.EventInputPort;
import mcr.robinson.annotations.EventOutputPortInfo;

class EventPortDescriptionROS { 
    public final String topic; 
    public final String event; 
    public EventPortDescriptionROS(String topic, String event) { 
        this.topic = topic; 
        this.event = event; 
    }

    @Override
    public String toString() {
        return "(" + topic + "," + event + ")";
    }

    @Override
    public boolean equals(Object other) {
        if (other == null) {
            return false;
        }
        if (other == this) {
            return true;
        }
        if (!(other instanceof EventPortDescriptionROS)){
            return false;
        }
        EventPortDescriptionROS other_ = (EventPortDescriptionROS) other;
        return other_.topic.equals(this.topic) && other_.event == this.event;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((topic == null) ? 0 : topic.hashCode());
        result = prime * result + ((event == null) ? 0 : event.hashCode());
        return result;
    }
}

public class PortWireingROS {

	//List<DataOutputPortROS<?,?>> dataoutput = new Vector<DataOutputPortROS<?,?>>();
	//List<EventOutputPortROS> eventoutput = new Vector<EventOutputPortROS>();
	//List<EventInputPortROS> eventinput = new Vector<EventInputPortROS>();
	//List<DataInputPortROS<?,?>> datainput = new Vector<DataInputPortROS<?,?>>();

	PortUtilsROS portUtil;
	
	private Class<?> interfaceClass;
	private Object object;
	
	//Class interfaceClass = null;
	//ConnectedNode connectedNode;
	//Object object;
	
	
	public PortWireingROS(Class<?> interfaceClass, Object object, PortUtilsROS portUtil) {
		this.interfaceClass = interfaceClass;
		this.object = object;
		this.portUtil = portUtil;	
	}
	
	public void connectAllPorts() {
		connectEventInputPorts();
		connectDataInputPorts();
		connectEventOutputPorts();
		connectDataOutputPorts();
		
	}
	
	
	
	public void connectEventInputPorts() {
		for (Method m : interfaceClass.getMethods()) {
			if (m.isAnnotationPresent(EventInputPort.class)) {
				EventInputPort port = m.getAnnotation(EventInputPort.class);

				portUtil.EventOutputPortROS(port.name(), port.event()).connect(new EventInputSlot(object, m));

				
				System.out.println("Added EventOutput");
			}
		}
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void connectDataInputPorts() {
		for (Method m :interfaceClass.getMethods()) {

			if (m.isAnnotationPresent(DataInputPort.class)) {
				try {
					DataInputPort port = m.getAnnotation(DataInputPort.class);
					Class<?> parameterType = m.getParameterTypes()[0];

					portUtil.DataOutputPortROS(port.name(), parameterType).connect(new DataInputSlot(object, m));
					System.out.println("Added DataOutputPortROS");
					
				} catch (Exception e) {
					e.printStackTrace();
				}

			}

		}
	}


	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void connectEventOutputPorts() {

		for (int i = 0; i < interfaceClass.getFields().length; i++) {
			Field d = interfaceClass.getFields()[i];

			if (d.isAnnotationPresent(EventOutputPortInfo.class)) {
				EventOutputPortInfo eop = d.getAnnotation(EventOutputPortInfo.class);

				try {
					EventOutputPort e = (EventOutputPort) d.get(object);
					
					e.connect(portUtil.EventInputPortROS(eop.name(), eop.event()));

					System.out.println("Added EventOutputPortROS");
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	public void connectDataOutputPorts() {

		for (int i = 0; i < interfaceClass.getFields().length; i++) {
			Field d = interfaceClass.getFields()[i];

			if (d.isAnnotationPresent(DataOutputPortInfo.class)) {
				try {
					DataOutputPortInfo eop = d.getAnnotation(DataOutputPortInfo.class);
					
					DataOutputPort e = (DataOutputPort) d.get(object);

					e.connect(portUtil.DataInputPortROS(eop.name(), eop.type()));

					System.out.println("Added DataOutputPort");
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}
	}



	
}
