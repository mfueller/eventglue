/*
 * JointPositionCommandWrapper.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: matthias
 */

#include "JointPositionCommandWrapper.h"



namespace mir_industrial
{
namespace manipulation
{

JointPositionCommandWrapper::JointPositionCommandWrapper()
{
    init();
}

JointPositionCommandWrapper::~JointPositionCommandWrapper()
{

}


void JointPositionCommandWrapper::setJointNames(std::vector<std::string> joint_names)
{
    this->joint_names = joint_names;
}

void JointPositionCommandWrapper::commandJointPositions(KDL::JntArray joint_positions)
{
    brics_actuator::JointPositions pos;

    for (std::size_t i = 0; i < joint_positions.data.rows(); i++) {
        brics_actuator::JointValue v1;
        v1.joint_uri = this->joint_names[i];
        v1.value = joint_positions(0);
        v1.unit = "m";
        pos.positions.push_back(v1);
    }

    this->pub_cmd_values.publish(pos);
}

void JointPositionCommandWrapper::init()
{
    ros::NodeHandle node("~");

    pub_cmd_values = node.advertise<brics_actuator::JointPositions>("joint_position_command_wrapper/position_command", 1);

}

} /* namespace manipulation */
} /* namespace mir_industrial */
