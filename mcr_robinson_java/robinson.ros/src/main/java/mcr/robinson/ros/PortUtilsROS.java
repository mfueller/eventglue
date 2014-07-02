package mcr.robinson.ros;

import java.util.HashMap;
import java.util.Map;

import org.ros.node.ConnectedNode;

import mcr.robinson.ros.converter.MessageConverter;
import mcr.robinson.ros.converter.MessageConverterRegistration;

public class PortUtilsROS {

	private ConnectedNode connectedNode;
	
	Map<String, DataOutputPortROS<?,?>> dataoutput = new HashMap<String, DataOutputPortROS<?,?>>();
	Map<String, DataInputPortROS<?,?>> datainput = new HashMap<String, DataInputPortROS<?,?>>();
	
	Map<EventPortDescriptionROS, EventOutputPortROS> eventoutput = new HashMap<EventPortDescriptionROS, EventOutputPortROS>();
	Map<EventPortDescriptionROS, EventInputPortROS> eventinput = new HashMap<EventPortDescriptionROS, EventInputPortROS>();
	
	
	public PortUtilsROS(ConnectedNode connectedNode) {
		super();
		this.connectedNode = connectedNode;
	}

	public EventOutputPortROS EventOutputPortROS(String topic, String event) {
		EventPortDescriptionROS eventPortDescriptionROS = new EventPortDescriptionROS(topic, event);
		
		if (eventoutput.containsKey(eventPortDescriptionROS)) {
			return eventoutput.get(eventPortDescriptionROS);
		}
		
		EventOutputPortROS eventOut = new EventOutputPortROS(connectedNode, topic, event);
		eventoutput.put(eventPortDescriptionROS, eventOut);
		
		return eventOut;
	}
	
	public EventInputPortROS EventInputPortROS(String topic, String event) {
		EventPortDescriptionROS eventPortDescriptionROS = new EventPortDescriptionROS(topic, event);
		
		if (eventinput.containsKey(eventPortDescriptionROS)) {
			return eventinput.get(eventPortDescriptionROS);
		}
		
		EventInputPortROS in = new EventInputPortROS(connectedNode, topic, event);
		eventinput.put(eventPortDescriptionROS, in);
		
		return in;
	}
	
	@SuppressWarnings({"rawtypes", "unchecked"})
	public DataOutputPortROS DataOutputPortROS(String topic, Class<?> local_type) {
		
		if (dataoutput.containsKey(topic)) {
			return dataoutput.get(topic);
		}
		
		try {
			Class<?> c = getMessageConverter(local_type);
			
			MessageConverterRegistration mcr = c.getAnnotation(MessageConverterRegistration.class);
	
			MessageConverter<?, ?> converter = (MessageConverter<?, ?>) c.newInstance();
			
			
			DataOutputPortROS out = new DataOutputPortROS(connectedNode, topic, mcr.ROSType(), converter);
			
			dataoutput.put(topic, out);
			return out;
		} catch(Exception e) {
			e.printStackTrace();
		}
		return null;
		
	}
	
	@SuppressWarnings({"rawtypes", "unchecked"})
	public DataInputPortROS DataInputPortROS(String topic, Class<?> local_type) {
		
		if (datainput.containsKey(topic)) {
			return datainput.get(topic);
		}
		
		try {
			Class<?> c = getMessageConverter(local_type);
			
			MessageConverterRegistration mcr = c.getAnnotation(MessageConverterRegistration.class);
	
			MessageConverter<?, ?> converter = (MessageConverter<?, ?>) c.newInstance();
			
			
			DataInputPortROS out = new DataInputPortROS(connectedNode, topic, mcr.ROSType(), converter);
			
			datainput.put(topic, out);
			
			return out;
		} catch(Exception e) {
			e.printStackTrace();
		}
		return null;
		
	}
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public Class<?> getMessageConverter(Class<?> localType) {
		JavaPackageFinder finder = new JavaPackageFinder();
		
		Class<?>[] converterClasses = finder.getClasses("mcr.robinson.ros.converter", MessageConverter.class);
		System.out.println("Found classes: " + converterClasses.length);
		
		for (Class<?> c : converterClasses) {
			System.out.println("######## Searching in class: " + c);
			if (c.isAnnotationPresent(MessageConverterRegistration.class)) {
				MessageConverterRegistration mcr = c.getAnnotation(MessageConverterRegistration.class);
				if (localType.equals(mcr.LocalType())) {
					return c;
				}
			}

		}

		return null;
	}
}
