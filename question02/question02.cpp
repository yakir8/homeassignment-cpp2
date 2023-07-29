//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

#include <chrono>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include "semaphore.h"

/*
// ============================================================Answer============================================
// Because we have two threads that accesses to the same variable named 'gSum' in same cases thread1 read the value of gSum 
// and before its write the new value thread 2 write new value to gSum. In this case the data on gSum will be corrupted
// I resolved this by using semaphore that lock access to this variable if another thread already use it.
// In this way only one thread can access to the variable every time.
*/

using namespace std;


constexpr size_t ITERATIONS = 1000 * 1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

size_t gSum = 0;
Semaphore semaphore(1);


void operation1(size_t arg) {
	std::cout << "Performing operation1" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		semaphore.acquire(); // request access to gSume
		gSum += (arg + i);
		semaphore.release(); // release gSume from using
	}
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	std::cout << "Performing operation2" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		semaphore.acquire(); // request access to gSume
		gSum += (arg*i);
		semaphore.release(); // release gSume from using
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}


int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();
	thread t1(operation1, OP1_PARAM);
	thread t2(operation2, OP2_PARAM);
	t1.join();
	t2.join();

	auto end = std::chrono::steady_clock::now();

	std::cout << "Total execution duration in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "Result:  " << gSum << ", " << (gSum == EXPECTED_SUM ? "success" : "failure!") << std::endl;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}
