#pragma once
#include "Tile.h"
#include "Clock.h"
#include <utility>
#include <vector>
#include <nlohmann/json.hpp>
#include "TileMap.h"
class Reactor
{
	//game data
	double power = 0;
	double maxPower = 100;
	double money = 0;


	//map data
	std::vector<std::vector<Tile>> tiles;
	std::vector<int> tileMap;


	//clock
	std::mutex mtx;
	Clock clock{ mtx };
public:
	//Map initialization
	Reactor();

	Reactor(std::vector<int> tileMap, int width, int height);

	explicit Reactor(std::vector< std::vector<Tile>> tiles_) {
		tiles = std::move(tiles_);
	}
	double getPower() const { return power; }

	double getMoney() const { return money; }
	
	/**	Checks if clock have any ticks, if yes it calculates all elements.
	 *
	 */
	void checkTick(TileMap& partMap);

	std::string buyPart(nlohmann::json j, sf::Vector2i location, TileMap& partMap);
	std::string sellPart(sf::Vector2i location, TileMap& partMap);

	//float getPartPrice(std::string type);
	nlohmann::json getPostUpgradePart(nlohmann::json j) {
		return j;
	}

	void sellPower();

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
	std::vector<std::vector<Tile>>& getTiles() {
		return tiles;
	}

	void recalculateMaxPower();

	double getFullPrice(nlohmann::json j) {
		return j["basePrice"].get<double>();
	}
	double getFullPrice(Types type, double price) {
		return price;
		//add upgrades handle here
		//return j["basePrice"].get<float>();
	}
	double getMaxPower() { return maxPower; }
};

