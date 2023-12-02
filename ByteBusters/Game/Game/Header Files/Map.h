#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include "GameObjectManager.h"
#include "Defines.h"
#include <mutex>
#include "TextureManager.h"




class Map { 

public:

	static std::shared_ptr<Map> GetInstance(const int tileSize);
	Map(Map& other) = delete;
	void operator=(const Map&) = delete;

	~Map();

	void Clean();
	//takes in the level number (what file to load)
	void SaveMapNumber(int mapNum);
	int LoadMapNumber();
	int LoadMap(int lvl); //!< Bet�ltj�k az adott p�ly�t 	
	void SpawnGameObjects(int lvl);
	void DrawMap(); //!< Az adott p�lya h�tter�nek a kirajzol�sa

private:

	Map(int tS); //!<  L�trehoz egy p�ld�nyt az oszt�lyb�l, amely a megadott cella m�retet fogja haszn�lni
	static std::shared_ptr<Map> instance_;
	static std::mutex mutex_;


	std::string pathToFields;
	std::string pathToTextures;

	SDL_Rect* destRectDraw;

	SDL_Texture* path;

	int tileSize; //!< Cella m�rete		
	int map[ROWS][COLS]; //! < Itt t�roljuk el az adott p�ly�t	

	struct levelData {
		GameObjectManager::WallTypes wallType = GameObjectManager::concrete02;
		SDL_Texture* path = TextureManager::dirt;
		int ape = 0;
		int deer = 0;
		int homeless = 0;
		int joseph = 0;
		int rat = 0;
		int soldier = 0;
		int yusri = 0;
	};

	levelData lvlData[MAPS];

};