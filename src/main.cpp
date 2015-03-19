#include "Game.hpp"

#include <stdexcept>
#include <iostream>

int WinMain()
{

	Game game;
	game.Init();
	game.Run();
	game.Close();
	
	return 0;
}