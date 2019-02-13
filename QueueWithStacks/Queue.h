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

	void deque()
	{
		if(dequeStack_.empty())
		{
			// fill up the dequeu stack with elements from enqueu
			while(!enqueueStack_.empty())
			{
				dequeStack_.push(enqueueStack_.top());
				enqueueStack_.pop();
			}
		}
		dequeStack_.pop();
	}

	void enqueue(uint32_t item)
	{
		enqueueStack_.push(item);
	}

	uint32_t front()
	{
		if(dequeStack_.empty())
		{
			// fill up the dequeu stack with elements from enqueu
			while(!enqueueStack_.empty())
			{
				dequeStack_.push(enqueueStack_.top());
				enqueueStack_.pop();
			}
		}
		return dequeStack_.top();
	}

private:
	std::stack<uint32_t> enqueueStack_;
	std::stack<uint32_t> dequeStack_;
};

