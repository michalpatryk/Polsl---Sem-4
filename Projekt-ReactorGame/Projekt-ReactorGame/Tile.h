#pragma once
#include "Coordinates.h"
#include  "Part.h"
#include "PowerSource.h"
#include "Battery.h"
#include "Seller.h"
#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>


#include "Generator.h"
#include "HeatSource.h"

enum class TileType{buildable, unbuildable};

class Tile
{
	sf::Vector2i location;
	TileType tileType;
	std::shared_ptr<Part> part{};

public:
	Tile() {
		location = sf::Vector2i{ 0,0 };
		tileType = TileType::buildable;
	}



	Tile(sf::Vector2i location_, TileType tileType_) {
		location = location_;
		tileType = tileType_;

	}
	///Tworzy część z przesłanego pliku json
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
		case Types::Generator:
			part = std::make_shared<Generator>(j);
			break;
		default:
			throw std::runtime_error("Can't create part: Type not specified");
		}
	}
	
	void deletePart(){
		part = nullptr;
	}
	std::shared_ptr<Part> getPart() {
		return part;
	}
	TileType getTileType() {
		return tileType;
	}
	sf::Vector2i getLocation() const {
		return location;
	}

};

