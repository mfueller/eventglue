eventglue
=========


Hello World example

- start the hello world node

 $ roslaunch mcr_robinson_hello_world_ros hello_world.launch

- listen to the output port

 $ rostopic echo /hello_world/pout_answer
   
- send a name to the input port
   
 $ rostopic pub -r 1 hello_world/pin_name std_msgs/String "Matthias"
   
- send the start event
   
 $ rostopic pub /hello_world/event_in std_msgs/String "e_start"
    
-> "Hello <name>" should now be published on the output port

- send stop event
   
 $ rostopic pub /hello_world/event_in std_msgs/String "e_stop"
  
