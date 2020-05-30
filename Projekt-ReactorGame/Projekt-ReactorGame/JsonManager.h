#pragma once
#include <nlohmann/json.hpp>
#include <fstream>

#include <iomanip>
#include <iostream>
#include "Part.h"
class JsonManager
{
	nlohmann::json loadedJson;
public:
	JsonManager() {
		std::string s1("parts.json");
		loadJson(s1);
	}
	JsonManager(std::string& filename) {
		loadJson(filename);
	}
	nlohmann::json loadJson(std::string& filename) {
		std::vector<nlohmann::json> alljSon;
		std::ifstream i(filename);
		nlohmann::json j = nlohmann::json::parse(i);
		return j;
	}
};

