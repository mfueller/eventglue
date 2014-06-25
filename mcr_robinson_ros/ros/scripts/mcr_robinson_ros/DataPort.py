
import rospy

from mcr_robinson_ros.Converter import NoneConverter
from mcr_robinson_python.DataPort import DataPortOutput

from std_msgs.msg import String

class DataPortOutputROS(DataPortOutput):
    
    def __init__(self, topic, type, converter=NoneConverter()):
        DataPortOutput.__init__(self)
        
        self.topic = topic
        self.converter = converter.__func__
        rospy.Subscriber(self.topic, type, self.callback)
        
    def callback(self, msg):
        self(self.converter(msg))
        

class DataPortInputROS:
    
    def __init__(self, topic, type, converter=NoneConverter()):
        self.pub = rospy.Publisher(topic, type)
        self.converter = converter.__func__

    def callback(self, msg):
        self.pub.publish(self.converter(msg))

    def __call__(self, msg):
        self.callback(msg)
        

class EventPortOutputROS(DataPortOutput):
    
    def __init__(self, topic, event):
        DataPortOutput.__init__(self)
        
        self.topic = topic
        self.event = event
        rospy.Subscriber(self.topic, String, self.callback)
        
    def callback(self, msg):
        s = msg.data
        
        if (s == self.event):
            self()
        
class EventPortInputROS:
    def __init__(self, topic, event):
        self.pub = rospy.Publisher(topic, String)
        self.event = event
        
    def callback(self):
        s = String()
        s.data = self.event
        self.pub.publish(s)

    def __call__(self):
        self.callback()
  
  
