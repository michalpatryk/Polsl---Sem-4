#include "Game.h"


int Game::run()
{
	window.create(vMode, "test");
	window.setFramerateLimit(60);
	tgui::Gui gui(window);
	bool txtBoxChanged = true;

	level = levelGenerator("Default");
	loadPartsJson("parts.json");

	TileMap map;
	if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 9, 230, 200))
		return -1;
	TileMap partMap;
	if (!partMap.load("partsTileset.png", sf::Vector2u(32, 32), std::vector<int>(144, 0), 16, 9, 230, 200))
		return -1;


	Reactor reactor{ level, 16, 9 };
	try{
		guiInitialize(gui, txtBoxChanged, reactor);
	}
	catch (const tgui::Exception& e){
		std::cerr << "TGUI Exception: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	//start reactor clock
	std::thread clockThread(std::ref(reactor.getClock()));

	while (window.isOpen())
	{
		reactor.checkTick(partMap);

		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				reactor.reactorShutdown();
				clockThread.join();
			}
			if(!gui.get("Group1")->isVisible()) {
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.key.code == sf::Mouse::Left) {
						if (map.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {	//check if mouse buttone pressed on tilemap
							std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(
								reactor.buyPart(getTypeJson(selectedPart), map.clickedCoordinates(sf::Mouse::getPosition(window)), partMap));
							std::dynamic_pointer_cast<tgui::Label>(gui.get("MaxPower_var"))->setText(labelMaxPowerText(reactor));
						}
					}
					else if (event.key.code == sf::Mouse::Right) {
						if (map.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
							std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(
								reactor.sellPart(map.clickedCoordinates(sf::Mouse::getPosition(window)), partMap));
							std::dynamic_pointer_cast<tgui::Label>(gui.get("MaxPower_var"))->setText(labelMaxPowerText(reactor));
						}
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
					if (map.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
						std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(
							reactor.buyPart(getTypeJson(selectedPart), map.clickedCoordinates(sf::Mouse::getPosition(window)), partMap));
						std::dynamic_pointer_cast<tgui::Label>(gui.get("MaxPower_var"))->setText(labelMaxPowerText(reactor));
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
					if (map.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
						std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(
							reactor.sellPart(map.clickedCoordinates(sf::Mouse::getPosition(window)), partMap));
						std::dynamic_pointer_cast<tgui::Label>(gui.get("MaxPower_var"))->setText(labelMaxPowerText(reactor));
					}
				}
			}			
			gui.handleEvent(event);
		}

		if (txtBoxChanged == true) {
			std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(textBoxText());
			txtBoxChanged = false;
		}

		
		std::ostringstream streamObj;
		streamObj << std::scientific << reactor.getMoney();
		std::string moneyVar = streamObj.str();
		streamObj.str("");
		streamObj << std::scientific << reactor.getPower();
		//streamObj << std::scientific << reactor.getTickCounter();
		std::string powerVar = streamObj.str();
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Money_var"))->setText(moneyVar);
		std::dynamic_pointer_cast<tgui::Label>(gui.get("Power_var"))->setText(powerVar);
		std::dynamic_pointer_cast<tgui::Label>(gui.get("MaxPower_var"))->setText(labelMaxPowerText(reactor));
		
		window.clear(sf::Color::White);
		window.draw(map);
		window.draw(partMap);
		gui.draw();
		window.display();
	}
	return EXIT_SUCCESS;
}

void upgradeGuiOnClick(Types type, UpgradeTypes upgradeType, Reactor& reactor) {
	reactor.onUpgradeClick(type, upgradeType);
};

