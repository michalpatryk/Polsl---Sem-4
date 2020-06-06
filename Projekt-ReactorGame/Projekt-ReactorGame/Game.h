#pragma once
#include <TGUI/TGUI.hpp>
#include "TileMap.h"
#include <nlohmann/json.hpp>
#include "JsonManager.h"
#include <iostream>
#include "Reactor.h"
///Główna klasa gry - odpowiada za malowanie wszystkich obiektów na ekran oraz obsługę interakcji z graczem
class Game
{
	sf::RenderWindow window{};
	sf::VideoMode vMode{};
	std::vector<int> level;
	std::vector<int> parts;
	std::string selectedPart = "Wind turbine";
	nlohmann::json partsJson;
	JsonManager jsonManager;

public:
	explicit Game(const sf::VideoMode VMode) {
		vMode = VMode;
	};
	int run();
	int TSP(int x, int y) { return(x + y * 23); }
	void guiInitialize(tgui::Gui& gui, bool& txtBoxChanged, Reactor& reactor);
	void loadPartsJson(std::string filename) { partsJson = jsonManager.loadJson(filename); }
	std::vector<int> levelGenerator(std::string levelType);

	std::string textBoxText();

	std::string labelMaxPowerText(Reactor& reactor);
	nlohmann::json getTypeJson(std::string type);

};

