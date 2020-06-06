#pragma once
#include "Part.h"
///Zmienia ciepło w energię
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
	double getBaseHeatConversion() { return baseHeatConversion; }
};

