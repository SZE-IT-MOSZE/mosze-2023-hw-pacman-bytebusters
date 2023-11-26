#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "GameObjectManager.h"
#include "Defines.h"




class Map { 

public:

	static void Innit(int size); //!< Inicializálja a pályák használatához szükséges adatokat, paraméterben megadott cella méretet fogja használni
	static void Clean();
	//takes in the level number (what file to load)
	static void LoadMap(int lvl); //!< Betöltjük az adott pályát 	
	static void SpawnGameObjects(int lvl);
	static void DrawMap(); //!< Az adott pálya hátterének a kirajzolása
	static int GetTileSize() { return tileSize; };

private:

	static std::string pathToFields;
	static std::string pathToTextures;

	static SDL_Rect* destRectDraw;

	static SDL_Texture* path;

	static int tileSize; //!< Cella mérete		
	static int map[ROWS][COLS]; //! < Itt tároljuk el az adott pályát	
	static int lvl;

};