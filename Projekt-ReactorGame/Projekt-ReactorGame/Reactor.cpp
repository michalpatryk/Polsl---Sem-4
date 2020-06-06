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

void Reactor::checkTick(TileMap& partMap) {
	const int ticks = clock.getTick();
	clock.resetTick();


	for (int i = 0; i < ticks; i++) {
		//sell power by sellers
		//! Take it to the back
		double sellingPower = 0;
		for (const auto& it : tiles) {
			for (auto jt : it) {
				std::shared_ptr<Part> part = jt.getPart();
				if (part) {
					if (part->getType() == Types::Seller) {
						sellingPower += std::static_pointer_cast<Seller>(part)->getBaseSell();
					}
				}
			}
		}

		//gain power by generators. Power sources block merging these nested loops
		std::vector<Tile> heatGeneratorTiles;
		for (auto& it : tiles) {
			for (auto jt : it) {
				std::shared_ptr<Part> part = jt.getPart();
				if (part) {
					if (part->getType() == Types::PowerSource) {
						power += std::static_pointer_cast<PowerSource>(part)->getBasePowerGeneration();
					}
					else if (part->getType() == Types::HeatSource) {
						heatGeneratorTiles.push_back(jt);
					}
				}
			}
		}

		for (auto it : heatGeneratorTiles) {
			std::vector<Tile> tilesToHeatUp;
			sf::Vector2i loc = it.getLocation();
			if ((loc.x - 1) >= 0
				&& tiles[loc.y][loc.x - 1].getPart() != nullptr)
				tilesToHeatUp.push_back(tiles[loc.y][loc.x - 1]);
			if ((loc.x + 1) <= static_cast<int>(tiles[loc.y].size())
				&& tiles[loc.y][loc.x + 1].getPart() != nullptr)
				tilesToHeatUp.push_back(tiles[loc.y][loc.x + 1]);
			if ((loc.y - 1) >= 0
				&& tiles[loc.y - 1][loc.x].getPart() != nullptr)
				tilesToHeatUp.push_back(tiles[loc.y - 1][loc.x]);
			if ((loc.y + 1) <= static_cast<int>(tiles.size())
				&& tiles[loc.y + 1][loc.x].getPart() != nullptr)
				tilesToHeatUp.push_back(tiles[loc.y + 1][loc.x]);

			for (auto jt : tilesToHeatUp) {
				//check if tile is heat affected. If yes, increase the heat of this part(heatUp) by base heat generation of the given
				//heat generator
				if (jt.getPart()->isHeatAffected()) {
					jt.getPart()->getPartHeatHandle()->heatUp(
						std::static_pointer_cast<HeatSource>(it.getPart())->getBaseHeatGeneration() / tilesToHeatUp.
						size());
				}
			}
		}

		//all parts are now heated up. Now is the time to use the generators and dissipate the heat
		for (auto it : tiles) {
			for (auto jt : it) {
				std::shared_ptr<Part> part = jt.getPart();
				if (part) {
					if (part->getType() == Types::Generator) {
						double heat = part->getPartHeatHandle()->getHeat();
						double heatConversionPower = std::static_pointer_cast<Generator>(part)->getBaseHeatConversion();
						if (heat - heatConversionPower < 0) {
							power += heat;
							part->getPartHeatHandle()->coolDown(heat);
						}
						else {
							power += heatConversionPower;
							part->getPartHeatHandle()->coolDown(heatConversionPower);
						}
					}
					if (part->isHeatAffected()) {
						if (part->getPartHeatHandle()->getHeat() > part->getPartHeatHandle()->getBaseMaxHeat()) {
							tiles[jt.getLocation().y][jt.getLocation().x].deletePart();
							partMap.change(jt.getLocation(), sf::Vector2i{0, 0});
						}
					}
				}
			}
		}


		power++;
		if (power - sellingPower > 0) {
			power -= sellingPower;
			money += sellingPower;
		}
		else {
			money += power;
			power = 0;
		}
		if (power > maxPower) { power = maxPower; }
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

void Reactor::sellPower() {
	if (money < 11 && power < 11) {
		money++;
	}
	money += power;
	power = 0;

}

void Reactor::recalculateMaxPower() {
	maxPower = 100;
	for (const auto& it : tiles) {
		for (auto jt : it) {
			std::shared_ptr<Part> part = jt.getPart();
			if (part) {
				if (part->getType() == Types::Battery) {
					maxPower += std::static_pointer_cast<Battery>(part)->getCapacity();
				}
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
