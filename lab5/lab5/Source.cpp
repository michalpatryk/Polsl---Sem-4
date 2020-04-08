#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

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

	std::cout << "\nNajmniejszy element to: " << *min_element(vecCopy.begin(), vecCopy.end())<<std::endl;
	std::cout << "Najwiekszy element to: " << *max_element(vecCopy.begin(), vecCopy.end()) << std::endl;

	std::vector<int> ftwe(20);
	std::generate(ftwe.begin(), ftwe.end(), [i = 0]()mutable{return i++; });
	std::reverse(ftwe.begin(), ftwe.end());

	std::cout << "Zawartosc ftwe: " << std::endl;
	for_each(ftwe.begin(), ftwe.end(), 
		[&](int &wartosc) {std::cout << wartosc << ", "; });
	std::cout << "\nWartosc 7: ";
	std::cout << *find(ftwe.begin(), ftwe.end(), 7);

	return 0;
}