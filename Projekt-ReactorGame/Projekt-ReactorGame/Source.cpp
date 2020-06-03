#include <TGUI/TGUI.hpp>
#include <iostream>
#include <mutex>
#include "TileMap.h"
#include "Game.h"
#include "debugFunctions.h"



int main()
{
	//partDesign();
	//partLoad();
	//getFullPath("tileset.png");
	const sf::VideoMode v_mode(800, 600, 32);
	Game game(v_mode);
	return(game.run());
}
