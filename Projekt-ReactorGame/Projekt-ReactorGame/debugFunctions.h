#include <string>
#include <nlohmann/json.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Part.h"
void getFullPath(const std::string& str)
{
	char filename[100];
	strcpy_s(filename, str.c_str());
	char fullFilename[MAX_PATH];
	GetFullPathName(filename, MAX_PATH, fullFilename, nullptr);
	MessageBox(NULL, fullFilename, "DEBUG", MB_OK);
	return;
}

void partDesign() {
	std::ifstream i("parts.json");
	nlohmann::json j = nlohmann::json::parse(i);
	i.close();
	nlohmann::json j2;

	
	j2["type"] = Types::Seller;
	j2["model"] = "Home office";
	j2["description"] = "Sells your power";
	j2["basePrice"] = 160.0;
	j2["costMult"] = 1.8;
	
	//j2["baseMaxCapacity"] = 100.0;
	j2["baseMaxSell"] = 5.0;
	j2["baseMaxHeat"] = 10.0;
	//j2["basePowerGen"] = 1.0;

	
	j["parts"].push_back(j2);

	std::ofstream o("parts.json");
	//, std::ios::app
	o << std::setw(4) << j << std::endl;
	
}

void partLoad() {
	std::vector<nlohmann::json> alljSon;
	std::ifstream i("parts.json");
	//while(i) {
	//	//i >> j;
	//	j = nlohmann::json::parse(i);
	//	std::cout << j["model"];
	//	//vj.insert(j);
	//}
	nlohmann::json j = nlohmann::json::parse(i);
	for (auto it = j["parts"].begin(); it != j["parts"].end(); ++it)
	{	
		std::cout << it.value()<<std::endl;
		//if (j.is_array())
		//{
		//	alljSon.push_back(it.value());
		//}
		//else
		//{
		//	// If it's not an array, it's an object, and from what I understood you want the key too.
		//	alljSon.push_back({ it.key(), it.value() });
		//}
	}
	//std::cout << j["parts"][0] << std::endl;

	//std::cout << Types::Battery;
}