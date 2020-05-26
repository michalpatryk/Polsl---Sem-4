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
	//getFullPath(("../theme/reactorGame.txt"));
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
		window.display();
	}
	return EXIT_SUCCESS;
}
