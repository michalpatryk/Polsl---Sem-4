#pragma once
#include "Tile.h"
#include <utility>
#include <vector>
class Reactor
{
	double power = 0;
	double money = 0;
	std::vector<std::vector<Tile>> tiles;
public:
	Reactor() {
		tiles.resize(10);
		for (int i = 0; i < 10; i++) {
			tiles[i].resize(10);
			for (int j = 0; j < 10; j++) {
				tiles[i][j] = Tile{ Coordinates{i, j}, "Water" };
			}
		}
	}
	
	Reactor(std::vector< std::vector<Tile>> tiles_) {
		tiles = std::move(tiles_);
	}
	double getPower() const { return power; }

	double getMoney() const { return money; }

	void checkTick() {
		power++;
	}

	bool buyPart(std::string type);

	float getPartPrice(std::string type);

	void sellPower() {
		money += power;
		power = 0;
	}
	
};

