﻿#pragma once
#include "Part.h"
#include <iostream>
///Generuje ciepło
class HeatSource :
	public Part
{
	double baseHeatGeneration;
	double baseDurability;
	double durability;
public:
	HeatSource(nlohmann::json j):Part(j) {
		baseHeatGeneration = j["baseHeatGen"];
		baseDurability = j["baseDurability"];
		durability = baseDurability;	//add upgrade handle in the future
	}
	double getBaseHeatGeneration(){
		return baseHeatGeneration;
	}
};

