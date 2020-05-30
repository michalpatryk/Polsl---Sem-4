#pragma once
#include <TGUI/TGUI.hpp>
#include "TileMap.h"
#include <nlohmann/json.hpp>
#include <iostream>
class Game
{
	sf::RenderWindow window{};
	sf::VideoMode vMode{};
	std::vector<int> level;
	
public:
	explicit Game(const sf::VideoMode VMode) {
		vMode = VMode;
	};
	int run();
	int TSP(int x, int y) { return(x + y * 23); }
	std::vector<int> levelGenerator(std::string levelType);

};

