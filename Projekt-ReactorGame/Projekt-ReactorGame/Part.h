#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "PartHeat.h"
enum class Types {
	Battery,
	Seller,
	HeatSource,
	Reflector,
	Coolant,
	Generator,
	PowerSource
};

///Klasa przedstawiająca część w grze. Przykładowe części to turbnia, bateria itp
class Part
{
protected:
	std::shared_ptr<PartHeat> partHeat;
	Types type;
	std::string model;
	std::string description;
	int level = 1;
	double basePrice;
	double costMult = 2.2;
	int isCalc = 0;
	bool heatAffected;
public:
	Part(nlohmann::json j) {
		type = j["type"];
		model = j["model"].get<std::string>();
		description = j["description"].get<std::string>();
		basePrice = j["basePrice"].get<double>();
		costMult = j["costMult"].get<double>();
		if(j.find("baseMaxHeat") != j.end()) {
			heatAffected = true;
			partHeat = std::make_shared<HeatEnabled>();
			partHeat->setBaseMaxHeat(j["baseMaxHeat"]);
		}
		else {
			heatAffected = false;
			partHeat = std::make_shared<HeatDisabled>();
		}
	}
	///Zwraca informację, czy część powinna być sprawdzana pod względem ciepła
	bool isHeatAffected() {
		return heatAffected;
	}
	Types getType() { return type; }
	double getBasePrice() { return basePrice; }
	std::shared_ptr<PartHeat> getPartHeatHandle() { return partHeat; }
};

