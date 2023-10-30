#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>

#define ROWS 15
#define COLS 20

class Map { 

public:

	Map(int size); //!<  Létrehoz egy példányt az osztályból, amely a megadott cella méretet fogja használni
	~Map();
	//takes in the level number (what file to load)
	void LoadMap(int lvl); //!< Betöltjük az adott pályát 	

	void DrawMap(); //!< Az adott pálya hátterének a kirajzolása

private:

	std::string pathToFields;
	std::string pathToTextures;

	SDL_Rect* destRectDraw;

	SDL_Texture* path;
	SDL_Texture* wall;

	int tileSize; //!< Cella mérete		
	//init all to 0
	int map[ROWS][COLS] = {}; //! < Itt tároljuk el az adott pályát	

};