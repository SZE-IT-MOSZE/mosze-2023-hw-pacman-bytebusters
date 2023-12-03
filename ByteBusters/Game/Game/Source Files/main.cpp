#pragma once
#include "Game.h"
#include <iostream>

int CustomScope() {
	std::shared_ptr<Game> game = Game::GetInstance();

	if (game->Init() != 0)
	{
		std::cout << "Game initialization failed. Application quitting. \n";
		return -1;
	}

	game->MainLoop(); // only returns if the application is quitting
}

int main(int argc, char* argv[]) {
	
	CustomScope();

	if (_CrtDumpMemoryLeaks())
	{
		std::cout << "MEMORY LEAKS DETECTED !!!\n";
	} 
	else {
		std::cout << "No memory leaks.\n";
	}

	return 0;
}