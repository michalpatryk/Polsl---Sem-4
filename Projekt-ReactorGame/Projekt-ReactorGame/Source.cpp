#include <TGUI/TGUI.hpp>
#include <iostream>
#include "debugFunctions.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "TGUI window");
	window.setFramerateLimit(60);

	tgui::Gui gui(window);
	//getFullPath(("../theme/reactorGame.txt"));

	
	try
	{

		gui.loadWidgetsFromFile("../gui/reactorGame.txt");
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Money_var"))->setText("text");



	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "TGUI Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

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
		window.display();
	}

	return EXIT_SUCCESS;
}