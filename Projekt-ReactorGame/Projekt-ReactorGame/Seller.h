#pragma once
#include "Part.h"
class Seller :
	public Part
{
	double baseSell;
	double heat;
	double baseMaxHeat;
public:
	Seller(nlohmann::json j):Part(j) {
		baseSell = j["baseSell"];
		baseMaxHeat = j["baseMaxHeat"];
	}
	double getBaseSell() {
		return baseSell;
	}
};

