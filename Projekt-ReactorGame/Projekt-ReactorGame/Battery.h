#pragma once
#include "Part.h"
class Battery :public Part
{
	double heat = 0;
	double baseMaxHeat;
	double capacity;

public:
	Battery(nlohmann::json j):Part(j) {
		baseMaxHeat = j["baseMaxHeat"];
		capacity = j["baseMaxCapacity"];
	}
	double getCapacity() {
		return capacity;
	}
};

