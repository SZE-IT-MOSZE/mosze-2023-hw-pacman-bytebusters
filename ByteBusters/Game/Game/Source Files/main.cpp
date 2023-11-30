#pragma once
#include "Game.h"
#include <iostream>

int main(int argc, char* argv[]) {

	std::shared_ptr<Game> game = Game::GetInstance();

	if (game->Init() != 0)
	{
		std::cout << "Game initialization failed. Application quitting. \n";
		return -1;
	}

	game->MainLoop(); // only returns if the application is quitting

	std::cout << _CrtDumpMemoryLeaks();

	return 0;
}

