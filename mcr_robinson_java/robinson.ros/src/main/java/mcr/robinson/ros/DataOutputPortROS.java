package mcr.robinson.ros;

import mcr.robinson.DataOutputPort;
import mcr.robinson.IDataSlot;
import mcr.robinson.ros.converter.MessageConverter;

import org.ros.message.MessageListener;
import org.ros.node.ConnectedNode;
import org.ros.node.topic.Subscriber;

public class DataOutputPortROS<ROS_TYPE extends org.ros.internal.message.Message, OWN_TYPE> extends DataOutputPort<OWN_TYPE> implements MessageListener<ROS_TYPE> {
	
	String topic;
	MessageConverter<ROS_TYPE, OWN_TYPE> converter;
	Subscriber<ROS_TYPE> subscriber;
	String typename;
	ConnectedNode connectedNode;
	
	public DataOutputPortROS(ConnectedNode connectedNode, String topic, Class<ROS_TYPE> rosType, MessageConverter<ROS_TYPE, OWN_TYPE> converter) {
		this.topic = topic;
		this.converter = converter;
		this.connectedNode = connectedNode;
		
		try {
			this.typename = rosType.getField("_TYPE").get(null).toString();
		} catch (Exception e) {
			e.printStackTrace();
		}
				

	}
	
	@Override
	public void onNewMessage(ROS_TYPE arg0) {
		System.out.println("DataOutputPortROS.onNewMessage");
		OWN_TYPE msg = this.converter.convertFromROS(arg0);
		emit(msg);
	}
	
	@Override
	public void connect(IDataSlot<OWN_TYPE> slot) {
		super.connect(slot);
		
		if (subscriber == null) {
			subscriber = connectedNode.newSubscriber(this.topic, typename);
			subscriber.addMessageListener(this);
		}
	}
}
