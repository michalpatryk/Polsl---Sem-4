#pragma once
#include "Coordinates.h"
#include  "Part.h"
#include <string>
#include <SFML/System/Vector2.hpp>

enum class TileType{buildable, unbuildable};

class Tile
{
	sf::Vector2i location;
	TileType tileType;
	std::unique_ptr<Part> part{};
	//Part part;
public:
	Tile() {
		location = sf::Vector2i{ 0,0 };
		tileType = TileType::buildable;
		//part = nullptr;
	}
	Tile(sf::Vector2i location_, TileType tileType_) {
		location = location_;
		tileType = tileType_;
		//part = nullptr;
	}
	void createPart(nlohmann::json j) {
		part = std::make_unique<Part>(j);
	}
//	friend class Game;
};

