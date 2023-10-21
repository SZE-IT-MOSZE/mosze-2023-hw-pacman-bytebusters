#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <set>

class Map {

public:

	Map(int size, int res);
	~Map();

	void LoadMap(int lvl);	//takes in the level number (whyat file to load)

	void DrawMap();
	static std::set<SDL_Rect*> mapWalls;
	std::set<SDL_Rect*> GetWalls() { return mapWalls; };

private:

	std::string pathToFields;
	std::string pathToTextures;

	SDL_Rect* srcRect;
	SDL_Rect* destRectDraw;
	std::set<SDL_Rect*> mapPaths;
	

	SDL_Texture* path;
	SDL_Texture* wall;

	SDL_Texture* concrete01;
	SDL_Texture* concrete02;
	SDL_Texture* dirt;
	SDL_Texture* jungle;
	SDL_Texture* lava;
	SDL_Texture* water;
	SDL_Texture* err_;
	

	int tileSize;		// rectanqular !! target rersolution of one tile on the screen
	int tileResolution;	// rectanqular !! texture size in pixels
	int mapRows = 15;		// map has this much tiles in a row
	int mapCols = 20;		// map has this much tiles in a column ATTENTION !!! Hardcoded  values ! 
	int map[15][20] = {};	//init all to 0 

};