package mcr.robinson.ros.converter;

import org.ros.node.ConnectedNode;

public interface MessageConverter<ROS_TYPE, OWN_TYPE> {
	
	ROS_TYPE convertToROS(ConnectedNode node, OWN_TYPE msg);
	
	OWN_TYPE convertFromROS(ROS_TYPE msg);
	
}
