#pragma once
#include "Defines.h"

#include "SDL.h"
#include "Game.h"
#include "Window.h"
#include "Button.h"
#include <thread>
#include <forward_list>

#include <vector>

#include <chrono>

#include "generateMaze.h"

#include "GameObjectManager.h"

#include "UI.h"




#include <iostream>


//THE SMALLER GARBAGE DUMP ABOVE THE GREAT GARBAGE DUMP

//
//void zaza(std::forward_list<int>& l) {
//	std::forward_list<int>& funcList = l;
//
//	l.push_front(5);
//	l.push_front(6);
//	funcList.push_front(11);
//	funcList.push_front(12);
//
//	for (int i : l) {
//		std::cout << i << std::endl;
//	}
//	std::cout << "----------" << std::endl;
//
//	for (int i : funcList) {
//		std::cout << i << std::endl;
//	}
//	std::cout << "----------" << std::endl;
//
//}


int main(int argc, char* argv[]) {

	//{215} i know what this means and i dont like it

	//THE GREAT GARBAGE DUMP
	{

		//int* zaza = new int[5];

		//for (int i = 0; i < 5; i++)
		//{
		//	zaza[i] = i;
		//}

		//for (int i = 0; i < 5; i++)
		//{
		//	std::cout << zaza[i] << std::endl;
		//}

		//delete[] zaza;
		//zaza = new int[5]; // so this is a memory leak without the above line. good to know.

		//for (int i = 0; i < 5; i++)
		//{
		//	zaza[i] = i*2;
		//}

		//for (int i = 0; i < 5; i++)
		//{
		//	std::cout << zaza[i] << std::endl;
		//}

		//delete[] zaza;

		//std::cout << _CrtDumpMemoryLeaks();

		//return 0;

		//std::cout << time(NULL) << std::endl;

		//std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(
		//	std::chrono::system_clock::now().time_since_epoch()
		//);
		//std::cout << ms << std::endl;

		//uint64_t t = duration_cast<std::chrono::milliseconds>(
		//	std::chrono::system_clock::now().time_since_epoch()
		//).count();
		//std::cout << "t: " << t << std::endl;

		//SDL_Delay(1000);
		//ms = duration_cast<std::chrono::milliseconds>(
		//	std::chrono::system_clock::now().time_since_epoch()
		//);
		//std::cout << ms << std::endl;
		//std::cout << time(NULL) << std::endl;


		//return 123;

		//std::forward_list<int> zaza;
		//zaza.push_front(900);
		//zaza.push_front(800);
		//zaza.push_front(700);
		//zaza.push_front(600);
		//zaza.push_front(500);

		//int size = distance(zaza.begin(), zaza.end());

		//auto it = zaza.begin();

		//for (int i =0; i < distance(zaza.begin(), zaza.end()); i++)
		//{
		//	if (*it == 700) {
		//		//std::cout << "SIZE: " << zaza.size() << std::endl;
		//		i--;
		//		std::cout << "POP(cat)" << std::endl;

		//		zaza.remove(i);

		//		//std::cout << "SIZE: " << zaza.size() << std::endl;

		//	}
		//	std::advance(it, i);
		//	std::cout << "asd " << *it << std::endl;

		//}



		
		//std::forward_list<int> intList;
		//
		//intList.push_front(1);
		//intList.push_front(2);
		//intList.push_front(3);
		//for (int i : intList) {
		//	std::cout << i << std::endl;
		//}
		//std::cout << "----------" << std::endl;
		//
		//zaza(intList);
		//
		//
		//
		//for (int i : intList) {
		//	std::cout << i << std::endl;
		//}
		//std::cout << "----------" << std::endl;
		//
		//return 0;

	}

	Window* window = new Window();
	
	if (window->Init("DEER - MURDER - HORROR - BLOOD - GORE(The Game)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false) != 0)
	{
		delete window;
		return -1;
	}

	UI* ui = new UI(window, window->GetTileRes());

	Game* game = new Game();

	if (game->Init(window->GetWindow(), window->GetTileRes()))
	{
		delete game;
		delete window;
		return -1;
	}

	ui->Init(); // only create buttons after game has created its renderer, otherwise renderer creation will fail

	Map* map = new Map(window->GetTileRes());

	map->Innit();

	srand((unsigned int)time(NULL)); // only intitialize srand once

	bool isRunning = true;	// the application is running
	bool isPlaying = false; // the game is being played
	bool inMenu = true;		// the user is in the main menu

	SDL_Event event;

	constexpr int FPS = _FPS;
	constexpr int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	int currentLvl = 0;

	std::thread* gameUpdates;

	Uint32 UI_EVENT = ui->Get_UI_EVENT();

	while (isRunning)
	{
		

		while(inMenu) {

			frameStart = SDL_GetTicks();
			//------------------------------------------------------------------------------
			while (SDL_PollEvent(&event))
			{

				switch (event.type)
				{
				case SDL_QUIT:
					inMenu = false;
					isRunning = false;
					break;
				default:
					break;
				} 

				if (event.type == UI_EVENT)
				{
					switch (event.user.code)
					{
					case EVENT_START:
						std::cout << "START GAME\n";
						isPlaying = true;
						inMenu = false;

						game->Start();
						generateMaze(); // keep fields folder intact in case of save load
						break;
					case EVENT_LOAD:
						std::cout << "LOAD GAME\n";
						break;
					default:
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

		if (isPlaying)
		{
			

			//maybe gameupdates should be in game
			//buttons call game load or game start/newgame?
			game->StartUpdate(); // not the best name, it just sets the variable that lets it run when update is created
			gameUpdates = new std::thread(&Game::UpdateThread, game); // pointer to non-static member function (Game:: necessary), pointer to object (game)

			while(isPlaying) {
				frameStart = SDL_GetTicks();
				//------------------------------------------------------------------------------
				while (SDL_PollEvent(&event))
				{
					
					if (event.type == UI_EVENT)
					{
						switch (event.user.code)
						{
						case EVENT_SAVE:
							std::cout << "SAVE GAME\n";
							isPlaying = false;
							inMenu = true;
							game->StopUpdate();
							gameUpdates->join();
							break;
						case EVENT_MENU:
							std::cout << "TO MENU\n";
							isPlaying = false;
							inMenu = true;
							game->StopUpdate();
							gameUpdates->join();
							break;
						default:
							break;
						}
					}
					if (event.type == SDL_QUIT)
					{
						isPlaying = false;
						isRunning = false;
						game->StopUpdate();
						gameUpdates->join();
						break;
					}
					game->HandleEvents(&event);
					ui->HandleGameMenuEvents(&event);
				}
				//------------------------------------------------------------------------------
				SDL_RenderClear(Game::renderer);

				//std::cout << "RENDER main \n";

				map->DrawMap();
				game->Render();
				ui->RenderGameMenu();

				SDL_RenderPresent(Game::renderer);
				//------------------------------------------------------------------------------
				if (GameObjectManager::AreAllItemsPickedUp())
				{
					//SDL_Delay(2000); // some delay between two maps
					++currentLvl;
					if (currentLvl > MAPS) {
						isPlaying = false;
						game->StopUpdate();
						gameUpdates->join();
						currentLvl = 0;
						GameObjectManager::DestroyAllExceptPlayer();
						break;
					}

					GameObjectManager::DestroyAllExceptPlayer();
					GameObjectManager::ResetPlayer();
					map->LoadMap(currentLvl);
				
				}
				//------------------------------------------------------------------------------
				if (game->isPlayerDead())
				{
					//SDL_Delay(2000);
					map->LoadMap(currentLvl);
					GameObjectManager::DestroyAllExceptPlayer();
					GameObjectManager::ResetPlayer();
				}
				//------------------------------------------------------------------------------
				frameTime = SDL_GetTicks() - frameStart;
				if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
			}

			//gameUpdates->join(); // wait for update if it didnt finish already
			delete gameUpdates;
			GameObjectManager::DestroyAllGameObjects();



		}

	}

	game->Clean();

	map->Clean();

	delete game;

	delete window;

	delete ui;

	delete map;


	

	std::cout << _CrtDumpMemoryLeaks();

	return 0;
}

