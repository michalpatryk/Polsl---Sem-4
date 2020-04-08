#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
	srand(time(NULL));
	std::vector<int> vec;
	for (int i = 0; i < 20; i++) {
		vec.push_back(rand() % 100);
	}
	std::vector<int> vecCopy(20);
	std::copy(vec.begin(), vec.end(), vecCopy.begin());
	std::sort(vecCopy.begin(), vecCopy.end());

	std::cout << "Przed sortowaniem: " << std::endl;
	std::for_each(vec.begin(), vec.end(),
		[&](int &var) {std::cout << var << ", "; });
	std::cout << "\nPo sortowaniu: " << std::endl;
	std::for_each(vecCopy.begin(), vecCopy.end(),
		[&](int &var) {std::cout << var << ", "; });

	std::cout << "\nNajmniejszy element to: " << *min_element(vecCopy.begin(), vecCopy.end()) << std::endl;
	std::cout << "Najwiekszy element to: " << *max_element(vecCopy.begin(), vecCopy.end()) << std::endl;
	//zad 2--------------------------------------------
	std::vector<int> ftwe(20);
	std::generate(ftwe.begin(), ftwe.end(), [i = 0]()mutable{return i++; });
	std::reverse(ftwe.begin(), ftwe.end());

	std::cout << "Zawartosc ftwe: " << std::endl;
	for_each(ftwe.begin(), ftwe.end(),
		[&](int &wartosc) {std::cout << wartosc << ", "; });
	std::cout << "\nWartosc 7: ";
	std::cout << *find(ftwe.begin(), ftwe.end(), 7);
	std::cout << std::endl;

	std::vector<int> ften(10);
	std::generate(ften.begin(), ften.end(), [i = 0]()mutable{return i++; });
	//zad3------------------------------------------
	std::cout << "Zad 3: " << std::endl;
	std::vector<int>::iterator it;
	for (it = ften.begin(); it != ften.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::vector<int>::reverse_iterator ri;
	for (ri = ften.rbegin(); ri != ften.rend(); ri++) {
		std::cout << *ri << " ";
	}
	std::cout << std::endl;

	std::vector<int> vfive(5);
	std::generate(vfive.begin(), vfive.end(), [i = 0]()mutable{return i++; });
	std::vector<int>::iterator vfi = vfive.begin();
	std::copy(ften.begin(), ften.end(), std::inserter(vfive, vfi));
	for (vfi = vfive.begin(); vfi != vfive.end(); vfi++) {
		std::cout << *vfi << " ";
	}
	return 0;
}