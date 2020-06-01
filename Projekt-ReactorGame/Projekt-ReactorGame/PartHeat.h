#pragma once
class PartHeat
{
protected:
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

