#pragma once

#include "Game.h"

#include "Defines.h"

SDL_Renderer* Game::renderer = nullptr;

Game::Game() 
{
	window = nullptr;
	map = nullptr;
	player = nullptr;
	gameUpdates = nullptr;
	tileRes = 32;
	isRunning = true;
	isPlaying = false;
}

Game::~Game() 
{
	delete map;
}

void Game::SetPlaying(bool p) 
{
	isPlaying = false;
}

int Game::Init(SDL_Window* window,const int tileRes)
{	
	this->window = window;

	

	this->tileRes = tileRes;

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer)
	{
		std::cout << "Renderer created!" << std::endl;
	}
	else 
	{
		std::cout << "Renderer creation failed!" << std::endl;
		return -1;
	}

	TextureManager::LoadAllTextures(); /*/////////////////////////////////*/

	GameObjectManager::SetTileSize(tileRes);

	map = new Map(tileRes);

	map->Innit();

	return 0;
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
	map->Clean();

	SDL_DestroyRenderer(renderer);
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
	
	// Might be my fault that this happenes, but I dont know why. :/

	*/

	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				//std::cout << "LEFT \n";
				pressedKeys.insert('a');
				break;
			case SDLK_RIGHT:
				//std::cout << "RIGHT \n";
				pressedKeys.insert('d');
				break;
			case SDLK_UP:
				//std::cout << "UP \n";
				pressedKeys.insert('w');
				break;
			case SDLK_DOWN:
				//std::cout << "DOWN \n";
				pressedKeys.insert('s');
				break;
			case SDLK_y:
				pressedKeys.insert('y');
				break;
			case SDLK_x:
				pressedKeys.insert('x');
				break;
			default:
				break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				pressedKeys.erase('a');
				break;
			case SDLK_RIGHT:
				pressedKeys.erase('d');
				break;
			case SDLK_UP:
				pressedKeys.erase('w');
				break;
			case SDLK_DOWN:
				pressedKeys.erase('s');
				break;
			case SDLK_y:
				pressedKeys.erase('y');
				break;
			case SDLK_x:
				pressedKeys.erase('x');
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
		if (pressedKeys.contains('w')) {
			//std::cout << "w" << std::endl;
			player->SetVelY(-1);
		}
		//////////////////////////////////////////////////////////
		if (pressedKeys.contains('a')) {
			//std::cout << "a" << std::endl;
			player->SetVelX(-1);
		}
		//////////////////////////////////////////////////////////
		if (pressedKeys.contains('s')) {
			//std::cout << "s" << std::endl;
			player->SetVelY(1);
		}
		//////////////////////////////////////////////////////////
		if (pressedKeys.contains('d')) {
			//std::cout << "d" << std::endl;
			player->SetVelX(1);
		}
		//////////////////////////////////////////////////////////
		if (!pressedKeys.contains('d') && !pressedKeys.contains('a')) { // stop if none
			player->SetVelX(0);
		}
		//////////////////////////////////////////////////////////
		if (!pressedKeys.contains('w') && !pressedKeys.contains('s')) { // stop if none
			player->SetVelY(0);
		}
		//////////////////////////////////////////////////////////
		if (pressedKeys.contains('y')) {
			player->Shoot();
		}
		if (pressedKeys.contains('x')) {
			player->Hit();
		}
		//////////////////////////////////////////////////////////

	}
}

void Game::Start()
{
	

	constexpr int FPS = _FPS;
	constexpr int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	// generally better to create player before everything, as player is pointer that can be null, while the rest are in lists that exist from the beggining as an empty list empty and get filled in later
	player = GameObjectManager::CreateGameObject(GameObjectManager::player, tileRes * PLAYER_SPAWN_X, tileRes * PLAYER_SPAWN_Y); //only need pointer to call SetVelX/Y at this time
	std::cout << "game tile size" << tileRes << "\n";
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
#ifdef DO_RENDER
			Render();
#endif // DO_RENDER
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (GameObjectManager::AreAllItemsPickedUp())
			{
				isPlaying = false; // stop both update and render
				SDL_Delay(2000); // some delay between two maps
				currentLvl++;
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (player->GetHP() <= 0)
			{
				isPlaying = false; // stop both update and render without going to next map
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);

		}

		gameUpdates->join(); // wait for update if it didnt finish already
		delete gameUpdates;

		GameObjectManager::DestroyAllExceptPlayer();
		player->Reset();
		if (currentLvl > MAPS) isRunning = false;
	}
}

void Game::UpdateThread() {

	std::cout << "Thread Created" << std::endl;

	constexpr int UPS = _UPS;
	constexpr int frameDelay = 1000 / UPS;

	Uint32 frameStart;
	int frameTime;

	while (isPlaying)
	{
		frameStart = SDL_GetTicks();
		////////////////////////////////////////////////////////////////////////////
		
#ifdef DO_UPDATE
		GameObjectManager::UpdateAllGameObjects();
#endif // DISABLE_UPDATE

		////////////////////////////////////////////////////////////////////////////
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	std::cout << "Thread Finished" << std::endl;
}