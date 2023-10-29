#include "Map.h"
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include "GameObjectManager.h"

Map::Map(int size) {

	tileSize = size;		//may not need to keep this in the future

	pathToFields = "Fields\\";

	destRectDraw = new SDL_Rect;
	
	destRectDraw->w = destRectDraw->h = tileSize;
	destRectDraw->x = destRectDraw->y = 0;

}

Map::~Map() {
	delete destRectDraw;
}

void Map::LoadMap(int lvl) { // could be separated into 2 individual functions

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
		catch (std::invalid_argument& e) {
			// if no conversion could be performed
			std::cout << "invalid_argument in: Row: " << rowCnt << " Col: " << colCnt<< std::endl;
			map[rowCnt][colCnt] = -1;
		}
		catch (std::out_of_range& e) {
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

	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			switch (map[r][c])
			{
			case 1:
				GameObjectManager::CreateGameObject(GameObjectManager::lava, c * tileSize, r * tileSize);
				break;
			case 2:
				GameObjectManager::CreateGameObject(GameObjectManager::item, c * tileSize, r * tileSize);
				break;
			default:
				break;
			}

		}
	}

	switch (lvl)	// technically i didnt do anything wrong
	{				// this is NOT a programming war crime
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		path = TextureManager::dirt;
		wall = TextureManager::concrete02;
		break;
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		path = TextureManager::jungle;
		wall = TextureManager::water;
		break;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		path = TextureManager::concrete01;
		wall = TextureManager::water;
		break;
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
		path = TextureManager::concrete02;
		wall = TextureManager::lava;
		break;
	default:
		break;
	}

}

void Map::DrawMap() {
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			switch (map[r][c])
			{
			case 0:
			case 2:
				destRectDraw->x = c * tileSize;
				destRectDraw->y = r * tileSize;
				TextureManager::Draw(path, NULL, destRectDraw);
				break;
			default:
				destRectDraw->x = c * tileSize;
				destRectDraw->y = r * tileSize;
				TextureManager::Draw(TextureManager::err_, NULL, destRectDraw);
				break;
			}

		}
	}
}