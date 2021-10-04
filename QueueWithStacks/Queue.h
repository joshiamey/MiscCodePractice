/*
 * Queue.h
 *
 *  Created on: Dec 7, 2018
 *      Author: ameya
 */

#pragma once
#include <stack>
#include <stdio.h>
#include <stdint.h>


class Queue {
public:
	Queue():
		enqueueStack_(),
		dequeStack_()
	{

	}
	virtual ~Queue();

	void deque();

	void enqueue(uint32_t item);

	uint32_t front();

private:
	std::stack<uint32_t> enqueueStack_;
	std::stack<uint32_t> dequeStack_;
};

