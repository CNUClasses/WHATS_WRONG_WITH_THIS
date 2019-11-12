//============================================================================
// Name        : WHATS_WRONG_WITH_THIS.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Run this code a few times, notice it locks up occasionally?
//				 Why? What did I do wrong?
//				 10 points added to project 4 grade for 1st right answer
//============================================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include "Semaphore.h"
using namespace std;

//mutex and function used to synchronize couts
mutex m_cout;
void log(int id){
	unique_lock<mutex> mlk(m_cout);
	cout<<"func "<<id<< " working, about to be done"<<endl;
}

const int NUMB_TO_RUN_AT_A_TIME = 2;

//initialize to neg number (must get above 0 for producer to wake!)
Semaphore s(NUMB_TO_RUN_AT_A_TIME);

void func(int id) {
	//block if too many threads working
	s.wait();

	//indicate that we are working
	log(id);

	//done work, let any waiting threads in
	s.signal();
}

int main() {
	thread t_func1(func, 1);
	thread t_func2(func, 2);
	thread t_func3(func, 3);
	thread t_func4(func, 4);
	thread t_func5(func, 5);

	t_func1.join();
	t_func2.join();
	t_func3.join();
	t_func4.join();
	t_func5.join();

	cout<<"program finished"<<endl;
}
