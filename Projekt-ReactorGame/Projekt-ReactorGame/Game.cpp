#include "Game.h"

int Game::run()
{
	window.create(vMode, "test");
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
	//Clock c1{10};
	//std::thread t1{ c1 };
	//t1.detach();
	
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
		std::ostringstream streamObj;

		//streamObj << std::scientific << test;

		std::string strObj = streamObj.str();
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Money_var"))->setText(strObj);
		window.display();
	}
	return EXIT_SUCCESS;
}
