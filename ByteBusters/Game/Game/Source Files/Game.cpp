#pragma once
#include "Defines.h"
#include "Game.h"
#include "generateMaze.h"
#include "Defines.h"

SDL_Renderer* Game::renderer{ nullptr };

std::shared_ptr<Game> Game::pinstance_{ nullptr };
std::mutex Game::mutex_;

std::shared_ptr<Game> Game::GetInstance() {
	std::lock_guard<std::mutex> lock(mutex_);
	if (!pinstance_) {
		pinstance_ = std::make_shared<Game>();
	}
	return pinstance_;
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
	delete window;
	delete map;
	delete ui;
	std::cout << "Game destroctor called \n";
}

int Game::Init()
{	
	window = new Window();
	if (window->Init("DEER - MURDER - HORROR - BLOOD - GORE(The Game)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false) != 0)
	{
		std::cout << "Window creation failed. \n";
		delete window;  //safe clean
		return -1;
	}

	this->tileRes = window->GetTileRes();

	renderer = SDL_CreateRenderer(window->GetWindow(), -1, 0);
	if (renderer)
	{
		std::cout << "Renderer created!" << std::endl;
	}
	else 
	{
		std::cout << "Renderer creation failed." << std::endl;
		delete window;
		return -1;
	}

	TextureManager::LoadAllTextures();

	ui = new UI(window->GetTileRes());
	if (ui->Init() != 0)
	{
		std::cout << "UI creation failed. \n";
		delete window;
		delete ui;
		return -1;
	}


	GameObjectManager::SetTileSize(tileRes);

	map = new Map(tileRes);

	map->Innit(); // doesnt make sense

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
							generateMaze();
						break;
						case EVENT_LOAD:
							inMenu = false;
							isPlaying = true;
							currentLvl = map->LoadMapNumber();
							if (currentLvl > MAPS || currentLvl < 1) // could be integrated into load function
							{
								std::cout << "LOADING SAVE FAILED! \n";
								currentLvl = 1;
							}
							std::cout << "Current Level: " << currentLvl << "\n";
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
		
		player = GameObjectManager::CreateGameObject(GameObjectManager::player, tileRes * PLAYER_SPAWN_X, tileRes * PLAYER_SPAWN_Y); //only need pointer to call SetVelX/Y at this time
		map->LoadMap(currentLvl);
		gameUpdates = new std::thread(&Game::UpdateThread, this); // pointer to non-static member function (Game:: necessary), pointer to object (this)
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
			GameObjectManager::RenderAllGameObjects();
			ui->SetHP(player->GetHP());
			ui->RenderGameMenu();
			SDL_RenderPresent(Game::renderer);
			//------------------------------------------------------------------------------
			if (GameObjectManager::AreAllItemsPickedUp())
			{
				if (currentLvl < 10) 
				{
					PauseUpdate(); // only returns if paused (no join, theread is waiting, it didnt quit)
					GameObjectManager::DestroyAllExceptPlayer();
					player->Reset();
					++currentLvl;
					map->LoadMap(currentLvl);
					std::cout << "Current Level: " << currentLvl << "\n";
					ResumeUpdate();
				}
				else if (GameObjectManager::AreJosephAndYusriDead())
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
				GameObjectManager::DestroyAllExceptPlayer();
				player->Reset();
				map->LoadMap(currentLvl);
				std::cout << "Current Level: " << currentLvl << "\n";
				ResumeUpdate();
			}
			//------------------------------------------------------------------------------
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
		}
		delete gameUpdates;
		GameObjectManager::DestroyAllGameObjects();
		
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
			GameObjectManager::UpdateAllGameObjects();
			//------------------------------------------------------------------------------
			frameTime = SDL_GetTicks() - frameStart;
			if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
		}
		
	}
}

void Game::HandleKeyEvents(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym) {
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
		case SDLK_y:
			player->Shoot();
			break;
		case SDLK_x:
			player->Hit();
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event->key.keysym.sym) {
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
	default:
		break;
	}
}