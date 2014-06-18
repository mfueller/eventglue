#ifndef EVENTGLUE_ROSEVENTGLUE_H_
#define EVENTGLUE_ROSEVENTGLUE_H_

#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/signal.hpp>
#include <boost/any.hpp>

#include <map>
#include <vector>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <kdl/jntarray.hpp>

#include "mcr_robinson/message_converter/MessageConverter.h"
#include "mcr_robinson_ros/message_converter/ros_msgs.h"

#include <iostream>

#include "mcr_robinson/EventGlue.h"

#include "RosPort.h"


#define EVENT_OUTPUT_ROS(TOPIC, NAME) \
    RosEventGlue::ros_event_source(TOPIC, NAME)

#define EVENT_INPUT_ROS(TOPIC, NAME) \
    RosEventGlue::ros_event_sink(TOPIC, NAME)


//typedef EventOutputROS<std_msgs::String, std::string> EventPortOutputROS;
//typedef EventInputROS<std_msgs::String, std::string> EventPortInputROS;

typedef std_msgs::String ROS_TYPE;
typedef std::string MY_TYPE;

class EventPortInputROS : public EventPortInput
{
        std::string topic_name;
        std::string event_name;

        ros::Publisher publisher;

    public:

        //typename PortSink<MY_TYPE>::type ros_publisher;

        EventPortInputROS(std::string topic_name, std::string event_name)
            : boost::function<void ()>(boost::bind(&EventPortInputROS::callback, this))
        {
            std::cout << "EventPortOutputROS::EventPortOutputROS(topic, name): advertises: " << topic_name << ", " << event_name <<
                      std::endl;

            ros::NodeHandle n("~");
            this->topic_name = topic_name;
            this->event_name = event_name;
            this->publisher = n.advertise<ROS_TYPE>(this->topic_name, 1);
            //ros_publisher = boost::bind(&RosPortSink<ROS_TYPE, MY_TYPE>::callback, this, _1);
            //boost::bind(&EventPortInputROS::callback, this);
        }

        ~EventPortInputROS()
        {
            std::cout << "RosOutPort::~RosOutPort()" << std::endl;
            this->publisher.shutdown();
        }

        void callback()
        {
            ROS_TYPE msg = MessageConverter<MY_TYPE, ROS_TYPE>::convert(this->event_name);
            this->publisher.publish(msg);
        }

};


class EventPortOutputROS : public EventPortOutput
{
        std::string topic_name;
        std::string event_name;

        ros::Subscriber subscriber;
    public:

        //typename PortSource<MY_TYPE>::type ros_topic_signal;

        EventPortOutputROS(std::string topic_name, std::string event_name)
        {
            std::cout << "EventOutputROS::EventOutputROS(topic, name): registered to: " << topic_name << ", " << event_name <<
                      std::endl;
            ros::NodeHandle n("~");
            this->topic_name = topic_name;
            this->event_name = event_name;
            this->subscriber = n.subscribe(this->topic_name, 1,
                                           &EventPortOutputROS::event_callback, this);
        }

        ~EventPortOutputROS()
        {
            std::cout << "EventOutputROS::~EventOutputROS()" << std::endl;
            this->subscriber.shutdown();
        }

        void event_callback(ROS_TYPE event)
        {
            MY_TYPE msg_new = MessageConverter<ROS_TYPE, MY_TYPE>::convert(event);

            if (this->event_name.compare(msg_new) == 0) {
                (*this)();
            }
        }


};



#endif
