#include "Reactor.h"

bool Reactor::buyPart(std::string type) {
	if (money > getPartPrice(type)) return true;
	else return false;
}

float Reactor::getPartPrice(std::string type) {
	float price;
	if (type == "uranium x1") price = 10;
	else if (type == "uranium x2") price = 22;

	
	return (price);
}
