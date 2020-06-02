#pragma once
class PartHeat
{
public:
	virtual double getHeat() = 0;
	virtual double getBaseMaxHeat() = 0;
	virtual void setBaseMaxHeat(double baseMaxHeat) = 0;
	virtual void heatUp(double heat) = 0;
	virtual void coolDown(double heat) = 0;
};

class HeatEnabled :public PartHeat
{
	double heat = 0;
	double baseMaxHeat;
public:
	double getHeat() {
		return heat;
	}
	double getBaseMaxHeat() {
		return baseMaxHeat;
	}
	void setBaseMaxHeat(double baseMaxHeat) { this->baseMaxHeat = baseMaxHeat; }
	void heatUp(double heat) {
		this->heat += heat;
	}
	void coolDown(double heat) {
		this->heat -= heat;
	}
};

class HeatDisabled :public PartHeat
{
public:
	double getHeat() {	return 0;	}
	double getBaseMaxHeat() { return 0; }
	void setBaseMaxHeat(double baseMaxHeat){}
	void heatUp(double heat) {}
	void coolDown(double heat) {}
};