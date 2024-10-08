#pragma once
#include "Map.h"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

std::weak_ptr<Map> Map::instance_;
std::mutex Map::mutex_;

std::shared_ptr<Map> Map::GetInstance(const int tileSize) {
	std::lock_guard<std::mutex> lock(mutex_);
	std::shared_ptr<Map> sharedInstance;
	if (!(sharedInstance = instance_.lock())) {
		sharedInstance = std::shared_ptr<Map>(new Map(tileSize));
		instance_ = sharedInstance;
	}
	return sharedInstance;
}

Map::Map(const int tR)
{
	tileRes = tR;

	gom = GameObjectManager::GetInstance(tR);

	path = TextureManager::err_;

	pathToFields = "Fields";

	std::filesystem::create_directory(pathToFields); // if Fields does not exist create it. No need to check if it exists, nothing will happen then

	destRectDraw.w = destRectDraw.h = tileRes;
	destRectDraw.x = destRectDraw.y = 0;

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
	lvlData[0].ape = 1;
	lvlData[0].deer = 1;
	lvlData[0].homeless = 1;
	lvlData[0].joseph = 1;
	lvlData[0].rat = 1;
	lvlData[0].soldier = 1;
	lvlData[0].yusri = 1;

	lvlData[9].soldier = 1;
	lvlData[9].yusri = 1;
	lvlData[9].joseph = 1;
#endif // DEBUGLEVEL

}

int Map::LoadMapNumber() {
	//error is < 0;
	std::ifstream ReadSave(pathToFields + "\\" + "save.txt"); // open the level file
	
	if (!ReadSave)
	{
		std::cout << "Error reading file: save.txt\n";
		ReadSave.close();
		return -1;
	}
	std::string mapNumStr = "";
	if (std::getline(ReadSave, mapNumStr))
	{
		int mapNum;
		try {
			mapNum = std::stoi(mapNumStr);
		}
		catch (std::invalid_argument& /*e*/) {
			// if no conversion could be performed
			std::cout << "invalid_argument in save.txt\n";
			mapNum = -1;
		}
		catch (std::out_of_range& /*e*/) {
			// if the converted value would fall out of the range
			std::cout << "out_of_range in save.txt\n";
			mapNum = -1;
		}
		catch (...) {
			// everything else
			std::cout << "UNEXPECTED_ERROR in save.txt\n";
			mapNum = -1;
		}
		ReadSave.close();
		return mapNum;
	}
	ReadSave.close();
	return -1;

}

void Map::SaveMapNumber(int mapNum) {
	// not creating save.txt
	std::ofstream WriteFile(pathToFields + "\\" + "save.txt");

	if (!WriteFile) {
		std::cout << "ERROR WRITING TO FILE save.txt \n";
		WriteFile.close();
		return;
	}
	WriteFile << std::to_string(mapNum);
	WriteFile.close();
}

int Map::LoadMap(int l) { // could be separated into 2 individual functions

	int lvl = l;

	path = lvlData[lvl - 1].path;

	std::ifstream ReadLevel(pathToFields + "\\" + std::to_string(lvl) + ".txt"); // open the level file

	if (!ReadLevel)
	{
		std::cout << "ERROR READING FILE: " << std::to_string(lvl) + ".txt\n";

		ReadLevel.close();
		return -1;
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
			std::cout << "WRONG FORMAT: " << std::to_string(lvl) + ".txt\n";
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
			std::cout << "invalid_argument in: Row: " << rowCnt << " Col: " << colCnt << "\n";
			map[rowCnt][colCnt] = -1;
		}
		catch (std::out_of_range& /*e*/) {
			// if the converted value would fall out of the range
			std::cout << "out_of_range in: Row: " << rowCnt << " Col: " << colCnt << "\n";
			map[rowCnt][colCnt] = -1;
		}
		catch (...) {
			// everything else
			std::cout << "unexpected_error in: Row: " << rowCnt << " Col: " << colCnt << "\n";
			map[rowCnt][colCnt] = -1;
		}

		colCnt++;
		totalCnt++;
		
	}

	if (totalCnt < totalTiles)
	{
		std::cout << "Wrong format: " << std::to_string(lvl) + ".txt\n";
	}

	ReadLevel.close();

	SpawnGameObjects(lvl-1);

	return 0;
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
				gom->CreateGameObject(lvlData[lvl].wallType, c * tileRes, r * tileRes);
				break;
			case 2:
				gom->CreateGameObject(GameObjectManager::item, c * tileRes, r * tileRes);
				break;
			default:
				break;
			}

		}
	}

	//spawn enemies
	for (int i = 0; i < lvlData[lvl].ape; i++)
	{
		gom->CreateGameObject(GameObjectManager::ape, ENEMY_SPAWN_X * tileRes, ENEMY_SPAWN_Y * tileRes);
	}
	for (int i = 0; i < lvlData[lvl].deer; i++)
	{
		gom->CreateGameObject(GameObjectManager::deer, ENEMY_SPAWN_X * tileRes, ENEMY_SPAWN_Y * tileRes);
	}
	for (int i = 0; i < lvlData[lvl].homeless; i++)
	{
		gom->CreateGameObject(GameObjectManager::homeless, ENEMY_SPAWN_X * tileRes, ENEMY_SPAWN_Y * tileRes);
	}
	for (int i = 0; i < lvlData[lvl].joseph; i++)
	{
		gom->CreateGameObject(GameObjectManager::joseph, ENEMY_SPAWN_X * tileRes, ENEMY_SPAWN_Y * tileRes);
	}
	for (int i = 0; i < lvlData[lvl].rat; i++)
	{
		gom->CreateGameObject(GameObjectManager::rat, ENEMY_SPAWN_X * tileRes, ENEMY_SPAWN_Y * tileRes);
	}
	for (int i = 0; i < lvlData[lvl].soldier; i++)
	{
		gom->CreateGameObject(GameObjectManager::soldier, ENEMY_SPAWN_X * tileRes, ENEMY_SPAWN_Y * tileRes);
	}
	for (int i = 0; i < lvlData[lvl].yusri; i++)
	{
		gom->CreateGameObject(GameObjectManager::yusri, ENEMY_SPAWN_X * tileRes, ENEMY_SPAWN_Y * tileRes);
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
				destRectDraw.x = c * tileRes;
				destRectDraw.y = r * tileRes;
				TextureManager::Draw(path, NULL, &destRectDraw);
				break;
			default:
				break;
			}

		}
	}
}