#pragma once
#include "Tile.h"
#include "Clock.h"
#include <utility>
#include <vector>
#include <thread>
#include <nlohmann/json.hpp>
class Reactor
{
	//game data
	double power = 0;
	double money = 0;

	
	//map data
	std::vector<std::vector<Tile>> tiles;
	std::vector<int> tileMap;
	int width = 0;
	int height = 0;
	
	//clock
	std::mutex mtx;
	Clock clock{ mtx};
public:
	///Map initialization
	Reactor();

	Reactor(std::vector<int> tileMap, int width, int height);

	explicit Reactor(std::vector< std::vector<Tile>> tiles_) {
		tiles = std::move(tiles_);
	}
	double getPower() const { return power; }

	double getMoney() const { return money; }

	void checkTick() {
		int ticks = clock.getTick();
		clock.resetTick();
		//sell power by sellers

		//gain power by generators
		for (int i = 0; i < ticks; i++) {
			power++;
		}
	}

	bool buyPart(std::string type);

	float getPartPrice(std::string type);

	void sellPower() {
		money += power;
		power = 0;
	}

	//used to start a clock thread
	Clock& getClock() {
		return std::ref(clock);
	}
	//DEBUG ONLY FUNCTION - to know current ticks
	int getTick() {
		return clock.getTick();
	}

	void reactorShutdown() {
		clock.initializeShutdown();
	}
};

