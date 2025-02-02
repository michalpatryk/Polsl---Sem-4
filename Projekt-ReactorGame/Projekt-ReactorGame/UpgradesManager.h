﻿#pragma once
#include "Upgrade.h"
#include <iostream>
///Klasa odpowiedzialna za podawanie wartości mnożnika danego ulepszenia.
class UpgradesManager
{
	std::vector<Upgrade> upgrades;

	Upgrade* findUpgrade(Types type, UpgradeTypes upgradeType) {
		for(auto&it : upgrades) {
			if(it.getUpgradeType() == upgradeType && it.getType() == type) {
				return &it;
			}
		}
		return nullptr;
	}

public:
	void guiUpgradeInitialize(Types type, UpgradeTypes upgradeType, double multiplier, double price) {
		upgrades.emplace_back(Upgrade{ type, upgradeType, multiplier, price });
	}
	
	bool upgrade(Types type, UpgradeTypes upgradeType, double &avaliableFunds) {
		auto upgradee = findUpgrade(type, upgradeType);
		if(upgradee && avaliableFunds > upgradee->getUpgradePrice()) {
			//Order is important! Or the price will be bigger than it should be
			avaliableFunds -= upgradee->getUpgradePrice();
			upgradee->upgrade();
			return 1;
		}
		return 0;
	}
	//Wrong type return - check for bugs
	double getLevel(Types type, UpgradeTypes upgradeType) {
		auto upgradee = findUpgrade(type, upgradeType);
		if (upgradee) {
			return upgradee->getLevel();
		}
		else return 1;
	}
	double getMultiplier(Types type, UpgradeTypes upgradeType) {
		auto upgradee = findUpgrade(type, upgradeType);
		if (upgradee) {
			return upgradee->getMultiplier();
		}
		else return 1;
	}
	double getPrice(Types type, UpgradeTypes upgradeType) {
		auto upgradee = findUpgrade(type, upgradeType);
		if(upgradee) {
			return upgradee->getUpgradePrice();
		}
		else return 0;
	}
};

