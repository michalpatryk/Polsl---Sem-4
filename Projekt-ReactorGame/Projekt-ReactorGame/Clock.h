#pragma once
#include <mutex>  
#include <iostream>
//std::mutex mtx;
///Klasa odpowiadająca za zarządzanie, czy powinna wykonać się tura (tick) gry. Jest przystosowana do pracy w wątkach
class Clock {
	///Licznik nieobsłużonych ticków zegara
	int tick = 0;
	///Aktualny poziom zegara. Im wyższy, tym szybciej działa zegar
	int level = 5;
	///Flaga sprawdzająca, czy należy wyłączyć zegar
	bool shutdown = false;
	std::mutex &mtx;

	///Usypia zegar na ustawiony okres czasu
	void wait() {
		double waitTime = (1000 * (1.0 - level / 8.0));
		int time = static_cast<int>(waitTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}
public:
	Clock(std::mutex& mutex) :mtx(mutex){};
	//Debug functions: pretty useless
	//void incrementTick() {
	//	//std::lock_guard<std::mutex> lck(mtx);
	//	tick++;
	//}
	//void decrementTick(std::mutex &mtx) {
	//	std::lock_guard<std::mutex> lck(mtx);
	//	tick--;
	//}

	///Ulepsza zegar. Ulepszenie zegara na poziom 8 spowowdowałoby dzielenie przez zero, co całkowicie zniszczyłoby grę
	bool upgradeClock() {
		if (level < 8) {
			level++;
			return true;
		}
		else return false;
	}

	///Resetuje zegar - używane przez klasę reactor po zczytaniu liczby ticków
	void resetTick() {
		std::lock_guard<std::mutex> lck(mtx);
		tick = 0;
	}

	int getTick() const {
		std::lock_guard<std::mutex> lck(mtx);
		return tick;
	}

	///Inicjalizacja wyłączenia zegara. Po włączeniu, zegar nie powinien być już używany
	void initializeShutdown() {
		shutdown = true;
	}
	///Funckcja przekazywana do std::thread, odpowiada za zwiększanie liczby ticków
	void operator()() {
		while(true) {
			mtx.lock();
			tick++;
			mtx.unlock();
			if (shutdown == true) return;
			wait();
			//std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}
	
};