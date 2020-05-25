#include <TGUI/TGUI.hpp>
#include <iostream>
#include <mutex>
#include <thread>
std::mutex mtx;
float test;
#include "debugFunctions.h"

class Clock{
	float clockTick=0;
public:
	explicit Clock(float clock_tick)
		: clockTick(clock_tick) {
	}

	void operator()() {
		while(1) {
			std::cout << clockTick << std::endl;
			test++;
			clockTick++;
		}
	}
	float getClockTick() const {
		mtx.lock();
		std::cout << clockTick;
		mtx.unlock();
		return clockTick;
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "TGUI window");
	window.setFramerateLimit(60);

	tgui::Gui gui(window);
	//getFullPath(("../theme/reactorGame.txt"));

	
	try
	{
		gui.loadWidgetsFromFile("../gui/reactorGame.txt");
		

	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "TGUI Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	Clock c1{10};
	std::thread t1{ c1 };
	t1.detach();
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			gui.handleEvent(event);
		}
		
		window.clear(sf::Color::White);
		gui.draw();
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Money_var"))->setText(std::to_string(1));
		std::cout << "******************************** "<< test <<std::endl;
		window.display();
	}

	return EXIT_SUCCESS;
}