#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>

#define ROWS 15
#define COLS 20

class Map {

public:

	Map(int size);
	~Map();

	void LoadMap(int lvl);	//takes in the level number (what file to load)

	void DrawMap();

private:

	std::string pathToFields;
	std::string pathToTextures;

	SDL_Rect* destRectDraw;

	SDL_Texture* path;
	SDL_Texture* wall;

	int tileSize;		// rectanqular !! target rersolution of one tile on the screen
	//int mapRows = 15;		// map has this much tiles in a row
	//int mapCols = 20;		// map has this much tiles in a column ATTENTION !!! Hardcoded  values ! 
	int map[ROWS][COLS] = {};	//init all to 0 

};