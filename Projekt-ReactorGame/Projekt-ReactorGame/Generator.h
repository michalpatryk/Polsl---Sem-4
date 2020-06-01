#pragma once
#include "Part.h"
class Generator :
	public Part
{
	double baseHeatConversion;
	double heat = 0;
	double baseMaxHeat;
public:
	Generator(nlohmann::json j):Part(j) {
		baseHeatConversion = j["baseHeatConversion"];
		baseMaxHeat = j["baseMaxHeat"];
	}
};

