package mcr.robinson.ros;

import mcr.robinson.IDataSlot;
import mcr.robinson.IEventSlot;
import mcr.robinson.ros.converter.MessageConverter;

import org.ros.node.ConnectedNode;
import org.ros.node.topic.Publisher;

public class EventInputPortROS implements IEventSlot {
	
	ConnectedNode node;
	private String topic;
	private Publisher<std_msgs.String> publisher;
	private String typename;
	private String event;
	
	public EventInputPortROS(ConnectedNode node, String topic, String event) {
		super();
		this.node = node;
		this.topic = topic;
		this.event = event;
		
		try {
			this.typename = std_msgs.String._TYPE;
		} catch (Exception e) {
			e.printStackTrace();
		}
		publisher =
		        node.newPublisher(this.topic, this.typename);
	}


	@Override
	public void receive() {
	
		std_msgs.String msg = publisher.newMessage();
		msg.setData(this.event);
		
		publisher.publish(msg);
	}
}
