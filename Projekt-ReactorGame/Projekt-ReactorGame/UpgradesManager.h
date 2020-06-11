#pragma once
#include "Upgrade.h"
#include <iostream>
class UpgradesManager
{
	std::vector<Upgrade> upgrades;
	//untested
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
		std::cout << getMultiplier(type, upgradeType) << std::endl;
		auto upgradee = findUpgrade(type, upgradeType);
		if(upgradee && avaliableFunds > upgradee->getUpgradePrice()) {
			//Order is important! Or the price will be bigger than it should be
			avaliableFunds -= upgradee->getUpgradePrice();
			upgradee->upgrade();
			return 1;
		}
		return 0;
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

