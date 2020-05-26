#pragma once
#include "Coordinates.h"
#include  "Part.h"
#include <string>

class Tile
{
	Coordinates location;
	std::string tileType;
	std::unique_ptr<Part> part;
	//Part part;
public:
	Tile() {
		location = Coordinates{ 0,0 };
		tileType = "Water";
		part = nullptr;
	}
	Tile(Coordinates location_, std::string tileType_) {
		location = location_;
		tileType = tileType_;
	}
	
};

