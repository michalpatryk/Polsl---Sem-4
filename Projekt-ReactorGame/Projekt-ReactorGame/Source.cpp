#include <TGUI/TGUI.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#include <sstream>
#include "Game.h"
std::mutex mtx;
float test;
#include "debugFunctions.h"

class Clock{
	float clockTick=0;
public:
	explicit Clock(float clock_tick)
		: clockTick(clock_tick) {
	}

	void operator()() {
		while(1) {
			std::cout << clockTick << std::endl;
			test++;
			clockTick++;
		}
	}
	float getClockTick() const {
		mtx.lock();
		std::cout << clockTick;
		mtx.unlock();
		return clockTick;
	}
};

int main()
{
	const sf::VideoMode v_mode(1024, 800, 32);
	Game game(v_mode);
	return(game.run());
	
}