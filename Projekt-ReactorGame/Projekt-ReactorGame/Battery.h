#pragma once
#include "Part.h"
class Battery :public Part
{
	double capacity;
	double heat;
	double baseMaxHeat;
public:
	Battery();
};

