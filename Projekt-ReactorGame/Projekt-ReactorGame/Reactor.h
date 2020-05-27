#pragma once
#include "Tile.h"
#include "Clock.h"
#include <utility>
#include <vector>
#include <thread>
class Reactor
{
	double power = 0;
	double money = 0;
	std::vector<std::vector<Tile>> tiles;
	std::vector<int> tileMap;
	int width = 0;
	int height = 0;
	
	int ticks = 0;

	bool shutdown = false;
	std::mutex mtx;
	Clock clock{mtx};
public:
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

	void startClock() {
		//std::thread t1{c1, std::ref(ticks)};
		//t1.detach();
		int xd = 0;
		int gettick = 0;
		std::thread t1{ clock, std::ref(xd), std::ref(shutdown) };
		t1.detach();
		std::cout << "test";
		int j = 1;
		for(int i = 0; i < 1000000; i++) {
			j = j * 2 * 2 * 2 * 2 * 2;
			j /= 2;
			j /= 2;
			j /= 2;
			j /= 2;
			//gettick += clock.getTick();
		}
		std::cout << "test";
		
	}

	Clock& getClock() {
		return std::ref(clock);
	}
	int& getTickCounter() {
		return std::ref(ticks);
	}
	std::mutex& getMutex() {
		return std::ref(mtx);
	}
	void accessTick() {
		//clock.getTick();
	}
	void reactorShutdown() {
		shutdown = true;
	}
};

