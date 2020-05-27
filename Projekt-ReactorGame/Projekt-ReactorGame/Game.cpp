#include "Game.h"
#include "Reactor.h"
void sru() {
	std::cout << "sru";
}

int Game::run()
{
	Reactor reactor;
	window.create(vMode, "test");
	window.setFramerateLimit(60);
	tgui::Gui gui(window);
	
	int level[] =
	{
		0, TSP(3, 21), 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	};
	TileMap map;
	if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 8, 230, 200))
		return -1;
	
	try
	{
		gui.loadWidgetsFromFile("../gui/reactorGame.txt");
		std::dynamic_pointer_cast<tgui::Button>(gui.get("powerSell"))->connect("clicked", [&]() { reactor.sellPower(); });
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Money_var"))->connect("MouseEntered", sru);
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "TGUI Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	map.change(2, 2, sf::Vector2u(20, 3));
	//Clock c1{10};
	//std::thread t1{ c1 };
	//t1.detach();
	
	while (window.isOpen())
	{
		reactor.checkTick();
		
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
		streamObj << std::scientific << reactor.getMoney();
		std::string moneyVar = streamObj.str();
		streamObj.str("");
		streamObj << std::scientific << reactor.getPower();
		std::string powerVar = streamObj.str();
		
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Money_var"))->setText(moneyVar);
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Power_var"))->setText(powerVar);
		window.draw(map);
		window.display();
	}
	return EXIT_SUCCESS;
}
