
from std_msgs.msg import String

class NoneConverter:
    
    def __call__(self, msg):
        return msg

class RosStringConverter:
    
    def fromROS(msg):
        return msg.data
    
    def fromPython(msg):
        s = String()
        s.data = msg
        return s
    
    
    