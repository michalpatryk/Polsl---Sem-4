#pragma once
#include <TGUI/TGUI.hpp>
#include "TileMap.h"
#include <nlohmann/json.hpp>
#include "JsonManager.h"
#include <iostream>
#include "Reactor.h"
class Game
{
	sf::RenderWindow window{};
	sf::VideoMode vMode{};
	std::vector<int> level;
	std::string selectedPart = "null";
	nlohmann::json partsJson;
	JsonManager jsonManager;

public:
	explicit Game(const sf::VideoMode VMode) {
		vMode = VMode;
	};
	int run();
	int TSP(int x, int y) { return(x + y * 23); }
	void loadPartsJson(std::string filename) { partsJson = jsonManager.loadJson(filename); }
	std::vector<int> levelGenerator(std::string levelType);
	std::string textBoxText() {
		nlohmann::json j = getTypeJson(selectedPart);
		std::ostringstream oss;
		oss << j["model"].get<std::string>() << ":	" << j["description"].get<std::string>() << std::endl;
		oss << "Price:	" << j["basePrice"].get<float>() << std::endl;
		
		if (j["type"] == Types::Battery) {
			oss << "Capacity:	" << j["baseMaxCapacity"] << std::endl;		//!get multipliers from reactor
		}
		if (j["type"] == Types::PowerSource) {
			oss << "Power generation:	" << j["basePowerGen"] << std::endl;		//!get multipliers from reactor
		}
		std::string a = oss.str();
		return a;
	}

	nlohmann::json getTypeJson(std::string type);

};

