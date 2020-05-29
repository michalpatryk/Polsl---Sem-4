#pragma once
#include "Tile.h"
#include "Clock.h"
#include <utility>
#include <vector>
#include <thread>
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
	Reactor() {
		tiles.resize(10);
		for (int i = 0; i < 10; i++) {
			tiles[i].resize(10);
			for (int j = 0; j < 10; j++) {
				tiles[i][j] = Tile{ Coordinates{i, j}, TileType::buildable };
			}
		}
	}

	Reactor(std::vector<int> tileMap, int width, int height): tileMap(tileMap), width(width), height(height) {
		tiles.resize(height);
		for (int i = 0; i < height; i++) {
			tiles[i].resize(width);
			for (int j = 0; j < width; j++) {
				if(tileMap[i*width + j] == 47) {
					tiles[i][j] = Tile{ Coordinates{i, j}, TileType::buildable };
				}
				else {
					tiles[i][j] = Tile{ Coordinates{i, j}, TileType::unbuildable };
				}
			}
		}
	}

	explicit Reactor(std::vector< std::vector<Tile>> tiles_) {
		tiles = std::move(tiles_);
	}
	double getPower() const { return power; }

	double getMoney() const { return money; }

	void checkTick() { power++; }

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

