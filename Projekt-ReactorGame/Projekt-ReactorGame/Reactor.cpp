#include "Reactor.h"

Reactor::Reactor() {
	tiles.resize(10);
	for (int i = 0; i < 10; i++) {
		tiles[i].resize(10);
		for (int j = 0; j < 10; j++) {
			tiles[i][j] = Tile{ sf::Vector2i{i, j}, TileType::buildable};
		}
	}
}

Reactor::Reactor(std::vector<int> tileMap, int width, int height): tileMap(tileMap), width(width), height(height) {
	tiles.resize(height);
	for (int i = 0; i < height; i++) {
		tiles[i].resize(width);
		for (int j = 0; j < width; j++) {
			if (tileMap[i * width + j] == 47) {
				tiles[i][j] = Tile{ sf::Vector2i{i, j}, TileType::buildable};
			}
			else {
				tiles[i][j] = Tile{ sf::Vector2i{i, j}, TileType::unbuildable};
			}
		}
	}
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
