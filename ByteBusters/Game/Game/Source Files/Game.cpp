#pragma once

#include "Game.h"

#include "Defines.h"

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
	//this->ui = ui;

	update = true;
	paused = false;

	window = nullptr;
	player = nullptr;
	tileRes = 32;


	
}

Game::~Game() 
{
	//delete map;
}

void Game::StopUpdate() {
	update = false;
}

void Game::StartUpdate() {
	update = true;
}

void Game::PauseUpdate() {
	paused = true;
}

void Game::ResumeUpdate() {
	paused = false;
}

bool Game::isPlayerDead() {
	if (player->GetHP() <= 0)
	{
		return true;
	}
	return false;
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

	
	//map->Innit();

	return 0;
}

void Game::Render()
{
	

	//map->DrawMap(); ///////////////////////////////////////////////// only for background now

	GameObjectManager::RenderAllGameObjects();

	//ui->RenderGameMenu();

	
}

void Game::Clean()
{
	//GameObjectManager::DestroyAllGameObjects();
	//map->Clean();

	SDL_DestroyRenderer(renderer);
	std::cout << "Game Cleaned" << std::endl;
}



void Game::HandleEvents(SDL_Event* event)
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

	std::cout << "event handling in game\n";

	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
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
		switch (event->key.keysym.sym) {
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

void Game::Start()
{
	player = GameObjectManager::CreateGameObject(GameObjectManager::player, tileRes * PLAYER_SPAWN_X, tileRes * PLAYER_SPAWN_Y); //only need pointer to call SetVelX/Y at this time
	//int currentLvl = 0;
}

void Game::UpdateThread() {

	std::cout << "Thread Created" << std::endl;

	constexpr int UPS = _UPS;
	constexpr int frameDelay = 1000 / UPS;

	Uint32 frameStart;
	int frameTime;

	while (update)
	{
		frameStart = SDL_GetTicks();
		//------------------------------------------------------------------------------
		if (!paused)
		{
			GameObjectManager::UpdateAllGameObjects();
		}
		//------------------------------------------------------------------------------
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}

	std::cout << "Thread Finished" << std::endl;
}