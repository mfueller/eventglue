#!/usr/bin/env python

import rospy

import roslib
import rospy
import actionlib

from control_msgs.msg import GripperCommandAction

from brics_actuator.msg import JointPositions, JointValue

from sensor_msgs.msg import JointState
from brics_actuator.msg._JointValue import JointValue
import sensor_msgs
import std_msgs
from std_msgs.msg import String

class GripperCommandControllerServer:
	def __init__(self):
		self.received_state = False

		self.server = actionlib.SimpleActionServer('gripper_controller', GripperCommandAction, self.execute, False)
		
		self.pub_cfg_joint_positions = rospy.Publisher("~set_target_joint_position", JointState)
		
		self.pub_event_out = rospy.Publisher("~event/out", String)
		
		self.event_done_subscriber = rospy.Subscriber("~event/in", String, self.cb_event_in)
		
		self.joint_names = []
		self.current_joint_configuration = [0, 0]
		
		if (not rospy.has_param("~joints")):
			rospy.logerr("No parameter set for ~joints")
			exit(-1)
		else:
			self.joint_names = sorted(rospy.get_param("~joints"))
			
		rospy.loginfo("gripper joints: %s", self.joint_names)
		
		self.last_event = ""
		
		self.server.start()

	def cb_event_in(self, event):
		
		self.last_event = event.data
		
		
	def execute(self, goal):
		rospy.logdebug("Executing command goal: " + str(goal))
		
		joint_state = JointState()
		
		joint_state.name = self.joint_names
		joint_state.position.append(goal.command.position)
		joint_state.position.append(goal.command.position)
		
		
		rospy.loginfo("sending joint configuration ")
		self.pub_cfg_joint_positions.publish(joint_state)
		
		# second step -> send start signal
		e_start = String()
		e_start.data = "e_start"
		
		rospy.loginfo("sending e_start event")
		
		self.last_event = "" # reset last_event
		self.pub_event_out.publish(e_start)
		
		# wait for msg
		loop_counter = 100
		sleep_duration = rospy.Duration(0.1, 0)
		rospy.loginfo("Waiting for event e_done")
		while(loop_counter > 0):
			if (loop_counter % 10 == 0):
				rospy.logdebug("Waiting for event e_done")
			
			if (self.last_event == "e_done"):
				self.server.set_succeeded()
				return
			elif (self.last_event == "e_error"):
				break
			
			loop_counter-=1
			rospy.sleep(sleep_duration)
		
		if (loop_counter <= 0):
			self.server.set_aborted(text="Cound not get e_done event, last received event=" + str(self.last_event))
		


def main():
	rospy.init_node('gripper_controller')
	server = GripperCommandControllerServer()
	rospy.spin()
