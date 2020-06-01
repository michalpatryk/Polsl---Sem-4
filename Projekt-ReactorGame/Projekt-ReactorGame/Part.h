#pragma once
#include <string>
#include <nlohmann/json.hpp>
enum class Types {
	Battery,
	Seller,
	HeatSource,
	Reflector,
	Coolant,
	Generator,
	PowerSource
};


class Part
{
protected:
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
		if(j["baseMaxHeat"].get<float>()) {
			heatAffected = true;
		}
		else heatAffected = false;
	}
	Types getType() { return type; }
};

