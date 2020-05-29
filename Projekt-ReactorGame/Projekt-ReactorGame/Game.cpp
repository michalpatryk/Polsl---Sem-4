#include "Game.h"
#include "Reactor.h"
void sru() {
	std::cout << "sru";
}

//void level1(std::vector<int>level) {
//	level = {
//		0, 486, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
//		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
//		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
//		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
//		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
//		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
//		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//		1, 1, 1, 1, 3, 4, 1, 5, 4, 4, 3, 2, 1, 2, 3, 4
//	};
//}


int Game::run()
{
	
	window.create(vMode, "test");
	window.setFramerateLimit(60);
	tgui::Gui gui(window);
	
	std::vector<int> a2 = { 1, 2, 3 };
	level = levelGenerator("Default");

	TileMap map;
	if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 9, 230, 200))
		return -1;
	bool exit = false;
	Reactor reactor{ level, 16, 9 };
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
	
	//start reactor clock
	std::thread clockThread(std::ref(reactor.getClock()));

	while (window.isOpen())
	{
		reactor.checkTick();
		
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				reactor.reactorShutdown();
				clockThread.join();
			}				
			gui.handleEvent(event);
		}
		
		window.clear(sf::Color::White);
		
		gui.draw();
		std::ostringstream streamObj;
		streamObj << std::scientific << reactor.getMoney();
		std::string moneyVar = streamObj.str();
		streamObj.str("");
		streamObj << std::scientific << reactor.getPower();
		//streamObj << std::scientific << reactor.getTickCounter();
		std::string powerVar = streamObj.str();
		std::cout << reactor.getTick();
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Money_var"))->setText(moneyVar);
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Power_var"))->setText(powerVar);

		window.draw(map);
		window.display();
	}
	return EXIT_SUCCESS;
}

inline std::vector<int> Game::levelGenerator(std::string levelType) {
	std::vector<int> level;
	if (levelType == "Default") {
		level = {
			486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486,
			486, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 486, 486,
			486, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 486,
			486, 486, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 486,
			486, 486, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 486, 486,
			486, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 486, 486,
			486, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 486, 486, 486,
			486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486,
			486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486, 486
		};
	}
	return level;
}
