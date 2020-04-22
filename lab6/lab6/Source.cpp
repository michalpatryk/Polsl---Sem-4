#include <vector>
#include <iostream>
int main() {
	//Zad1
	std::unique_ptr <int> p1 = std::make_unique<int>();
	std::unique_ptr <int> p2;
	std::cout << "p1: " << p1 << "\np2: " << p2 << std::endl;

	p2 = std::move(p1);
	std::cout << "p1: " << p1 << "\np2: " << p2 << std::endl;

	//Zad2
}