#include <string>
#include <nlohmann/json.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Part.h"

///Plik zawierający pliki służące jedynie w czasie tworzenia gry, nie przez samą grę.

///Funkcja zwracająca pełną ścieżkę w systemie windows. Ułatwia rozstawianie plików w solucji
void getFullPath(const std::string& str)
{
	char filename[100];
	strcpy_s(filename, str.c_str());
	char fullFilename[MAX_PATH];
	GetFullPathName(filename, MAX_PATH, fullFilename, nullptr);
	MessageBox(NULL, fullFilename, "DEBUG", MB_OK);
	return;
}

///Funkcja służąca do tworzenia nowych części. Wybierając odpowiednią kombinację jesteśmy w stanie stworzyć dowolną część.
void partDesign() {
	std::ifstream i("parts.json");
	nlohmann::json j = nlohmann::json::parse(i);
	i.close();
	nlohmann::json j2;

	
	j2["type"] = Types::Generator;
	j2["model"] = "Basic generator";
	j2["description"] = "Generates power from adjected heat sources";
	j2["basePrice"] = 10.0;
	j2["costMult"] = 1.8;
	
	//j2["baseMaxCapacity"] = 100.0;
	//j2["baseMaxSell"] = 5.0;
	j2["baseMaxHeat"] = 100.0;
	j2["baseHeatConversion"] = 10.0;
	//j2["baseHeatGen"] = 5.0;
	//j2["baseDurability"] = 100.0;

	j2["textureX"] = 5;
	j2["textureY"] = 0;
	//j2["basePowerGen"] = 1.0;

	
	j["parts"].push_back(j2);

	std::ofstream o("parts.json");
	//, std::ios::app
	o << std::setw(4) << j << std::endl;
	
}

///Funkcja pozwalająca na wczytanie i wypisanie poszczególnych części
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