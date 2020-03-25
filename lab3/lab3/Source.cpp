#include <iostream>

template<typename T>
T operacja_na_liczbach(T x, T y) { return(x + y); }

template<>
double operacja_na_liczbach(double x, double y) { return (x - y); }



template<typename T>
class Tlista
{
	struct element
	{
		T data;
		element *pNext;
	};
	element *pHead;
public:
	Tlista() {
		pHead = nullptr; 
	}
	void append(T x) {
		if (pHead == nullptr) {
			element * temp = new element;
			temp->data = x;
			temp->pNext = nullptr;
			pHead = temp;
		}
		else {
			element * temp = new element;
			temp->data = x;
			temp->pNext = pHead;
			pHead = temp;
		}
	}
	void print() {
		if (pHead == nullptr) {
			std::cout << "Lista pusta" << std::endl;
			return;
		}
		else {
			element *temp = pHead;
			while (temp) {
				std::cout << temp->data << "  ";
				temp = temp->pNext;
			}
		}

	}
};

int main() {
	int x = 20, y = 10;
	int z = operacja_na_liczbach(x, y);
	double dx = 14.5, dy = 15.6;
	double dz = operacja_na_liczbach(dx, dy);
	std::cout << "Wynik z int: " << z << "\nWynik z double: " << dz << std::endl;
	std::cout << "Wynik z cast: " << (int)operacja_na_liczbach(dx, dy) << std::endl;
	Tlista <int> newLista{};
	for (int i = 0; i < 20; i++) {
		int temp = i * 10+2;
		newLista.append(temp);
	}
	newLista.print();
	return 0;
}