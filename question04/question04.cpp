//Question 4 - pointers

// There is a memory leak in the code below, where is it?, what class/solution can you use to fix it while ensuring that the object will be deleted only once and only when it's not used by any consumer
// Task: Modify the code to address the issues above. Please explain the changes you made and how they solve the memory allocation/deletion issue  

// Do not remove any function or change threads dispatching order - you can(and should) change the functions body/signature

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include "../question02/semaphore.h"


/*
// ============================================================Answer============================================
// The is a memory leak is on payload struct that didn't free at the end of used
// I added 3 function on Paylaod struct with semaphore protection that count the number of threads that use this resource
// 1. open() -> increased the number of threads using this resource 
// 2. close() -> decreased the number of threads using this resource 
// 3. is_open() -> return true if there is tread using this resource 
// In each thread I declare on start using payload and finish.
// At the end of the thread I check if there is any another thred that use this resource, if not I free it.
*/


struct Payload {

	Payload(uint64_t id_) :
		id(id_),
		veryLargeVector(1000 * 1000),
		open_count(0),
		semaphore(1)
	{}
	void open() {
		semaphore.acquire();
		open_count++;
		semaphore.release();
	}
	void close() {
		semaphore.acquire();
		open_count--;
		semaphore.release();
	}
	bool is_open() {
		return open_count;
	}
	uint64_t id;
	int open_count;
	Semaphore semaphore;
	std::vector<int> veryLargeVector;
};

void operation1(Payload* payload) {
	payload->open();
	std::cout << "Performing operation1 on payload " << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
	payload->close();
	if (!payload->is_open()) {
		delete payload;
	}
}

void operation2(Payload* payload) {
	payload->open();
	std::cout << "Performing operation2 on payload " << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1)))));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
	payload->close();
	if (!payload->is_open()) {
		delete payload;
	}
}

void dispacher_thread() {
	Payload* payload = new Payload(1);
	std::this_thread::sleep_for(std::chrono::seconds(2));  //Simulate some heavy work
	std::thread wt1(&operation1, payload);
	std::thread wt2(&operation2, payload);
	//Waiting for wt1 & wt2 to finish is not allowed, dispacher_thread should exit after creating wt1 and wt2
	wt1.detach();
	wt2.detach();
}

int main(int argc, char** argv)
{
	std::cout << "Calling dispatcher thread" << std::endl;
	std::thread t(&dispacher_thread);
	t.join();

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}