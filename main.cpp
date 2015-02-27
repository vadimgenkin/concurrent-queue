/*
 * main.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: vadim
 */

#include <iostream>
#include "concurrentqueue.h"

using namespace std;

int main()
{
	concurrent_queue<int> cq;
	cq.push(10);

	int x;
	cq.pop(x);

	cout << x << endl;

	return 0;
}
