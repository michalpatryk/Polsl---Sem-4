#pragma once
class PartHeat
{
public:
	virtual double getHeat() = 0;
	virtual void heatUp(double heat) = 0;
	virtual void coolDown(double heat) = 0;
};

class HeatEnabled :public PartHeat
{
	double heat = 0;
public:
	double getHeat() {
		return heat;
	}
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
	void heatUp(double heat) {}
	void coolDown(double heat) {}
};