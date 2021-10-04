/*
 * Queue.cpp
 *
 *  Created on: Dec 7, 2018
 *      Author: ameya
 */

#include "Queue.h"

Queue::Queue() {
	// TODO Auto-generated constructor stub

}

Queue::~Queue() {
	// TODO Auto-generated destructor stub
}

void Queue::deque() {

	if(dequeStack_.empty()) {
			// fill up the dequeu stack with elements from enqueu
			while(!enqueueStack_.empty())
			{
				dequeStack_.push(enqueueStack_.top());
				enqueueStack_.pop();
			}			
	}

	dequeStack_.pop();
}

void Queue::enqueue(uint32_t data) {
	enqueueStack_.push(data);
}

uint32_t Queue::front() {

	if(dequeStack_.empty()) {
			// fill up the dequeu stack with elements from enqueu
			while(!enqueueStack_.empty())
			{
				dequeStack_.push(enqueueStack_.top());
				enqueueStack_.pop();
			}			
	}

	return dequeStack_.top();
}

