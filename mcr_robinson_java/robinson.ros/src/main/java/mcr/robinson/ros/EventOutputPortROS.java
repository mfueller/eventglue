package mcr.robinson.ros;

import mcr.robinson.EventOutputPort;
import mcr.robinson.IEventSlot;

import org.ros.message.MessageListener;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Subscriber;

public class EventOutputPortROS extends EventOutputPort implements MessageListener<std_msgs.String> {
	
	String topic;
	String event;
	Subscriber<std_msgs.String> subscriber;
	ConnectedNode connectedNode;
	
	public EventOutputPortROS(ConnectedNode connectedNode, String topic, String event) {
		this.topic = topic;
		this.connectedNode = connectedNode;	
		this.event = event;
	}
	
	@Override
	public void onNewMessage(std_msgs.String arg0) {
		if (arg0.getData().equals(this.event)) {
			emit();
		}
	}
	
	@Override
	public void connect(IEventSlot slot) {
		super.connect(slot);
		
		if (subscriber == null) {
			subscriber = connectedNode.newSubscriber(this.topic, std_msgs.String._TYPE);
			subscriber.addMessageListener(this);
		}
	}
}
