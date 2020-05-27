#pragma once
#include <mutex>  
#include <iostream>
//std::mutex mtx;
class Clock {
	int tick = 0;
	std::mutex &mtx;
public:
	Clock(std::mutex& mutex) :mtx(mutex){};
	//void incrementTick() {
	//	//std::lock_guard<std::mutex> lck(mtx);
	//	tick++;
	//}
	//void decrementTick(std::mutex &mtx) {
	//	std::lock_guard<std::mutex> lck(mtx);
	//	tick--;
	//}
	//void resetTick(std::mutex &mtx) {
	//	std::lock_guard<std::mutex> lck(mtx);
	//	tick--;
	//}
	//int getTick() {
	//	std::lock_guard<std::mutex> lck(mtx);
	//	return tick;
	//}
	void operator()(int &tick, bool &exit) {
		while (true) {
			mtx.lock();
			tick++;
			mtx.unlock();
			//incrementTick();
			if (exit == true) return;
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}
};