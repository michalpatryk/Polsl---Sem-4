#pragma once
#include <TGUI/TGUI.hpp>
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
};

