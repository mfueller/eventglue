/*
 * GripperControllerCoordinator.cpp
 *
 *  Created on: Mar 24, 2014
 *      Author: matthias
 */

#include "mir_gripper_controller/JointPositionCoordinator.h"

namespace mir_industrial
{
namespace manipulation
{

JointPositionCoordinator::JointPositionCoordinator()
{

}

JointPositionCoordinator::~JointPositionCoordinator()
{

}

void JointPositionCoordinator::e_cmd_in(std::string event)
{
    std::cout << "JointPositionCoordinator::e_cmd_start" << std::endl;
    /*
    event_cmd_joint_monitors_start();
    event_cmd_joint_ctl_start();
    */
}
/*
void JointPositionCoordinator::e_cmd_stop() {
	std::cout << "JointPositionCoordinator::e_cmd_stop" << std::endl;

	event_cmd_joint_monitors_stop();
	event_cmd_joint_ctl_stop();
}
*/

void JointPositionCoordinator::e_cb_jointctl_in(std::string event)
{
    std::cout << "JointPositionCoordinator::e_cb_jointctl_done" << std::endl;

    //Nothing to do?
}

/*
void JointPositionCoordinator::e_cb_jointctl_error() {

	std::cout << "JointPositionCoordinator::e_cb_jointctl_error" << std::endl;

	event_cmd_joint_monitors_stop();
	event_cmd_joint_ctl_stop();
	event_status_error();
}
*/

void JointPositionCoordinator::e_cb_monitor_in(std::string event)
{
    std::cout << "JointPositionCoordinator::e_cb_monitor_done" << std::endl;
    /*
    //count how often we need to receive the event?
    event_cmd_joint_monitors_stop();
    event_cmd_joint_ctl_stop();
    event_status_done();
    */
}
/*
void JointPositionCoordinator::e_cb_monitor_error() {
	std::cout << "JointPositionCoordinator::e_cb_monitor_error" << std::endl;

	event_cmd_joint_monitors_stop();
	event_cmd_joint_ctl_stop();
	event_status_error();
}
*/
} /* namespace manipulation */
} /* namespace mir_industrial */


