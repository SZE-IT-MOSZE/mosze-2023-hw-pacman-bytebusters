#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "GameObjectManager.h"
#include "Defines.h"




class Map { 

public:

	Map(int size); //!<  Létrehoz egy példányt az osztályból, amely a megadott cella méretet fogja használni
	~Map();

	void Innit(); 
	void Clean();
	//takes in the level number (what file to load)
	int LoadMap(int lvl); //!< Betöltjük az adott pályát 	
	void SpawnGameObjects(int lvl);
	void DrawMap(); //!< Az adott pálya hátterének a kirajzolása
	//static void ReloadMap();

private:

	std::string pathToFields;
	std::string pathToTextures;

	SDL_Rect* destRectDraw;

	SDL_Texture* path;

	int tileSize; //!< Cella mérete		
	int map[ROWS][COLS]; //! < Itt tároljuk el az adott pályát	

	int lvl;

};