#include "Game.h"

void sru() {
	std::cout << "sru" << std::endl;
}

void sru2(int i) {
	std::cout << "sru: " << i << std::endl;
}


int Game::run()
{
	window.create(vMode, "test");
	window.setFramerateLimit(60);
	tgui::Gui gui(window);
	bool txtBoxChanged = false;

	level = levelGenerator("Default");
	loadPartsJson("parts.json");

	TileMap map;
	if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 9, 230, 200))
		return -1;
	
	Reactor reactor{ level, 16, 9 };
	try
	{
		gui.loadWidgetsFromFile("../gui/reactorGame.txt");
		std::dynamic_pointer_cast<tgui::Button>(gui.get("powerSell"))->connect("clicked", [&]() { reactor.sellPower(); });
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Money_var"))->connect("MouseEntered", sru);
		std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("Wind turbine"))->connect(
			"clicked", [&]() { selectedPart = "Wind turbine"; txtBoxChanged = true; });
		std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("Basic Battery"))->connect(
			"clicked", [&]() { selectedPart = "Basic Battery"; txtBoxChanged = true; });
		std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("Home office"))->connect(
			"clicked", [&]() { selectedPart = "Home office"; txtBoxChanged = true; });
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
			if (event.type == sf::Event::MouseButtonPressed) {
				if(event.key.code == sf::Mouse::Left) {
					//if(sf::Mouse::getPosition().x > )
				}
			}
			gui.handleEvent(event);
		}
		//optimize me
		if(txtBoxChanged == true)	std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(textBoxText());
		//std::cout << getTypeJson(selectedPart);
		window.clear(sf::Color::White);
		//reactor.buyPart(partsJson[selectedPart]);
		gui.draw();
		std::ostringstream streamObj;
		streamObj << std::scientific << reactor.getMoney();
		std::string moneyVar = streamObj.str();
		streamObj.str("");
		streamObj << std::scientific << reactor.getPower();
		//streamObj << std::scientific << reactor.getTickCounter();
		std::string powerVar = streamObj.str();
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

std::string Game::textBoxText() {
	nlohmann::json j = getTypeJson(selectedPart);
	std::ostringstream oss;
	oss << j["model"].get<std::string>() << ":	" << j["description"].get<std::string>() << std::endl;
	oss << "Price:	" << j["basePrice"].get<float>() << std::endl;

	if (j["type"] == Types::Battery) {
		oss << "Capacity:	" << j["baseMaxCapacity"] << std::endl; //!get multipliers from reactor
	}
	if (j["type"] == Types::PowerSource) {
		oss << "Power generation:	" << j["basePowerGen"] << std::endl; //!get multipliers from reactor
	}
	std::string a = oss.str();
	return a;
}

nlohmann::json Game::getTypeJson(std::string type) {
	for (auto it = partsJson["parts"].begin(); it != partsJson["parts"].end(); ++it) {
		if (it.value()["model"] == type) {
			return it.value();
		}
	}
	throw std::runtime_error("Part does not exist!");
}
