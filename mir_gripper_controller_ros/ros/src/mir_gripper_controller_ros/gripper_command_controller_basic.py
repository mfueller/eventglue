#!/usr/bin/env python

import rospy

import roslib
import rospy
import actionlib

from control_msgs.msg import GripperCommandAction

from brics_actuator.msg import JointPositions, JointValue

from sensor_msgs.msg import JointState
from brics_actuator.msg._JointValue import JointValue

class GripperCommandControllerServer:
	def __init__(self):
		self.received_state = False

		if (not rospy.has_param("~position_command")):
			rospy.logerr("No parameter set for ~position_command")
			exit(-1)
		else:
			self.position_cmd_topic = rospy.get_param("~position_command", "POSITION_COMMAND_NOT_SET")
		
		self.server = actionlib.SimpleActionServer('gripper_controller', GripperCommandAction, self.execute, False)
		self.pub_joint_positions = rospy.Publisher(self.position_cmd_topic, JointPositions)
		rospy.loginfo("using " + self.position_cmd_topic + " topic for publishing gripper commands")
		
		self.joint_names = []
		self.current_joint_configuration = [0, 0]
		
		if (not rospy.has_param("~joints")):
			rospy.logerr("No parameter set for ~joints")
			exit(-1)
		else:
			self.joint_names = sorted(rospy.get_param("~joints"))
			
		rospy.loginfo("gripper joints: %s", self.joint_names)
		
		rospy.Subscriber("joint_states", JointState, self.joint_states_callback)
		
		self.server.start()

	def wait_for_new_joint_states(self):
		self.received_state = False

		while (self.received_state == False):
			rospy.sleep(0.01)

		return
	
	def execute(self, goal):
		rospy.logdebug("Executing command goal: " + str(goal))
		jnt_pos = JointPositions()
		
		for k in range(len(self.joint_names)):
			value = JointValue()
			value.joint_uri = self.joint_names[k]
			value.unit = "m"
			value.value = goal.command.position
			jnt_pos.positions.append(value)
		
		self.pub_joint_positions.publish(jnt_pos)
		
		rospy.sleep(2.0)
		
		self.server.set_succeeded()
	
	def joint_states_callback(self, msg):
		for k in range(len(self.joint_names)):
			for i in range(len(msg.name)):
				if (msg.name[i] == self.joint_names[k]):
					self.current_joint_configuration[k] = msg.position[i]
					
		self.received_state = True
			
		return True
	

def main():
	rospy.init_node('gripper_controller')
	server = GripperCommandControllerServer()
	rospy.spin()
