#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "GameObjectManager.h"
#include "Defines.h"




class Map { 

public:

	static void Innit(int size); //!< Inicializ�lja a p�ly�k haszn�lat�hoz sz�ks�ges adatokat, param�terben megadott cella m�retet fogja haszn�lni
	static void Clean();
	//takes in the level number (what file to load)
	static void LoadMap(int lvl); //!< Bet�ltj�k az adott p�ly�t 	
	static void SpawnGameObjects(int lvl);
	static void DrawMap(); //!< Az adott p�lya h�tter�nek a kirajzol�sa
	static int GetTileSize() { return tileSize; };

private:

	static std::string pathToFields;
	static std::string pathToTextures;

	static SDL_Rect* destRectDraw;

	static SDL_Texture* path;

	static int tileSize; //!< Cella m�rete		
	static int map[ROWS][COLS]; //! < Itt t�roljuk el az adott p�ly�t	
	static int lvl;

};