void Game::guiInitialize(tgui::Gui& gui, bool& txtBoxChanged, Reactor& reactor) {
	gui.loadWidgetsFromFile("../gui/reactorGame.txt");
	std::dynamic_pointer_cast<tgui::Label>(gui.get("MaxPower_var"))->setText(labelMaxPowerText(reactor));
	std::dynamic_pointer_cast<tgui::Button>(gui.get("powerSell"))->connect("clicked", [&]() { reactor.sellPower(); });
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("Wind turbine"))->connect(
		"clicked", [&]() {
		selectedPart = "Wind turbine";
		txtBoxChanged = true;
	});
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("Basic Battery"))->connect(
		"clicked", [&]() {
		selectedPart = "Basic Battery";
		txtBoxChanged = true;
	});
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("Home office"))->connect(
		"clicked", [&]() {
		selectedPart = "Home office";
		txtBoxChanged = true;
	});
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("Solar cell"))->connect(
		"clicked", [&]() {
		selectedPart = "Solar cell";
		txtBoxChanged = true;
	});
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("Basic generator"))->connect(
		"clicked", [&]() {
		selectedPart = "Basic generator";
		txtBoxChanged = true;
	});
	std::dynamic_pointer_cast<tgui::Button>(gui.get("UpgradesMenu"))->connect("clicked", [&]() {
		gui.get("Group1")->setVisible(!gui.get("Group1")->isVisible());
	});

	

	//Initializing upgrade menu - the simplest way, as opposed to complex, json initialized part setup
	reactor.upgradeByGuiInit(Types::PowerSource, UpgradeTypes::MainMultiplier, 2.0, 50);
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("UpgradeWindTurbine"))->connect(
		"clicked", upgradeGuiOnClick, Types::PowerSource, UpgradeTypes::MainMultiplier, std::ref(reactor));

	//On hover
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("UpgradeWindTurbine"))->connect(
		"mouseEntered", [&]() {
		std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(
			onUpgradeHoverTextBoxText(Types::PowerSource, UpgradeTypes::MainMultiplier, reactor));
	});
	
	reactor.upgradeByGuiInit(Types::Generator, UpgradeTypes::MainMultiplier, 2.0, 100);
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("UpgradeGenerator"))->connect(
		"clicked", upgradeGuiOnClick, Types::Generator, UpgradeTypes::MainMultiplier, std::ref(reactor));

	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("UpgradeGenerator"))->connect(
		"mouseEntered", [&]() {
		std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(
			onUpgradeHoverTextBoxText(Types::Generator, UpgradeTypes::MainMultiplier, reactor));
	});

	reactor.upgradeByGuiInit(Types::HeatSource, UpgradeTypes::MainMultiplier, 2.0, 120);
	//upgradeGuiOnClick(Types::HeatSource, UpgradeTypes::MainMultiplier, "UpgradeSolarCell", gui, reactor);
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("UpgradeSolarCell"))->connect(
		"clicked", upgradeGuiOnClick, Types::HeatSource, UpgradeTypes::MainMultiplier, std::ref(reactor));
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("UpgradeSolarCell"))->connect(
		"mouseEntered", [&]() {
		std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(
			onUpgradeHoverTextBoxText(Types::HeatSource, UpgradeTypes::MainMultiplier, reactor));
	});
	
	reactor.upgradeByGuiInit(Types::Battery, UpgradeTypes::MainMultiplier, 2.0, 100);
	//cant simplify: need to recalculate battery
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("UpgradeBattery"))->connect(
		"clicked", [&]() {
		reactor.onUpgradeClick(Types::Battery, UpgradeTypes::MainMultiplier);
		reactor.recalculateMaxPower();
	});
	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get("UpgradeBattery"))->connect(
		"mouseEntered", [&]() {
		std::dynamic_pointer_cast<tgui::TextBox>(gui.get("TextBox1"))->setText(
			onUpgradeHoverTextBoxText(Types::Battery, UpgradeTypes::MainMultiplier, reactor));
	});
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
//void Game::upgradeGuiOnClick(Types type, UpgradeTypes upgradeType, std::string partName, tgui::Gui & gui, Reactor & reactor)
//{
//	std::dynamic_pointer_cast<tgui::ClickableWidget>(gui.get(partName))->connect(
//		"clicked", [&]() {
//		reactor.onUpgradeClick(type, upgradeType);
//	});
//}


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

std::string Game::onUpgradeHoverTextBoxText(Types type, UpgradeTypes upgradeType, Reactor& reactor)
{
	std::ostringstream oss;
	oss << "Upgrade price: " << reactor.getUpgradePrice(type, upgradeType) << std::endl;
	oss << "Current level: " << reactor.getUpgradeLevel(type, upgradeType) << std::endl;
	oss << "Current multiplier: " << reactor.getUpgradeMultiplier(type, upgradeType) << std::endl;
	std::string str = oss.str();
	
	return str;
}

std::string Game::labelMaxPowerText(Reactor& reactor) {
	std::ostringstream streamObj;
	streamObj << std::scientific << reactor.getMaxPower();
	std::string maxPowerVar = streamObj.str();
	return maxPowerVar;
}

nlohmann::json Game::getTypeJson(std::string type) {
	for (auto it = partsJson["parts"].begin(); it != partsJson["parts"].end(); ++it) {
		if (it.value()["model"] == type) {
			return it.value();
		}
	}
	throw std::runtime_error("Part does not exist!");
}
