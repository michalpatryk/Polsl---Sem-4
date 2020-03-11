#include <iostream>
#include <stdexcept>
#include <ctime>

class Bank {
	int konto;
	int zdolnoscKredytowa;
public:
	Bank(int kwota) {
		konto = kwota;
	}
	void zaplacKarta(int kwota) {
		int randVal = rand() % 3;
		if (randVal) {
			if (kwota < konto) {
				konto -= kwota;
			}
			else {
				throw std::logic_error("Za ma³o pieniêdzy na koncie");
			}
		}
		else {
			throw std::runtime_error("Awaria p³atnosci karta!");
		}
	}

	void wezKredyt(int kwota) {
		if (kwota < zdolnoscKredytowa) {
			konto += kwota;
			zdolnoscKredytowa -= kwota;
		}
		else {
			throw std::logic_error("Za ma³a zdolnoœæ kredytowa");
		}
	}
};


int main() {
	srand(time(nullptr));
	Bank bank(300);
	
	for (int i = 0; i < 10; i++) {
		std::cout << i << ": " << std::endl;
		try {
			bank.zaplacKarta(200);
		}
		catch(std::runtime_error & e){	//blad karty
			std::cout << e.what();
		}
		catch (std::logic_error & e) {	//za malo pieniedzy

		}
	}
}