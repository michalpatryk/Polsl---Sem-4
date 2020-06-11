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
	Upgrade(Types type, UpgradeTypes upgradeType, double multiplier, double price) :type(type), upgradeType(upgradeType), multiplier(multiplier),
		price(price) {	}

	double getUpgradePrice() { return price * (level + 1)*(level + 1); }
	double getMultiplier() {
		if (level == 0) return 1;
		else return multiplier * level;
	}
	UpgradeTypes getUpgradeType() { return upgradeType; }
	Types getType() { return type; }
	void upgrade() { level++; }
};

