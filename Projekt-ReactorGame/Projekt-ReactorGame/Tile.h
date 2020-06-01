#pragma once
#include "Coordinates.h"
#include  "Part.h"
#include "PowerSource.h"
#include "Battery.h"
#include "Seller.h"
#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>

#include "HeatSource.h"

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
		switch ((Types)j["type"]) {
		case Types::PowerSource:
			part = std::make_shared<PowerSource>(j);
			break;
		case Types::Battery:
			part = std::make_shared<Battery>(j);
			break;
		case Types::Seller:
			part = std::make_shared<Seller>(j);
			break;
		case Types::HeatSource:
			part = std::make_shared <HeatSource>(j);
			break;
		default:
			throw std::runtime_error("Can't create part: Type not specified");
		}
	}
	
	void deletePart(){
		part = nullptr;
	}
	std::shared_ptr<Part> getPart() {
		//std::cout << part.use_count();;
		return part;
	}
	TileType getTileType() {
		return tileType;
	}
//	friend class Game;
};

