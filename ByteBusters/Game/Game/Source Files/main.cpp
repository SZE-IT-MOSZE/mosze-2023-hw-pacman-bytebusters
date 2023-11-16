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
	
	Game* game = new Game();

	if (game->Init(window->GetWindow(), window->GetTileRes()))
	{
		delete game;
		delete window;
		return -1;
	}

	srand(time(NULL)); // only intitialize srand once

	generateMaze();

	game->Start();

	game->Clean();

	delete game;

	delete window;

	


	

	std::cout << _CrtDumpMemoryLeaks();

	return 0;
}

