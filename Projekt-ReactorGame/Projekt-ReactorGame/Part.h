#pragma once
#include <string>
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
	Types type;
	std::string model;
	std::string description;
	int level = 1;
	double basePrice;
	double costMult = 2.2;
	int isCalc;
	bool heatAffected;

};

