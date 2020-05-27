#pragma once
#include <string>

class Part
{
	std::string type;
	std::string description;
	int levels = 5;
	int level = 1;
	double basePrice;
	double costMult = 2.2;
	int isCalc;
	bool heatAffected;

	
	
};

