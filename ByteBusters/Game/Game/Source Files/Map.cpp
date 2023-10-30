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


	GameObjectManager::TileTypes wallType;
	switch (lvl)	// technically i didnt do anything wrong
	{				// this is NOT a programming war crime
	case 1: // deep jungle
		path = TextureManager::jungle;
		wallType = GameObjectManager::concrete02;
		break;
	case 2: // jungle riverside
		path = TextureManager::jungle;
		wallType = GameObjectManager::water;
		break;
	case 3: // lavafields
		path = TextureManager::concrete01;
		wallType = GameObjectManager::lava;
		break;
	case 4: // wild monke area hmmm
		//majom lol
	case 5: // rocky shores
		path = TextureManager::concrete01;
		wallType = GameObjectManager::water;
		break;
	case 6: // desert oasis
		path = TextureManager::dirt; // we no have sand
		wallType = GameObjectManager::water;
		break;
	case 7: // dusty desert
		path = TextureManager::dirt; // we no have sand
		wallType = GameObjectManager::concrete02;
		break;
	case 8: // rocky hillside
		path = TextureManager::concrete01;
		wallType = GameObjectManager::concrete02;
		break;
	case 9: // around the lab
		path = TextureManager::jungle;
		wallType = GameObjectManager::concrete02;
		break;
	case 10: // in the lab
		path = TextureManager::concrete01;
		wallType = GameObjectManager::concrete02;
		break;
	default:
		break;
	}


	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLS; c++)
		{
			switch (map[r][c])
			{
			case 1:
				GameObjectManager::CreateGameObject(wallType, c * tileSize, r * tileSize);
				break;
			case 2:
				GameObjectManager::CreateGameObject(GameObjectManager::item, c * tileSize, r * tileSize);
				break;
			default:
				break;
			}

		}
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