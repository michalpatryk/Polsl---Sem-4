#include <iostream>
#include <stdexcept>
#include <ctime>

class Bank {
	int konto;
	int zdolnoscKredytowa = 600;
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
				throw std::logic_error("Za malo pieniedzy na koncie\n");
			}
		}
		else {
			throw std::runtime_error("Awaria platnosci karta!\n");
		}
	}

	void wezKredyt(int kwota) {
		if (kwota < zdolnoscKredytowa) {
			konto += kwota;
			zdolnoscKredytowa -= kwota;
		}
		else {
			throw std::logic_error("Za mala zdolnosc kredytowa\n");
		}
	}
};


int main() {
	srand(time(nullptr));
	Bank bank(700);
	
	for (int i = 0; i < 10; i++) {
		std::cout << i << ": " << std::endl;
		try {
			bank.zaplacKarta(200);
		}
		catch(std::runtime_error & e){	//blad karty
			std::cout << e.what();
		}
		catch (std::logic_error & e) {	//za malo pieniedzy
			try {
				bank.wezKredyt(200);
				try {
					bank.zaplacKarta(200);
					std::cout << "Platnosc karta kredytowa" << std::endl;
				}
				catch (...) {
					std::cout << "Za mala zdolnosc kredytowa" << std::endl;
				}
			}
			catch (std::logic_error &e2) {
				std::cout << e2.what();
			}
		}
	}
}