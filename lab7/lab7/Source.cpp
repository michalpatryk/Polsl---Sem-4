/*

#include <thread>
#include <iostream>
#include <string>
#include <atomic>
#include <chrono>
std::atomic_flag lock = ATOMIC_FLAG_INIT;

class Reaktor {
public:
	int paliwo;
	int moc;
	std::string nazwa;
	Reaktor(int paliwo, int moc, std::string nazwa) :paliwo(paliwo), moc(moc), nazwa(nazwa) {};
	void operator()(){
		while (paliwo - moc > 0) {
			paliwo = paliwo - moc;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));	
			std::cout << "Reaktor " << nazwa << " ma " << paliwo << " paliwa" << std::endl;
		}
	}
};

class Reaktor_MK2 {
public:
	int paliwo;
	int moc;
	std::string nazwa;
	Reaktor_MK2(int paliwo, int moc, std::string nazwa) :paliwo(paliwo), moc(moc), nazwa(nazwa) {};
	void operator()() {
		while (paliwo - moc > 0) {
			paliwo = paliwo - moc;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			while (lock.test_and_set(std::memory_order_acquire));											//zad 3
			std::cout << "Reaktor " << nazwa << " ma " << paliwo << " paliwa" << std::endl;
			lock.clear(std::memory_order_release);															//zad 3
		}
	}
};

int main() {
	Reaktor pierwszy{ 1000, 200, "Blok 1" };
	Reaktor drugi{ 599, 100, "Blok 2" };
	Reaktor trzeci{ 6000, 500, "Blok 3" };
	Reaktor czwarty{ 10000, 800, "Blok 4" };

	std::thread t1{ pierwszy };
	std::thread t2{ drugi };
	std::thread t3{ trzeci };
	std::thread t4{ czwarty };


	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << "Wszystkie bloki wylaczone\n\n" << std::endl;

	Reaktor_MK2 pierwszy_MK2{ 1000, 200, "Blok 1" };
	Reaktor_MK2 drugi_MK2{ 599, 100, "Blok 2" };
	Reaktor_MK2 trzeci_MK2{ 6000, 500, "Blok 3" };
	Reaktor_MK2 czwarty_MK2{ 10000, 800, "Blok 4" };

	//t1{ pierwszy_MK2 };
	std::thread t1_MK2{ pierwszy_MK2 };
	std::thread t2_MK2{ drugi_MK2 };
	std::thread t3_MK2{ trzeci_MK2 };
	std::thread t4_MK2{ czwarty_MK2 };

	t1_MK2.join();
	t2_MK2.join();
	t3_MK2.join();
	t4_MK2.join();
	std::cout << "Wszystkie bloki klasy 2 wylaczone" << std::endl;
	return 0;
}
*/
#include <thread>
#include <iostream>
#include <string>
#include <atomic>
#include <chrono>
std::atomic_flag lock = ATOMIC_FLAG_INIT;

class Reaktor {
public:
	int paliwo;
	std::string nazwa;
	Reaktor(int paliwo, std::string nazwa) :paliwo(paliwo), nazwa(nazwa) {};
	void operator()(int moc) {
		while (paliwo - moc > 0) {
			paliwo = paliwo - moc;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::cout << "Reaktor " << nazwa << " ma " << paliwo << " paliwa" << std::endl;
		}
	}
};

class Reaktor_MK2 :public Reaktor {
public:
	Reaktor_MK2(int paliwo, std::string nazwa) :Reaktor{ paliwo, nazwa } {};
	void operator()(int moc) {
		while (paliwo - moc > 0) {
			paliwo = paliwo - moc;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			while (lock.test_and_set(std::memory_order_acquire));											//zad 3
			std::cout << "Reaktor " << nazwa << " ma " << paliwo << " paliwa" << std::endl;
			lock.clear(std::memory_order_release);															//zad 3
		}
	}
};

int main() {
	Reaktor pierwszy{ 1000, "Blok 1" };
	Reaktor drugi{ 599, "Blok 2" };
	Reaktor trzeci{ 6000, "Blok 3" };
	Reaktor czwarty{ 10000, "Blok 4" };

	std::thread t1{ pierwszy, 100 };
	std::thread t2{ drugi, 300 };
	std::thread t3{ trzeci, 250 };
	std::thread t4{ czwarty, 2000 };


	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << "Wszystkie bloki wylaczone" << std::endl;

	Reaktor_MK2 pierwszy_MK2{ 1000,  "Blok 1" };
	Reaktor_MK2 drugi_MK2{ 599,  "Blok 2" };
	Reaktor_MK2 trzeci_MK2{ 6000,  "Blok 3" };
	Reaktor_MK2 czwarty_MK2{ 10000,  "Blok 4" };

	//t1{ pierwszy_MK2 };
	std::thread t1_MK2{ pierwszy_MK2, 100 };
	std::thread t2_MK2{ drugi_MK2, 300 };
	std::thread t3_MK2{ trzeci_MK2, 250 };
	std::thread t4_MK2{ czwarty_MK2, 2000 };

	t1_MK2.join();
	t2_MK2.join();
	t3_MK2.join();
	t4_MK2.join();
	std::cout << "Wszystkie bloki klasy 2 wylaczone" << std::endl;
	return 0;
}
