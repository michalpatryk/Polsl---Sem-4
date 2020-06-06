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
	//Map initialization
	Reactor();

	Reactor(std::vector<int> tileMap, int width, int height);

	explicit Reactor(std::vector< std::vector<Tile>> tiles_) {
		tiles = std::move(tiles_);
	}
	double getPower() const { return power; }

	double getMoney() const { return money; }
	
	///Sprawdza, czy zegar ma jakieś nieobliczone takty. Jeżeli tak, oblicza je
	void checkTick(TileMap& partMap);

	///Kupuje wybraną część na danej lokacji
	std::string buyPart(nlohmann::json j, sf::Vector2i location, TileMap& partMap);
	///Sprzdaje część z danej lokacji
	std::string sellPart(sf::Vector2i location, TileMap& partMap);

	///Zwraca ulepszoną część. Klasa przyszłościowa, użyta tylko gdy dodane zostaje ulepszenie zmniejszające koszt części
	nlohmann::json getPostUpgradePart(nlohmann::json j) {
		return j;
	}

	///Sprzedaje całą moc po kliknięciu guziku, lub gdy mamy za mało pieniędzy - daje nam pieniądze
	void sellPower();

	///Zwraca obiekt zegara w celu jego uruchomienia w innym wątku
	Clock& getClock() {
		return std::ref(clock);
	}
	
	//DEBUG ONLY FUNCTION - to know current ticks
	int getTick() {
		return clock.getTick();
	}

	///Służy do manualnego wyłączenia zegara
	void reactorShutdown() {
		clock.initializeShutdown();
	}
	std::vector<std::vector<Tile>>& getTiles() {
		return tiles;
	}
	///Liczy maksymalną moc reaktora
	void recalculateMaxPower();

	///Zwraca koszt części
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

