/*
 * Semaphore.cpp
 *
 *  Created on: Nov 8, 2017
 *      Author: keith
 */
#include <iostream>
#include "Semaphore.h"
using namespace std;

Semaphore::Semaphore(int cnt) :
		count(cnt) {
}
Semaphore::~Semaphore() {
}

void Semaphore::wait() {
	unique_lock<mutex> mlk(m);
	count--;
	while (count < 0)
		cv.wait(mlk);
}
void Semaphore::signal() {
	{
		unique_lock<mutex> mlk(m);
		count++;
	}
	cv.notify_all();
}

