#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "GameObjectManager.h"
#include "Defines.h"




class Map { 

public:

	Map(int size); //!<  L�trehoz egy p�ld�nyt az oszt�lyb�l, amely a megadott cella m�retet fogja haszn�lni
	~Map();
	//takes in the level number (what file to load)
	void LoadMap(int lvl); //!< Bet�ltj�k az adott p�ly�t 	
	void SpawnGameObjects(int lvl);
	void DrawMap(); //!< Az adott p�lya h�tter�nek a kirajzol�sa

private:

	std::string pathToFields;
	std::string pathToTextures;

	SDL_Rect* destRectDraw;

	SDL_Texture* path;

	int tileSize; //!< Cella m�rete		
	//init all to 0
	int map[ROWS][COLS] = {}; //! < Itt t�roljuk el az adott p�ly�t	

};