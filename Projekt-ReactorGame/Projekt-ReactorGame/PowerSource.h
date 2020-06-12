#pragma once
#include "Part.h"
///Generuje energię
class PowerSource :
	public Part
{
	float heat = 0;
	//float baseMaxHeat;
	float basePowerGeneration;
public:
	PowerSource(nlohmann::json j):Part(j) {
	//	baseMaxHeat = j["baseMaxHeat"];
		basePowerGeneration = j["basePowerGeneration"];
	}
	float getBasePowerGeneration() const { return basePowerGeneration; }
};

