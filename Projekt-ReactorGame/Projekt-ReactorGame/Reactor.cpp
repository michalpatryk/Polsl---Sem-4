#include "Reactor.h"

Reactor::Reactor() {
	tiles.resize(10);
	for (int i = 0; i < 10; i++) {
		tiles[i].resize(10);
		for (int j = 0; j < 10; j++) {
			tiles[i][j] = Tile{ sf::Vector2i{j, i}, TileType::buildable};
		}
	}
}

Reactor::Reactor(std::vector<int> tileMap, int width, int height): tileMap(tileMap){
	tiles.resize(height);
	for (int i = 0; i < height; i++) {
		tiles[i].resize(width);
		for (int j = 0; j < width; j++) {
			if (tileMap[i * width + j] == 47) {
				tiles[i][j] = Tile{ sf::Vector2i{j, i}, TileType::buildable};
			}
			else {
				tiles[i][j] = Tile{ sf::Vector2i{j, i}, TileType::unbuildable};
			}
		}
	}
}

std::string Reactor::buyPart(nlohmann::json j, sf::Vector2i location, TileMap& partMap) {
	auto tile = tiles[location.y][location.x];
	if (tile.getTileType() == TileType::buildable) {
		if (tile.getPart() == nullptr) {
			if (money >= getFullPrice(j)) {
				money -= getFullPrice(j);
				tiles[location.y][location.x].createPart(j);
				partMap.change(location, sf::Vector2i{j["textureX"], j["textureY"]});

				if(j["type"] == Types::Battery) {
					recalculateMaxPower();
				}
				
				return (j["model"].get<std::string>() += " built!");
			}
			else return "Not enough money";
		}
		else return "There is already a part here!";
	}
	else return "You can't build on this tile!";

	return ".";
}

std::string Reactor::sellPart(sf::Vector2i location, TileMap& partMap) {
	auto tile = tiles[location.y][location.x];
	if (tile.getTileType() == TileType::buildable) {
		if (tile.getPart() != nullptr) {
			money += getFullPrice(tile.getPart()->getType(), tile.getPart()->getBasePrice());
			tiles[location.y][location.x].deletePart();
			partMap.change(location, sf::Vector2i{ 0, 0 });

			if (tile.getPart()->getType() == Types::Battery) {
				recalculateMaxPower();
			}
			
			return "Part sold";
		}
		else return "There is nothing here!";
	}
	else return "You can't even build there!";
}

//
//bool Reactor::buyPart(std::string type) {
//	if (money > getPartPrice(type)) return true;
//	else return false;
//}
//
//float Reactor::getPartPrice(std::string type) {
//	float price;
//	if (type == "uranium x1") price = 10;
//	else if (type == "uranium x2") price = 22;
//
//	
//	return (price);
//}
