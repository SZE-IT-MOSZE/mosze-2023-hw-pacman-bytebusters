#pragma once
#include "Defines.h"
#include "SDL.h"
#include "Game.h"
//#include <thread>
//#include <forward_list>
//#include <vector>
#include "generateMaze.h"
#include "GameObjectManager.h"
#include <iostream>

Game* game = nullptr;


int main(int argc, char* argv[]) {
	
	if ((SDL_Init(SDL_INIT_VIDEO) == -1)) {
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		return -1;
	}

	SDL_DisplayMode dm;

	if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
	{
		SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
		return -1;
	}

	int screenResWidth, screenResHeight; // these are scaled resolutions, not screen size in pixels
	screenResWidth = dm.w;
	screenResHeight = dm.h;


	int gameResWidth, gameResHeight, tileRes;
	if (screenResHeight <= 480) {
		std::cout << "SCREEN TOO SMALL. GAME CANNOT BE STARTED." << std::endl;
		return -1;
	}
	else if (screenResHeight <= 720) {
		tileRes = 32;
	}
	else if (screenResHeight <= 960) {
		tileRes = 48;
	}
	else if (screenResHeight <= 1200) {
		tileRes = 64;
	}
	else if (screenResHeight <= 1440) {
		tileRes = 80;
	}
	else if (screenResHeight <= 1680) {
		tileRes = 112;
	}
	else { // this fits 4K
		tileRes = 128;
	}
	gameResHeight = tileRes * 15; //map size again
	gameResWidth = tileRes * 20;  //map size again

	//15*32 = 480
	//15*48 = 720
	//15*64 = 960
	//15*80 = 1200
	//15*96 = 1440
	//15*112 = 1680
	//15*128 = 1920

	srand(time(NULL)); // only intitialize srand once

	generateMaze(); // call before game->Init

	if (!Game::Init("DEER-MURDER-HORROR-BLOOD-GORE (The Game)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameResWidth, gameResHeight, tileRes, false))
	{
		return 1;
	}

	Game::Start();

	Game::Clean();

	//std::cout << _CrtDumpMemoryLeaks();

	return 0;
}

