#pragma once
#include <TGUI/TGUI.hpp>
#include "TileMap.h"
#include <iostream>

class Game
{
	sf::RenderWindow window{};
	sf::VideoMode vMode{};
public:
	explicit Game(const sf::VideoMode VMode) {
		vMode = VMode;
	};
	int run();
	int TSP(int x, int y) { return(x + y * 23); }
};

