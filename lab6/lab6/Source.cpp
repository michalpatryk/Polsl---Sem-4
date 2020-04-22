#include <iostream>
#include <vector>
#include <windows.h>
class ZbiornikPaliwa
{
	
public:
	unsigned int cap;
	ZbiornikPaliwa(unsigned int cap) :cap(cap) { }

	bool pobierz(unsigned int in)
	{
		if (cap < in) {
			return false;
		}
		else {
			cap -= in;
			return true;
		}
	}
};

class Silnik
{
public:
	unsigned int req_fuel;
	std::vector<std::shared_ptr<ZbiornikPaliwa>>zbiorniki;

	Silnik(unsigned int fuel)
		:req_fuel(fuel) { }

	void dodajZbiornik(std::shared_ptr<ZbiornikPaliwa>zbiornik)
	{
		zbiorniki.push_back(zbiornik);
	}
};

int main() 
{
	//Zad1
	std::unique_ptr <int> up1 = std::make_unique<int>();
	std::unique_ptr <int> up2;
	std::cout << "up1: " << up1 << "\nup2: " << up2 << std::endl;

	up2 = std::move(up1);
	std::cout << "up1: " << up1 << "\nup2: " << up2 << std::endl;

	std::cout << "\n==============================\n\n";
	//Zad2
	std::shared_ptr <int> sp1 = std::make_shared<int>();
	std::shared_ptr <int> sp2;
	std::cout << "sp1: " << sp1.use_count() << "\nsp2: " << sp2.use_count() << std::endl;
	sp2 = sp1;
	std::cout << "sp1: " << sp1.use_count() << "\nsp2: " << sp2.use_count() << std::endl;

	{
		std::shared_ptr < int > sp3 = sp2;
		std::cout << "sp1: " << sp1.use_count() << "\nsp2: " << sp2.use_count() << std::endl;
	}
	std::cout << "sp1: " << sp1.use_count() << "\nsp2: " << sp2.use_count() << std::endl;

	std::cout << "\n==============================\n\n";
	//Zad3
	std::weak_ptr <int> wp1;
	{
		std::shared_ptr <int> sp1 = std::make_shared<int>();
		wp1 = sp1;
		if (wp1.expired())
			std::cout << "Pamiec zwolniona, adres:" << wp1.lock() << std::endl;
		else
			std::cout << "Pamiec nie zwolniona, adres:" << wp1.lock() << std::endl;
	}
	std::cout << "scope exit" << std::endl;
	if (wp1.expired())
		std::cout << "Pamiec zwolniona, adres:" << wp1.lock() << std::endl;
	else
		std::cout << "Pamiec nie zwolniona, adres:" << wp1.lock() << std::endl;

	std::cout << "\n==============================\n\n";
	//Zad4

	Silnik eng1{ 5 }, eng2{ 1 }, eng3{ 2 };
	std::vector<std::shared_ptr<ZbiornikPaliwa>> storage;

	for (const int& capacity : { 12, 14, 16, 18, 20 }) {
		storage.push_back(std::make_shared<ZbiornikPaliwa>(capacity));
		eng1.dodajZbiornik(storage.back());
		eng2.dodajZbiornik(storage.back());
		eng3.dodajZbiornik(storage.back());
	}

	while (storage.size() > 0) {
		for (std::shared_ptr<ZbiornikPaliwa>& tank : storage) {
			std::vector<std::shared_ptr<ZbiornikPaliwa>>::iterator current= storage.begin();

			if (tank) {
				if (!(tank->pobierz(eng1.req_fuel)
					&& tank->pobierz(eng2.req_fuel)
					&& tank->pobierz(eng3.req_fuel))) {
					storage.erase(current);
					std::cout << "Zbiornik: " << tank << " usuniety" << std::endl;
				}
				else {
					Sleep(1000);
					std::cout << "Zostalo " << tank->cap << " w: " << tank << std::endl;
				}
			}
		}
	}
	std::cout << "Wszystkie zbiorniki puste" << std::endl;
}