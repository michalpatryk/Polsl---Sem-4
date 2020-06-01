#pragma once
#include "Tile.h"
#include "Clock.h"
#include <utility>
#include <vector>
#include <nlohmann/json.hpp>
#include "TileMap.h"
class Reactor
{
	//game data
	double power = 0;
	double maxPower = 100;
	double money = 0;


	//map data
	std::vector<std::vector<Tile>> tiles;
	std::vector<int> tileMap;


	//clock
	std::mutex mtx;
	Clock clock{ mtx };
public:
	///Map initialization
	Reactor();

	Reactor(std::vector<int> tileMap, int width, int height);

	explicit Reactor(std::vector< std::vector<Tile>> tiles_) {
		tiles = std::move(tiles_);
	}
	double getPower() const { return power; }

	double getMoney() const { return money; }
	
	/**	Checks if clock have any ticks, if yes it calculates all elements.
	 *
	 */
	void checkTick() {
		const int ticks = clock.getTick();
		clock.resetTick();

		for (int i = 0; i < ticks; i++) {
			//sell power by sellers
			double sellingPower = 0;
			for (const auto& it : tiles) {
				for (auto jt : it) {
					std::shared_ptr<Part> part = jt.getPart();
					if(part) {
						if (part->getType() == Types::Seller) {
							sellingPower += std::static_pointer_cast<Seller>(part)->getBaseSell();
						}
					}
				}
			}
			power -= sellingPower;
			money += sellingPower;

			//gain power by generators
			std::vector<Tile> heatGeneratorTiles;
			for (auto& it : tiles) {
				for (auto jt : it) {
					std::shared_ptr<Part> part = jt.getPart();
					if (part) {
						if (part->getType() == Types::PowerSource) {
							power += std::static_pointer_cast<PowerSource>(part)->getBasePowerGeneration();
						}
						else if(part->getType() == Types::HeatSource) {
							heatGeneratorTiles.push_back(jt);
						}
					}
				}
			}
			
			for (auto it : heatGeneratorTiles) {
				std::vector<Tile> tilesToHeatUp;
				sf::Vector2i loc = it.getLocation();
				std::cout << std::endl;
				std::cout << loc.x - 1 << "\t" << loc.x + 1 << std::endl;
				std::cout << loc.y - 1 << "\t" << loc.y + 1 << std::endl << std::endl;

				if ((loc.x - 1) >= 0)	tilesToHeatUp.push_back(tiles[loc.y][loc.x - 1]);
				if ((loc.x + 1) <= static_cast<int>(tiles[loc.x].size()))	tilesToHeatUp.push_back(tiles[loc.y][loc.x + 1]);
				if ((loc.y - 1) >= 0)	tilesToHeatUp.push_back(tiles[loc.y - 1][loc.x]);
				if ((loc.y + 1) <= static_cast<int>(tiles.size()))	tilesToHeatUp.push_back(tiles[loc.y + 1][loc.x]);
				
			}
			for(unsigned int it = 0; it < tiles.size(); it++) {
				for(unsigned int jt = 0; jt < tiles[i].size(); jt++) {
					
				}
			}
			
			power++;
		}
		if (power > maxPower) { power = maxPower; }
	}

	std::string buyPart(nlohmann::json j, sf::Vector2i location, TileMap& partMap);
	std::string sellPart(sf::Vector2i location, TileMap& partMap);

	//float getPartPrice(std::string type);
	nlohmann::json getPostUpgradePart(nlohmann::json j) {
		return j;
	}
	void sellPower() {
		if (money < 11) {
			money++;
		}
		money += power;
		power = 0;

	}

	//used to start a clock thread
	Clock& getClock() {
		return std::ref(clock);
	}
	//DEBUG ONLY FUNCTION - to know current ticks
	int getTick() {
		return clock.getTick();
	}

	void reactorShutdown() {
		clock.initializeShutdown();
	}
	std::vector<std::vector<Tile>>& getTiles() {
		return tiles;
	}

	void recalculateMaxPower() {
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

	double getFullPrice(nlohmann::json j) {
		return j["basePrice"].get<double>();
	}
	double getFullPrice(Types type, double price) {
		return price;
		//add upgrades handle here
		//return j["basePrice"].get<float>();
	}
	double getMaxPower() { return maxPower; }
};

