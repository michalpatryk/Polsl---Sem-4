#pragma once
#include "Part.h"
class Battery :
	public Part
{
	//double heat = 0;
	//double baseMaxHeat;
	double capacity;

public:
	Battery(nlohmann::json j):Part(j) {
		//baseMaxHeat = j["baseMaxHeat"];
		capacity = j["baseCapacity"];
	}
	double getCapacity() {
		return capacity;
	}
	/*double getHeat() {
		return heat;
	}
	void heatUp(double heat) {
		this->heat += heat;
	}
	void coolDown(double heat) {
		this->heat -= heat;
	}*/
};

