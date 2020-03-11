#include <typeinfo>
#include <iostream>

class Firma
{
public:
	int do_uregulowania = 0;

	void uregulowane()
	{
		do_uregulowania = 0;
	}

	virtual ~Firma() = default;

};
class Dostawca : public Firma
{
public:
	virtual void dostawa() = 0;
};

class Nabywca : public Firma
{
public:
	virtual void sprzedaz() = 0;
};

class Detal : public Nabywca
{
	void sprzedaz() override
	{
		do_uregulowania += 1000;
	}
};

class Hurt : public Nabywca
{
	void sprzedaz() override
	{
		do_uregulowania += 20000;
	}
};

class Komputery : public Dostawca
{
	void dostawa() override
	{
		do_uregulowania -= 20000;
	}
};

class Sluchawki : public Dostawca
{
	void dostawa() override
	{
		do_uregulowania -= 1000;
	}
};

int main() {
	Komputery kom, kom2, kom3;
	Sluchawki slu;
	Hurt hur;
	Detal det, det2;

	Firma *tFirmy[] = { &kom, &kom2, &kom3, &slu, &hur, &det, &det2 };

	for (auto firma : tFirmy) {
		Nabywca *nab = dynamic_cast<Nabywca*>(firma);

		if (nab != nullptr) {
			nab->sprzedaz();
			std::cout << "Nabywca: ";
		}

		Dostawca *dos = dynamic_cast<Dostawca*>(firma);

		if (dos != nullptr) {
			dos->dostawa();
			std::cout << "Dostawca: ";
		}


		std::cout << typeid(*firma).name() << ": " << firma->do_uregulowania << std::endl;
	}
}


