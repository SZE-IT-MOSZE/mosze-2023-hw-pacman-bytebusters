#pragma once
#include "Defines.h"

#include "Map.h"
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <string>

std::string Map::pathToFields;
std::string Map::pathToTextures;

SDL_Rect* Map::destRectDraw;

SDL_Texture* Map::path;

int Map::tileSize;
int Map::map[ROWS][COLS] = {};

int Map::lvl;

struct levelData {
	GameObjectManager::WallTypes wallType = GameObjectManager::concrete02;
	SDL_Texture* path = TextureManager::dirt;
	int ape = 0;
	int deer = 0;
	int homeless = 0;
	int joseph = 0;
	int rat = 0;
	int soldier = 0;
	int yusri = 0;
};

levelData lvlData[MAPS]; //index level.txt from 1, index lvlData from 0. it's a bit weird i admit.

void DefineLevelData() {
	///////////// DEEP JUNGLE /////////////
	lvlData[0].wallType = GameObjectManager::concrete02;
	lvlData[0].path = TextureManager::jungle;
	lvlData[0].rat = 10;
	///////////// JUNGLE RIVERSIDE /////////////
	lvlData[1].wallType = GameObjectManager::water;
	lvlData[1].path = TextureManager::jungle;
	lvlData[1].deer = 10;
	///////////// LAVAFIELDS /////////////
	lvlData[2].wallType = GameObjectManager::water;
	lvlData[2].path = TextureManager::jungle;
	lvlData[2].rat = 10;
	///////////// WILD MONKEY AREA /////////////
	lvlData[3].wallType = GameObjectManager::concrete02;
	lvlData[3].path = TextureManager::dirt;
	lvlData[3].ape = 10;
	///////////// ROCKY SHORES /////////////
	lvlData[4].wallType = GameObjectManager::water;
	lvlData[4].path = TextureManager::concrete01;
	lvlData[4].homeless = 10;
	///////////// DESERT OASIS /////////////
	lvlData[5].wallType = GameObjectManager::water;
	lvlData[5].path = TextureManager::dirt;
	lvlData[5].ape = 3;
	lvlData[5].deer = 3;
	lvlData[5].rat = 3;
	///////////// DUSTY DESERT /////////////
	lvlData[6].wallType = GameObjectManager::concrete02;
	lvlData[6].path = TextureManager::dirt;
	lvlData[6].ape = 5;
	lvlData[6].deer = 5;
	///////////// ROCKY HILLSIDE /////////////
	lvlData[7].wallType = GameObjectManager::concrete02;
	lvlData[7].path = TextureManager::concrete01;
	lvlData[7].homeless = 10;
	///////////// AROUND THE LAB /////////////
	lvlData[8].wallType = GameObjectManager::concrete02;
	lvlData[8].path = TextureManager::jungle;
	lvlData[8].soldier = 10;
	///////////// IN THE LAB /////////////
	lvlData[9].wallType = GameObjectManager::concrete02;
	lvlData[9].path = TextureManager::concrete01;
	lvlData[9].soldier = 10;
	lvlData[9].yusri = 1;
	lvlData[9].joseph = 1;

#ifdef DEBUGLEVEL
	lvlData[0].rat = 1;

	lvlData[0].soldier = 1;
#endif // DEBUGLEVEL

	
}

void Map::Innit(int size) {

	tileSize = size;		//may not need to keep this in the future

	pathToFields = "Fields\\";

	destRectDraw = new SDL_Rect;
	
	destRectDraw->w = destRectDraw->h = tileSize;
	destRectDraw->x = destRectDraw->y = 0;

	DefineLevelData();

}

void Map::Clean() {
	delete destRectDraw;
}

