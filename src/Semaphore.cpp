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
	
	count--;			//what happens if all threads call wait before signal
	while (count == 0)
		cv.wait(mlk);
	
//	count--; 	//solution, move line 20 here, will only get count down to 0
	
}
void Semaphore::signal() {
	{
		unique_lock<mutex> mlk(m);
		count++;
	}
	cv.notify_all();
}

