#pragma once
#include "Upgrade.h"
class UpgradesManager
{
	std::vector<Upgrade> upgrades;
public:
	bool upgrade(Types type, UpgradeTypes upgradeType) { return 1; }
	double getMultiplier(Types type, UpgradeTypes upgradeType) { return 1; }
};

