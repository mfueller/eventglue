package mcr.robinson.ros.converter;

import org.ros.node.ConnectedNode;

@MessageConverterRegistration(LocalType=String.class, ROSType=std_msgs.String.class)
public class StringMessageConverter implements MessageConverter<std_msgs.String, String> {
	
	@Override
	public String convertFromROS(std_msgs.String msg) {
		return msg.getData();
	}
	
	@Override
	public std_msgs.String convertToROS(
			ConnectedNode node, String msg) {
		std_msgs.String s = node.getTopicMessageFactory().newFromType(std_msgs.String._TYPE);
		
		s.setData(msg);
		
		return s;
	}
}
