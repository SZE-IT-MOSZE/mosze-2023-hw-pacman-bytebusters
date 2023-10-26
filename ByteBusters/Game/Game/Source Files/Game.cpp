#include "Game.h"
#include <iostream>
#include "TextureManager.h"
#include "GameObject.h"
#include <thread>
#include "Player.h"
#include "Enemy.h"


SDL_Renderer* Game::renderer;


Game::Game() {
	height = 480; // default is smallest res
	width = 640;
	tileRes = 32;
	isRunning = false;
	window = nullptr;

}

Game::~Game() {
	//looks too empty, youre forgetting things
	delete map;
}

void Game::Init(const char* title, int xPos, int yPos, int w, int h, int tR, bool fullscreen)
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

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	TextureManager::LoadAllTextures(); /*/////////////////////////////////*/

	GameObjectManager::SetTileSize(tileRes);

	player = GameObjectManager::CreateGameObject(GameObjectManager::player, tileRes, tileRes); // Items in map need player ref, create player before map

	map = new Map(tileRes, 16);

	GameObjectManager::CreateGameObject(GameObjectManager::soldier, tileRes*10, tileRes*10);
	GameObjectManager::CreateGameObject(GameObjectManager::deer, tileRes * 10, tileRes * 10);
	GameObjectManager::CreateGameObject(GameObjectManager::homeless, tileRes * 10, tileRes * 10);
	GameObjectManager::CreateGameObject(GameObjectManager::ape, tileRes * 10, tileRes * 10);
	//for (size_t i = 0; i < 100; i++) // invasion of the yusri
	//{
	//	GameObjectManager::CreateGameObject(GameObjectManager::yusri, tileRes * 10, tileRes * 10);
	//}


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
	GameObjectManager::DestroyAllGameObjects(); //causes critcical error !?
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			player->SetVelX(-1);
			break;
		case SDLK_RIGHT:
			player->SetVelX(1);
			break;
		case SDLK_UP:
			player->SetVelY(-1);
			break;
		case SDLK_DOWN:
			player->SetVelY(1);
			break;
		default:
			break;
		}
		break;

	case SDL_KEYUP:
		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			player->SetVelX(0);
			break;
		case SDLK_RIGHT:
			player->SetVelX(0);
			break;
		case SDLK_UP:
			player->SetVelY(0);
			break;
		case SDLK_DOWN:
			player->SetVelY(0);
			break;
		default:
			break;
		}
		break;


	case SDL_QUIT:
		
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::UpdateThread() {
	std::cout << "Thread Created" << std::endl;
	std::cout << tileRes << std::endl;

	const int UPS = tileRes * 3;
	const int frameDelay = 1000 / UPS;

	Uint32 frameStart;
	int frameTime;

	while (isRunning)
	{
		frameStart = SDL_GetTicks();

		//player->Update(); ////////////////////////////////////////
		//enemy->Update();

		GameObjectManager::UpdateAllGameObjects();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	std::cout << "Thread Finished" << std::endl;

}