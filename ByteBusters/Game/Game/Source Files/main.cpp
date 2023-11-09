#pragma once
#include "Defines.h"

#include "SDL.h"
#include "Game.h"
#include <iostream>
#include <thread>
#include <forward_list>

#include <vector>

#include <chrono>

#include "generateMaze.h"

#include "GameObjectManager.h"

Game* game = nullptr;

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

	//THE GREAT GARBAGE DUMP
	{
	


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



	/*
	std::forward_list<int> intList;

	intList.push_front(1);
	intList.push_front(2);
	intList.push_front(3);
	for (int i : intList) {
		std::cout << i << std::endl;
	}
	std::cout << "----------" << std::endl;

	zaza(intList);



	for (int i : intList) {
		std::cout << i << std::endl;
	}
	std::cout << "----------" << std::endl;

	return 0;*/

	}

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

	std::cout << _CrtDumpMemoryLeaks();

	return 0;
}