void Map::LoadMap(int l) { // could be separated into 2 individual functions

	lvl = l;

	path = lvlData[lvl-1].path;

	std::ifstream ReadLevel(pathToFields + std::to_string(lvl) + ".txt"); // open the level file

	if (!ReadLevel)
	{
		std::cout << "ERROR READING FILE: " << std::to_string(lvl) + ".txt" << std::endl; 
		return;
	}

	std::string cell = "";
	int rowCnt = 0;
	int colCnt = 0;
	int totalCnt = 0;
	int totalTiles = ROWS * COLS; // 300

	while (std::getline(ReadLevel, cell, ' '))	//read the data into the map array, SHOULD BE FAILSAFE
	{
		if (totalCnt == totalTiles)
		{
			std::cout << "WRONG FORMAT: " << std::to_string(lvl) + ".txt" << std::endl;
			break; //loop quits if the file is too long
		}
		if (colCnt == COLS)
		{
			colCnt = 0;
			rowCnt++;
		}

		try {
			map[rowCnt][colCnt] = std::stoi(cell);
		}
		catch (std::invalid_argument& /*e*/) {
			// if no conversion could be performed
			std::cout << "invalid_argument in: Row: " << rowCnt << " Col: " << colCnt<< std::endl;
			map[rowCnt][colCnt] = -1;
		}
		catch (std::out_of_range& /*e*/) {
			// if the converted value would fall out of the range
			std::cout << "out_of_range in: Row: " << rowCnt << " Col: " << colCnt << std::endl;
			map[rowCnt][colCnt] = -1;
		}
		catch (...) {
			// everything else
			std::cout << "UNEXPECTED_ERROR in: Row: " << rowCnt << " Col: " << colCnt << std::endl;
			map[rowCnt][colCnt] = -1;
		}

		colCnt++;
		totalCnt++;
		
	}

	if (totalCnt < totalTiles)
	{
		std::cout << "WRONG FORMAT: " << std::to_string(lvl) + ".txt" << std::endl;
	}

	ReadLevel.close();

	SpawnGameObjects(lvl-1);
}

void Map::SpawnGameObjects(int lvl) {
	//spawn the walls and items
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			switch (map[r][c])
			{
			case 1:
				GameObjectManager::CreateGameObject(lvlData[lvl].wallType, c * tileSize, r * tileSize);
				break;
			case 2:
				GameObjectManager::CreateGameObject(GameObjectManager::item, c * tileSize, r * tileSize);
				break;
			default:
				break;
			}

		}
	}

	//spawn enemies
	for (size_t i = 0; i < lvlData[lvl].ape; i++)
	{
		GameObjectManager::CreateGameObject(GameObjectManager::ape, tileSize, tileSize);
	}
	for (size_t i = 0; i < lvlData[lvl].deer; i++)
	{
		GameObjectManager::CreateGameObject(GameObjectManager::deer, tileSize, tileSize);
	}
	for (size_t i = 0; i < lvlData[lvl].homeless; i++)
	{
		GameObjectManager::CreateGameObject(GameObjectManager::homeless, tileSize, tileSize);
	}
	for (size_t i = 0; i < lvlData[lvl].joseph; i++)
	{
		GameObjectManager::CreateGameObject(GameObjectManager::joseph, tileSize, tileSize);
	}
	for (size_t i = 0; i < lvlData[lvl].rat; i++)
	{
		GameObjectManager::CreateGameObject(GameObjectManager::rat, tileSize, tileSize);
	}
	for (size_t i = 0; i < lvlData[lvl].soldier; i++)
	{
		GameObjectManager::CreateGameObject(GameObjectManager::soldier, tileSize, tileSize);
	}
	for (size_t i = 0; i < lvlData[lvl].yusri; i++)
	{
		GameObjectManager::CreateGameObject(GameObjectManager::yusri, tileSize, tileSize);
	}
}

void Map::DrawMap() {
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			switch (map[r][c])
			{
			case 0: // path
			case 2: // item
				destRectDraw->x = c * tileSize;
				destRectDraw->y = r * tileSize;
				TextureManager::Draw(path, NULL, destRectDraw);
				break;
			default:
				break;
			}

		}
	}
}
