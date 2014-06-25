/*
 * Scheduler.h
 *
 *  Created on: Jun 12, 2014
 *      Author: matthias
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "mcr_robinson/EventGlue.h"

enum Mode {ON_DATA_EVENT, ON_UPDATE_EVENT};


template <class COMPONENT>
class ComponentContainer {
private:

	enum State {IDLE, ACTIVE};
	State state;


	Mode mode;

	COMPONENT* component;

	EventPortOutput updateEvent;
	EventPortOutput initEvent;
	EventPortOutput shutdownEvent;

	bool init;


	void update() {
		if (this->state == ACTIVE) {
			updateEvent();
		}
	}

public:
	ComponentContainer(COMPONENT* component) {
		this->component = component;
		init = false;
		mode = ON_DATA_EVENT;

		updateEvent.connect(EVENT_INPUT(&COMPONENT::update, component));
		initEvent.connect(EVENT_INPUT(&COMPONENT::init, component));
		shutdownEvent.connect(EVENT_INPUT(&COMPONENT::shutdown, component));

	}

	virtual ~ComponentContainer() {
		shutdownEvent();
	}

	EventPortInput(start) {
		this->state = ACTIVE;
		std::cout << "ComponentContainer::state = ACTIVE" << std::endl;

		if (init == false) {
			initEvent();
			init = true;
			std::cout << "ComponentContainer::init = TRUE" << std::endl;

		}
	}

	EventPortInput(stop) {
		this->state = IDLE;
		std::cout << "ComponentContainer::state = IDLE" << std::endl;

	}

	void update_on_data() {
		if (mode == ON_DATA_EVENT) {
			this->update();
		}
	}

	void update_cycle() {
		if (mode == ON_UPDATE_EVENT) {
			this->update();
		}
	}

	void setMode(Mode mode) {
		this->mode = mode;
		std::cout << "ComponentContainer::mode = " << mode << std::endl;

	}


};

#endif /* SCHEDULER_H_ */
