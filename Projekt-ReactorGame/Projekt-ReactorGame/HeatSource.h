#pragma once
#include "Part.h"
#include <iostream>
class HeatSource :
	public Part
{
	double baseHeatGeneration;
	double baseDurability;
	double durability;
public:
	HeatSource(nlohmann::json j):Part(j) {
		std::cout << "123";
		baseHeatGeneration = j["baseHeatGen"];
		baseDurability = j["baseDurability"];
		durability = baseDurability;	//add upgrade handle in the future
	}
};

