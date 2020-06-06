#pragma once
#include "Part.h"

enum class UpgradeTypes {
	MainMultiplier,
	Price,
	MaxHeat,
	MaxDurability
};

class Upgrade
{
	Types type;
	UpgradeTypes upgradeType;
	int level = 0;
	double multiplier{};
	double price{};
public:
	double getMultiplier() { return multiplier; }
	UpgradeTypes getType() { return upgradeType; }
	void upgrade() { level++; }
};

