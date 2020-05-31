#pragma once
#include "Tile.h"
#include "Clock.h"
#include <utility>
#include <vector>
#include <thread>
#include <nlohmann/json.hpp>
#include "TileMap.h"
class Reactor
{
	//game data
	double power = 0;
	double money = 0;

	
	//map data
	std::vector<std::vector<Tile>> tiles;
	std::vector<int> tileMap;

	
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

	std::string buyPart(nlohmann::json j, sf::Vector2i location, TileMap &partMap) {
		std::cout << location.x << " " << location.y << std::endl;
		std::cout << j << std::endl;
		if(tiles[location.y][location.x].getTileType() == TileType::buildable) {
			if(tiles[location.y][location.x].getPart() == nullptr) {
				if (money > getFullPrice(j)) {
					money -= getFullPrice(j);
					tiles[location.y][location.x].createPart(j);
					partMap.change(location, sf::Vector2i{ j["textureX"], j["textureY"] });
					return (j["model"].get<std::string>() += " built!");
				}
				else return "Not enough money";
			}
			else return "There is already a part here!";
		}
		else return "You can't build on this tile!";
		
		return ".";
	};

	//float getPartPrice(std::string type);
	nlohmann::json getPostUpgradePart(nlohmann::json j) {
		return j;
	}
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
	std::vector<std::vector<Tile>>& getTiles() {
		return tiles;
	}

	float getFullPrice(nlohmann::json j) {
		//add upgrades handle here
		return j["basePrice"].get<float>();
	}
};

