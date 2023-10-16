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

	player = new GameObject("Assets/Deerly.png", 0, 0); //tileRes needs to be included
	map = new Map(tileRes, 16);

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

//read velocity everyy frame in a separete function
//set velocity based on keyevents
//handle collisions based in velocity->new position every frame
//this way the inputs and the collision detection is separated
//same will be true for enemies and other game object
//only their velocity will be set and thir position updated every frame based on that
// !!! framerate independent velocity ???