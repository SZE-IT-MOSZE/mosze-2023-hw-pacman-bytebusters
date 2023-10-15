#include "Map.h"
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <string>

Map::Map(int size, int res) {

	tileResolution = res;	//may not need to keep this in the future
	tileSize = size;		//may not need to keep this in the future

	pathToFields = "Fields/";

	concrete01	= TextureManager::LoadTexture("Assets/concrete01.png");
	concrete02	= TextureManager::LoadTexture("Assets/concrete02.png");
	dirt		= TextureManager::LoadTexture("Assets/dirt.png");
	jungle		= TextureManager::LoadTexture("Assets/jungle.png");
	lava		= TextureManager::LoadTexture("Assets/lava.png");
	water		= TextureManager::LoadTexture("Assets/water.png");
	err_		= TextureManager::LoadTexture("Assets/err_.png");

	src.w = src.h = tileResolution;
	src.x = src.y = 0;
	dest.w = dest.h = tileSize;
	dest.x = dest.y = 0;
	
	LoadMap(17); // loadmap wont stay here i guess
}

void Map::LoadMap(int lvl) {

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
	int totalTiles = mapRows * mapCols; // 300

	while (std::getline(ReadLevel, cell, ' '))	//read the data into the map array, SHOULD BE FAILSAFE
	{
		if (totalCnt == totalTiles)
		{
			std::cout << "WRONG FORMAT: " << std::to_string(lvl) + ".txt" << std::endl;
			break; //loop quits if the file is too long
		}
		if (colCnt == mapCols)
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

	switch (lvl)	// technically i didnt do anything wrong
	{				// this is NOT a programming war crime
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		path = dirt;
		wall = concrete02;
		break;
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		path = jungle;
		wall = water;
		break;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		path = concrete01;
		wall = water;
		break;
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
		path = concrete02;
		wall = lava;
		break;
	default:
		break;
	}
	//std::cout << mapCols << std::endl;
	//std::cout << mapRows << std::endl;

}

void Map::DrawMap() {
	for (int r = 0; r < mapRows; r++)
	{
		for (int c = 0; c < mapCols; c++)
		{

			dest.x = c * tileSize;
			dest.y = r * tileSize;
			
			switch (map[r][c])
			{
			case 0:
				TextureManager::Draw(path, src, dest);
				break;
			case 1:
				TextureManager::Draw(wall, src, dest);
				break;
			default:
				TextureManager::Draw(err_, src, dest);
				break;
			}

		}
	}
}