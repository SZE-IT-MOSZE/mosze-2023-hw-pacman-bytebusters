#pragma once
#include "Game.h"
#include <iostream>

int main(int argc, char* argv[]) {

	Game* game = new Game();

	if (game->Init() != 0)
	{
		std::cout << "Game initialization failed. Application quitting. \n";
		delete game;
		return -1;
	}

	game->MainLoop(); // only returns if the application is quitting

	delete game;

	std::cout << _CrtDumpMemoryLeaks();

	return 0;
}

