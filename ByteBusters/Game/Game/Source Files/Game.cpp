#pragma once
#include "Game.h"
#include "Defines.h"
#include "generateMaze.h"

SDL_Renderer* Game::renderer{ nullptr };

std::weak_ptr<Game> Game::instance_;
std::mutex Game::mutex_;

std::shared_ptr<Game> Game::GetInstance() {
	std::lock_guard<std::mutex> lock(mutex_);
	std::shared_ptr<Game> sharedInstance;
	if (!(sharedInstance = instance_.lock())) {
		sharedInstance = std::shared_ptr<Game>(new Game());
		instance_ = sharedInstance;
	}
	return sharedInstance;
}

Game::Game()
{
	isRunning = true;
	inMenu = true;
	isPlaying = false;

	update = true;
	paused = false;
	confirmPause = paused;

	window = nullptr;
	map = nullptr;
	ui = nullptr;
	gameUpdates = nullptr;
	player = nullptr;
	tileRes = 32;
}

Game::~Game() 
{
	SDL_DestroyRenderer(renderer);
}

int Game::Init()
{	
	window = Window::GetInstance();
	if (window->Init(WINDOWTITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false) != 0)
	{
		std::cout << "Game initialization failed.\n";
		return -1;
	} 
	// SDL comes to life here

	tileRes = window->GetTileRes();

	renderer = SDL_CreateRenderer(window->GetWindow(), -1, 0);
	if (renderer)
	{
		std::cout << "Renderer created.\n";
	}
	else 
	{
		std::cout << "Could not create renderer.\n";
		return -1;
	}
	//Rederer works here

	TextureManager::LoadAllTextures(); // Needs initialized SDL and working Renderer to load textures

	ui = UI::GetInstance(window->GetTileRes());
	if (ui->Init() != 0)
	{
		std::cout << "Game initialization failed.\n";
		return -1;
	}

	gom = GameObjectManager::GetInstance(tileRes);
	map = Map::GetInstance(tileRes);

	std::cout << "Game ready.\n";
	return 0;
}

void Game::MainLoop()
{
	srand((unsigned int)time(NULL)); // only intitialize srand once

	constexpr int FPS = _FPS;
	constexpr int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	int currentLvl = 0;

	SDL_Event event;

	Uint32 UI_EVENT = ui->Get_UI_EVENT();

	while (isRunning) // the application is running
	{
		while (inMenu) { // the user is in the menu

			frameStart = SDL_GetTicks();
			//------------------------------------------------------------------------------
			while(SDL_PollEvent(&event)) {

				if (event.type == SDL_QUIT)
				{
					inMenu = false;
					isRunning = false;
					break;
				}
				if (event.type == UI_EVENT)
				{
					switch (event.user.code)
					{
						case EVENT_START:
							inMenu = false;
							isPlaying = true;
							currentLvl = STARTERLEVEL;
							std::cout << "Level " << currentLvl << "\n";
							generateMaze();
						break;
						case EVENT_LOAD:
							inMenu = false;
							isPlaying = true;
							currentLvl = map->LoadMapNumber();
							if (currentLvl > MAPS || currentLvl < 1) // could be integrated into load function
							{
								std::cout << "Loading save failed.\n";
								currentLvl = 1;
							}
							std::cout << "Level " << currentLvl << "\n";
						break;
					}
				}
				ui->HandleMainMenuEvents(&event);
			}
			//------------------------------------------------------------------------------
			SDL_RenderClear(Game::renderer);
			ui->RenderMainMenu();
			SDL_RenderPresent(Game::renderer);
			//------------------------------------------------------------------------------
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
		}

		if (!isRunning) break; // dont go further if the user has quit the application
		
		if (player)
		{
			player->Reset();
		}
		else 
		{
			player = gom->CreateGameObject(GameObjectManager::player, tileRes * PLAYER_SPAWN_X, tileRes * PLAYER_SPAWN_Y); //only need pointer to call SetVelX/Y at this time
		}
		map->LoadMap(currentLvl);
		gameUpdates = std::make_unique<std::thread>(&Game::UpdateThread, this); // pointer to non-static member function (Game:: necessary), pointer to object (this)
		while (isPlaying) { // the user is in the game
			frameStart = SDL_GetTicks();
			//------------------------------------------------------------------------------
			while(SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
				{
					StopUpdate(); // return only on stop, join within function
					isPlaying = false;
					isRunning = false;
					break;
				}
				if (event.type == UI_EVENT)
				{
					switch (event.user.code) {
					case EVENT_SAVE:
						map->SaveMapNumber(currentLvl); // no break on purpose
					case EVENT_MENU:
						StopUpdate();
						isPlaying = false;
						inMenu = true;
						break;
					default:
						break;
					}
					
				}
				HandleKeyEvents(&event);
				ui->HandleGameMenuEvents(&event);
			}
			if (!isPlaying) break;
			//------------------------------------------------------------------------------
			SDL_RenderClear(Game::renderer);
			map->DrawMap();
			gom->RenderAllGameObjects();
			ui->SetHP(player->GetHP());
			ui->RenderGameMenu();
			SDL_RenderPresent(Game::renderer);
			//------------------------------------------------------------------------------
			if (gom->AreAllItemsPickedUp())
			{
				if (currentLvl < 10) 
				{
					PauseUpdate(); // only returns if paused (no join, theread is waiting, it didnt quit)
					gom->DestroyAllExceptPlayer();
					player->Reset();
					++currentLvl;
					map->LoadMap(currentLvl);
					std::cout << "Level " << currentLvl << "\n";
					ResumeUpdate();
				}
				else if (gom->AreJosephAndYusriDead())
				{
					StopUpdate();
					isPlaying = false;
					inMenu = true;
					break; // break here as we are quitting the loop
				}
			}
			//------------------------------------------------------------------------------
			if (player->GetHP() <= 0)
			{
				PauseUpdate(); // only returns if paused (no join, theread is waiting, it didnt quit)
				gom->DestroyAllExceptPlayer();
				player->Reset();
				map->LoadMap(currentLvl);
				ResumeUpdate();
			}
			//------------------------------------------------------------------------------
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
		}
		gom->DestroyAllExceptPlayer();
	}
}

void Game::StopUpdate() {
	paused = true;
	update = false;
	gameUpdates->join();
}

void Game::PauseUpdate() {
	paused = true;
	while (!confirmPause);
}

void Game::ResumeUpdate() {
	paused = false;
}

void Game::UpdateThread() {

	std::cout << "Thread Created.\n";

	constexpr int UPS = _UPS;
	constexpr int frameDelay = 1000 / UPS;

	Uint32 frameStart;
	int frameTime;
	
	update = true;
	paused = false;
	confirmPause = paused;

	while (update)
	{
		confirmPause = paused;
		SDL_Delay(100);
		while (!paused) {
			frameStart = SDL_GetTicks();
			//------------------------------------------------------------------------------
			gom->UpdateAllGameObjects();
			//------------------------------------------------------------------------------
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
		}
		
	}

	std::cout << "Thread Quit.\n";

}

void Game::HandleKeyEvents(SDL_Event* event)
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

	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
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
		switch (event->key.keysym.sym) {
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

	default:
		break;
	}
	//////////////////////////////////////////////////////////
	if (isPressed.contains('w')) {
		player->SetVelY(-1);
	}
	//////////////////////////////////////////////////////////
	if (isPressed.contains('a')) {
		player->SetVelX(-1);
	}
	//////////////////////////////////////////////////////////
	if (isPressed.contains('s')) {
		player->SetVelY(1);
	}
	//////////////////////////////////////////////////////////
	if (isPressed.contains('d')) {
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