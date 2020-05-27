#pragma once
#include "Coordinates.h"
#include  "Part.h"
#include <string>

enum class TileType{buildable, unbuildable};

class Tile
{
	Coordinates location;
	TileType tileType;
	std::unique_ptr<Part> part;
	//Part part;
public:
	Tile() {
		location = Coordinates{ 0,0 };
		tileType = TileType::buildable;
		part = nullptr;
	}
	Tile(Coordinates location_, TileType tileType_) {
		location = location_;
		tileType = tileType_;
	}
	
};

