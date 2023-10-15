#include "Game.h"
#include <iostream>
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

GameObject* player;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {

}

Game::~Game() {

}

void Game::Init(const char* title, int xPos, int yPos, int w, int h, bool fullscreen)
{	
	height = h;
	width = w;

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem: !!!" << std::endl;

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

	player = new GameObject("Assets/Deerly.png", 0, 0);
	map = new Map(64, 16);

}

void Game::Update()
{
	player->Update();
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	//stuff to render
	map->DrawMap();

	player->Render();


	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
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
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}