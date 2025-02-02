﻿#pragma once
#include "Tile.h"
#include "Clock.h"
#include <utility>
#include <vector>
#include <nlohmann/json.hpp>
#include "TileMap.h"
#include "UpgradesManager.h"
///Klasa odpowiadająca za reaktor i wszystko z nim związane - zarządzanie częściami, obliczenia ilości pieniędzy oraz energi.
class Reactor
{
	//game data
	double power = 0;
	double maxPower = 100;
	double money = 0;


	//map data
	std::vector<std::vector<Tile>> tiles;
	std::vector<int> tileMap;
	UpgradesManager upgradesManager;

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
	Clock& getClock() { return std::ref(clock); }

	///TODO function - due to bad refactor function doesnt return anything.
	void onUpgradeClick(Types type, UpgradeTypes upgradeType) {
		if (upgradesManager.upgrade(type, upgradeType, money)) {

		};
	}
	void upgradeByGuiInit(Types type, UpgradeTypes upgradeType, double multiplier, double price) {
		upgradesManager.guiUpgradeInitialize(type, upgradeType, multiplier, price);
	}
	//std::string getUpgradePrice(Types type, UpgradeTypes upgradeType) {
	//	std::string str = "Upgrade price is: ";
	//	str += std::to_string(upgradesManager.getPrice(type, upgradeType));
	//	return str;
	//}
	double getUpgradePrice(Types type, UpgradeTypes upgradeType) {
		return upgradesManager.getPrice(type, upgradeType);
	}
	int getUpgradeLevel(Types type, UpgradeTypes upgradeType) {
		return upgradesManager.getLevel(type, upgradeType);
	}
	double getUpgradeMultiplier(Types type, UpgradeTypes upgradeType) {
		return upgradesManager.getMultiplier(type, upgradeType);
	}
	//DEBUG ONLY FUNCTION - to know current ticks
	int getTick() {	return clock.getTick();}

	///Służy do manualnego wyłączenia zegara
	void reactorShutdown() {	clock.initializeShutdown();}
	std::vector<std::vector<Tile>>& getTiles() {	return tiles;}
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
	
	void upgradeClock() {
		//if(//clock.upgradeClock())
	}
};

