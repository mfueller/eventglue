package mcr.robinson.ros;

import mcr.robinson.IDataSlot;
import mcr.robinson.ros.converter.MessageConverter;

import org.ros.node.ConnectedNode;
import org.ros.node.topic.Publisher;

public class DataInputPortROS<ROS_TYPE, OWN_TYPE> implements IDataSlot<OWN_TYPE> {
	
	ConnectedNode node;
	private String topic;
	private Publisher<ROS_TYPE> publisher;
	private String typename;
	private MessageConverter<ROS_TYPE, OWN_TYPE> converter;
	
	
	public DataInputPortROS(ConnectedNode node, String topic,Class<ROS_TYPE> rosType, MessageConverter<ROS_TYPE, OWN_TYPE> converter) {
		super();
		this.node = node;
		this.topic = topic;
		this.converter = converter;
		
		try {
			this.typename = rosType.getField("_TYPE").get(null).toString();
		} catch (Exception e) {
			e.printStackTrace();
		}
		publisher =
		        node.newPublisher(topic, this.typename);
	}


	@Override
	public void receive(OWN_TYPE msg) {
		ROS_TYPE ros = converter.convertToROS(node, msg);
		publisher.publish(ros);
	}
}
