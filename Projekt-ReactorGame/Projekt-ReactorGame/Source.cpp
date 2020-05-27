#include <TGUI/TGUI.hpp>
#include <iostream>
#include <mutex>
#include "TileMap.h"
#include "Game.h"
#include "debugFunctions.h"



int main()
{
	//getFullPath("tileset.png");
	const sf::VideoMode v_mode(1024, 800, 32);
	Game game(v_mode);
	return(game.run());
}
