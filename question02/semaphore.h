#pragma once

#include <atomic>
#include <mutex>


class Semaphore {
public:
	Semaphore(int count);
	//Request access to sharing resource
	void acquire();
	//Release sharing resource from using
	void release();

private:
	std::mutex mutex_;
	std::atomic<int> count_;
	std::condition_variable condition_;
};