/*
 * concurrentqueue.h
 *
 *  Created on: Feb 15, 2015
 *      Author: vadim
 */

#ifndef CONCURRENTQUEUE_H_
#define CONCURRENTQUEUE_H_

#include <stdlib.h>
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class concurrent_queue {
public:
	concurrent_queue(){};
	virtual ~concurrent_queue(){};
	int push(const T& item);
	int pop(T& item);
private:
	std::queue<T> _q;
	std::mutex _m;
	std::condition_variable _c;
};

template <class T>
int concurrent_queue<T>::pop(T& item){
	std::unique_lock<std::mutex> lock{_m};

	//using while to prevent spurious wake ups
	while(_q.empty())
	{
		_c.wait(lock);
	}
	item = _q.front();
	_q.pop();

	return 0;
}


template <class T>
int concurrent_queue<T>::push(const T& item){
	std::unique_lock<std::mutex> lock{_m};
	_q.push(item);
	lock.unlock();
	_c.notify_one();
	return 0;
}


#endif /* CONCURRENTQUEUE_H_ */
