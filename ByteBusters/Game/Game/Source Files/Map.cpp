#include "Map.h"
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <string>

#define MAPS 10

struct levelData {
	GameObjectManager::TileTypes wallType = GameObjectManager::concrete02;
	SDL_Texture* path = TextureManager::dirt;
	int ape = 0;
	int deer = 0;
	int guard = 0;
	int homeless = 0;
	int joseph = 0;
	int rat = 0;
	int soldier = 0;
	int yusri = 0;
};

levelData lvlData[MAPS]; 

void DefineLevelData() {
	///////////// DEEP JUNGLE /////////////
	lvlData[1].wallType = GameObjectManager::concrete02;
	lvlData[1].path = TextureManager::jungle;
	lvlData[1].rat = 10;
	///////////// JUNGLE RIVERSIDE /////////////
	lvlData[2].wallType = GameObjectManager::water;
	lvlData[2].path = TextureManager::jungle;
	lvlData[2].deer = 10;
	///////////// LAVAFIELDS /////////////
	lvlData[3].wallType = GameObjectManager::water;
	lvlData[3].path = TextureManager::jungle;
	lvlData[3].rat = 10;
	///////////// WILD MONKEY AREA /////////////
	lvlData[4].wallType = GameObjectManager::concrete02;
	lvlData[4].path = TextureManager::dirt;
	lvlData[4].ape = 10;
	///////////// ROCKY SHORES /////////////
	lvlData[5].wallType = GameObjectManager::water;
	lvlData[5].path = TextureManager::concrete01;
	lvlData[5].homeless = 10;
	///////////// DESERT OASIS /////////////
	lvlData[6].wallType = GameObjectManager::water;
	lvlData[6].path = TextureManager::dirt;
	lvlData[6].ape = 3;
	lvlData[6].deer = 3;
	lvlData[6].rat = 3;
	///////////// DUSTY DESERT /////////////
	lvlData[7].wallType = GameObjectManager::concrete02;
	lvlData[7].path = TextureManager::dirt;
	lvlData[7].ape = 5;
	lvlData[7].deer = 5;
	///////////// ROCKY HILLSIDE /////////////
	lvlData[8].wallType = GameObjectManager::concrete02;
	lvlData[8].path = TextureManager::concrete01;
	lvlData[8].homeless = 10;
	///////////// AROUND THE LAB /////////////
	lvlData[9].wallType = GameObjectManager::concrete02;
	lvlData[9].path = TextureManager::jungle;
	lvlData[9].soldier = 10;
	///////////// IN THE LAB /////////////
	lvlData[10].wallType = GameObjectManager::concrete02;
	lvlData[10].path = TextureManager::concrete01;
	lvlData[10].guard = 10;
	lvlData[10].yusri = 1;
	lvlData[10].joseph = 1;
	
}

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


	GameObjectManager::TileTypes wallType = GameObjectManager::concrete02;
	GameObjectManager::EnemyTypes enemyType = GameObjectManager::ape;

	//create function that spawns gameobjects instead of this switch and the for cycle under it.

	switch (lvl)
	{
	case 1: // deep jungle
		path = TextureManager::jungle;
		wallType = GameObjectManager::concrete02;
		enemyType = GameObjectManager::rat;
		break;
	case 2: // jungle riverside
		path = TextureManager::jungle;
		wallType = GameObjectManager::water;
		enemyType = GameObjectManager::deer;
		break;
	case 3: // lavafields
		path = TextureManager::concrete01;
		wallType = GameObjectManager::lava;
		enemyType = GameObjectManager::rat;
		break;
	case 4: // wild monke area
		path = TextureManager::dirt;
		wallType = GameObjectManager::concrete02;
		enemyType = GameObjectManager::ape;
		break;
	case 5: // rocky shores
		path = TextureManager::concrete01;
		wallType = GameObjectManager::water;
		enemyType = GameObjectManager::homeless;
		break;
	case 6: // desert oasis
		path = TextureManager::dirt; // we no have sand
		wallType = GameObjectManager::water;
		enemyType = GameObjectManager::rat; //RANDOM MUTANTS
		break;
	case 7: // dusty desert
		path = TextureManager::dirt; // we no have sand
		wallType = GameObjectManager::concrete02;
		enemyType = GameObjectManager::rat; //MUTANT APE AND DEER
		break;
	case 8: // rocky hillside
		path = TextureManager::concrete01;
		wallType = GameObjectManager::concrete02;
		enemyType = GameObjectManager::homeless;
		break;
	case 9: // around the lab
		path = TextureManager::jungle;
		wallType = GameObjectManager::concrete02;
		enemyType = GameObjectManager::soldier;
		break;
	case 10: // in the lab
		path = TextureManager::concrete01;
		wallType = GameObjectManager::concrete02;
		enemyType = GameObjectManager::guard; // + yusri + doktor
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

	for (size_t i = 1; i < 7; i++)
	{
		GameObjectManager::CreateGameObject(enemyType, tileSize * 2 * i, tileSize);
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
				destRectDraw->x = c * tileSize;
				destRectDraw->y = r * tileSize;
				TextureManager::Draw(TextureManager::err_, NULL, destRectDraw);
				break;
			}

		}
	}
}