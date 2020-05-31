#pragma once
#include <mutex>  
#include <iostream>
//std::mutex mtx;
class Clock {
	int tick = 0;
	int level = 5;
	bool shutdown = false;
	std::mutex &mtx;

	
	void wait() {
		double waitTime = (1000 * (1.0 - level / 8.0));
		int time = static_cast<int>(waitTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}
public:
	Clock(std::mutex& mutex) :mtx(mutex){};
	//Debug functions: pretty useless
	//void incrementTick() {
	//	//std::lock_guard<std::mutex> lck(mtx);
	//	tick++;
	//}
	//void decrementTick(std::mutex &mtx) {
	//	std::lock_guard<std::mutex> lck(mtx);
	//	tick--;
	//}
	
	bool upgradeClock() {
		if (level < 8) {
			level++;
			return true;
		}
		else return false;
	}
	void resetTick() {
		std::lock_guard<std::mutex> lck(mtx);
		tick = 0;
	}

	int getTick() const {
		std::lock_guard<std::mutex> lck(mtx);
		return tick;
	}
	void initializeShutdown() {
		shutdown = true;
	}
	void operator()() {
		while(true) {
			mtx.lock();
			tick++;
			mtx.unlock();
			if (shutdown == true) return;
			wait();
			//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}
	
};