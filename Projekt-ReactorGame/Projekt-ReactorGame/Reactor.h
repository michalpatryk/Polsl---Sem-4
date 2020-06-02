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
	
	void checkTick(TileMap& partMap) {
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

			//gain power by generators. Power sources block merging these nested loops
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
				if ((loc.x - 1) >= 0 
					&& tiles[loc.y][loc.x - 1].getPart() != nullptr)	tilesToHeatUp.push_back(tiles[loc.y][loc.x - 1]);
				if ((loc.x + 1) <= static_cast<int>(tiles[loc.y].size()) 
					&& tiles[loc.y][loc.x + 1].getPart() != nullptr)	tilesToHeatUp.push_back(tiles[loc.y][loc.x + 1]);
				if ((loc.y - 1) >= 0
					&& tiles[loc.y - 1][loc.x].getPart() != nullptr)	tilesToHeatUp.push_back(tiles[loc.y - 1][loc.x]);
				if ((loc.y + 1) <= static_cast<int>(tiles.size())
					&& tiles[loc.y + 1][loc.x].getPart() != nullptr)	tilesToHeatUp.push_back(tiles[loc.y + 1][loc.x]);

				for(auto jt:tilesToHeatUp) {
					//check if tile is heat affected. If yes, increase the heat of this part(heatUp) by base heat generation of the given
					//heat generator
					if(jt.getPart()->isHeatAffected()) {
						jt.getPart()->getPartHeatHandle()->heatUp(
							std::static_pointer_cast<HeatSource>(it.getPart())->getBaseHeatGeneration()/tilesToHeatUp.size());
					}
				}
			}
			
			//all parts are now heated up. Now is the time to use the generators and dissipate the heat
			for(auto it : tiles) {
				for(auto jt : it) {
					std::shared_ptr<Part> part = jt.getPart();
					if(part) {
						if (part->getType() == Types::Generator) {
							double heat = part->getPartHeatHandle()->getHeat();
							double heatConversionPower = std::static_pointer_cast<Generator>(part)->getBaseHeatConversion();
							if(heat-heatConversionPower < 0) {
								power += heat;
								part->getPartHeatHandle()->coolDown(heat);
							}
							else {
								power += heatConversionPower;
								part->getPartHeatHandle()->coolDown(heatConversionPower);
							}
						}
						if(part->isHeatAffected()) {
							if(part->getPartHeatHandle()->getHeat() > part->getPartHeatHandle()->getBaseMaxHeat()) {
								tiles[jt.getLocation().y][jt.getLocation().x].deletePart();
								partMap.change(jt.getLocation(), sf::Vector2i{ 0, 0 });
							}
						}
					}
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

