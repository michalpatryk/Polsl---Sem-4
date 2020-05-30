#pragma once
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "Part.h"
class JsonManager
{
public:
	nlohmann::json loadJson() {
		std::vector<nlohmann::json> alljSon;
		std::ifstream i("parts.json");
		nlohmann::json j = nlohmann::json::parse(i);
		return j;
	}
};

