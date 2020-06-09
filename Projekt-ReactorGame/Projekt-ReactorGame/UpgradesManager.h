#pragma once
#include "Upgrade.h"
#include <iostream>
class UpgradesManager
{
	std::vector<Upgrade> upgrades;
	//untested
	Upgrade& findUpgrade(Types type, UpgradeTypes upgradeType) {
		for(auto&it : upgrades) {
			if(it.getUpgradeType() == upgradeType && it.getType() == type) {
				return it;
			}
		}
	}
public:
	void guiUpgradeInitialize(Types type, UpgradeTypes upgradeType, double multiplier, double price) {
		upgrades.emplace_back(Upgrade{ type, upgradeType, multiplier, price });
	}
	bool upgrade(Types type, UpgradeTypes upgradeType) {
		std::cout << getMultiplier(type, upgradeType) << std::endl;
		
		return 1;
	}
	double getMultiplier(Types type, UpgradeTypes upgradeType) { return 1; }
};

