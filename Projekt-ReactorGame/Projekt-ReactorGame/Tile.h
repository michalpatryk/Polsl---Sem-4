#pragma once
#include "Coordinates.h"
#include  "Part.h"
#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>

enum class TileType{buildable, unbuildable};

class Tile
{
	sf::Vector2i location;
	TileType tileType;
	std::shared_ptr<Part> part{};
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
		part = std::make_shared<Part>(j);
	}
	void deletePart(){
		part = nullptr;
	}
	std::shared_ptr<Part> getPart() {
		std::cout << part.use_count();;
		return part;
	}
	TileType getTileType() {
		return tileType;
	}
//	friend class Game;
};

