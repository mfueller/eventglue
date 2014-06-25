
import rospy

import mcr_robinson_hello_world.HelloWorldComponent as hwc
from mcr_robinson_python.ComponentContainer import Mode as CCMode
from mcr_robinson_python.ComponentContainer import ComponentContainer

from mcr_robinson_ros.DataPort import DataPortOutputROS, DataPortInputROS, EventPortOutputROS, EventPortInputROS

from mcr_robinson_ros.Converter import RosStringConverter

from std_msgs.msg import String
          
if __name__ == "__main__":
    rospy.init_node("HelloWorldNodePython")
    
    
    # create component
    helloWorld = hwc.HelloWorld()
    
    # connect ports with ROS
    DataPortOutputROS("pin_name", String, RosStringConverter.fromROS).connect(helloWorld.pin_name)
    helloWorld.pout_answer.connect(DataPortInputROS("pout_answer", String, RosStringConverter.fromPython))
    helloWorld.eventport_output_done.connect(EventPortInputROS("event_out", "e_done"))
    
    
    
    # create component container
    cc = ComponentContainer(helloWorld)
    cc.mode = CCMode.CYCLIC
    
    # connect event ports
    EventPortOutputROS("event_in", "e_start").connect(cc.eventport_input_start)
    EventPortOutputROS("event_in", "e_stop").connect(cc.eventport_input_stop)
    
                                   
    r = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
       cc.update_cycle()
       r.sleep()
    
    rospy.spin()
    