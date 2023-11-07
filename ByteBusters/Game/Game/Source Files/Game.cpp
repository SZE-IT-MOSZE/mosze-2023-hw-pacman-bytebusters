#pragma once

#include "Game.h"
#include "Defines.h"


SDL_Renderer* Game::renderer;

Game::Game() {
	height = 480; // default is smallest res
	width = 640;
	tileRes = 32;
	isRunning = true;
	isPlaying = false;
	window = nullptr;

}

Game::~Game() {
	//looks too empty, youre forgetting things
	delete map;
}

bool Game::Init(const char* title, int xPos, int yPos, int w, int h, int tR, bool fullscreen)
{	
	height = h;
	width = w;
	tileRes = tR;
	

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem:" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			std::cout << "Renderer created!" << std::endl;
		}
	}
	else {
		return false;
	}

	TextureManager::LoadAllTextures(); /*/////////////////////////////////*/

	GameObjectManager::SetTileSize(tileRes);

	map = new Map(tileRes);

	return true;
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	map->DrawMap(); ///////////////////////////////////////////////// only for background now

	GameObjectManager::RenderAllGameObjects();

	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	GameObjectManager::DestroyAllGameObjects();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}
SDL_Event event;
void Game::HandleEvents()
{
	/*
	IMPORTANT !!!

	According to SDL documentation the KEYDOWN and KEYUP events should 
	only occure once when the key is pressed down or released, however, 
	the event triggeres once when the key is pressed/released, then 
	after a short delay (~0.5s) the event is constantly triggered for seemingly
	no reason. This caused weird glitches, thus the following system had to be implemented:

	-The KEYDOWN event inserts (and keeps trying to insert) a value into a <set> which can only contain that value once.
	-If the set contains that value, a respective fuction is called. 
	-The KEYUP event removes that value from the set.

	// May expand later to only trigger once when the key is pressed or released, how it should actually work, but for now it functions fine.
	
	// Might be my fault that this happenes, but I dont know why.

	*/

	
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			isPressed.insert('a');
			break;
		case SDLK_RIGHT:
			isPressed.insert('d');
			break;
		case SDLK_UP:
			isPressed.insert('w');
			break;
		case SDLK_DOWN:
			isPressed.insert('s');
			break;
		case SDLK_y:
			isPressed.insert('y');
			break;
		case SDLK_x:
			isPressed.insert('x');
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			isPressed.erase('a');
			break;
		case SDLK_RIGHT:
			isPressed.erase('d');
			break;
		case SDLK_UP:
			isPressed.erase('w');
			break;
		case SDLK_DOWN:
			isPressed.erase('s');
			break;
		case SDLK_y:
			isPressed.erase('y');
			break;
		case SDLK_x:
			isPressed.erase('x');
			break;
		default:
			break;
		}
		break;

	case SDL_QUIT:
		
		isPlaying = false;
		isRunning = false;

		break;
	default:
		break;
	}
	//////////////////////////////////////////////////////////
	if (isPressed.contains('w')) {
		//std::cout << "w" << std::endl;
		player->SetVelY(-1);
	}
	//////////////////////////////////////////////////////////
	if (isPressed.contains('a')) {
		//std::cout << "a" << std::endl;
		player->SetVelX(-1);
	}
	//////////////////////////////////////////////////////////
	if (isPressed.contains('s')) {
		//std::cout << "s" << std::endl;
		player->SetVelY(1);
	}
	//////////////////////////////////////////////////////////
	if (isPressed.contains('d')) {
		//std::cout << "d" << std::endl;
		player->SetVelX(1);
	}
	//////////////////////////////////////////////////////////
	if (!isPressed.contains('d') && !isPressed.contains('a')) { // stop if none
		player->SetVelX(0);
	}
	//////////////////////////////////////////////////////////
	if (!isPressed.contains('w') && !isPressed.contains('s')) { // stop if none
		player->SetVelY(0);
	}
	//////////////////////////////////////////////////////////
	if (isPressed.contains('y')) {
		player->Shoot();
	}
	if (isPressed.contains('x')) {
		player->Hit();
	}
	//////////////////////////////////////////////////////////
}

void Game::Start()
{

	const int FPS = _FPS;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// generally better to create player before everything, as player is pointer that can be null, while the rest are in lists that exist from the beggining as an empty list empty and get filled in later
	player = GameObjectManager::CreateGameObject(GameObjectManager::player, tileRes * PLAYERSPAWNX, tileRes * PLAYERSPAWNY); //only need pointer to call SetVelX/Y at this time

	int currentLvl = 1;

	while(isRunning)
	{
		map->LoadMap(currentLvl);

		isPlaying = true;
										
		gameUpdates = new std::thread(&Game::UpdateThread, this); // pointer to non-static member function (Game:: necessary), pointer to object (this)

		while (isPlaying)
		{
			frameStart = SDL_GetTicks();
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			HandleEvents();
			Render();
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (GameObjectManager::AreAllItemsPickedUp())
			{
				isPlaying = false; // stop both update and render
				SDL_Delay(2000); // some delay between two maps

			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);

		}
		gameUpdates->join(); // wait for update

		GameObjectManager::DestroyAllExceptPlayer();
		player->Reset();
		currentLvl++;
		if (currentLvl > MAPS) isRunning = false;
	}
}

void Game::UpdateThread() {

	std::cout << "Thread Created" << std::endl;

	const int UPS = _UPS;
	const int frameDelay = 1000 / UPS;

	Uint32 frameStart;
	int frameTime;

	while (isPlaying)
	{
		frameStart = SDL_GetTicks();
		////////////////////////////////////////////////////////////////////////////
		GameObjectManager::UpdateAllGameObjects();
		////////////////////////////////////////////////////////////////////////////
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	std::cout << "Thread Finished" << std::endl;
}