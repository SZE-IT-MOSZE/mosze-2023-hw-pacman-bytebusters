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
	int LoadMap(int lvl); //!< Betöltjük az adott pályát 	
	void SpawnGameObjects(int lvl);
	void DrawMap(); //!< Az adott pálya hátterének a kirajzolása

private:

	Map(int tS); //!<  Létrehoz egy példányt az osztályból, amely a megadott cella méretet fogja használni
	static std::shared_ptr<Map> instance_;
	static std::mutex mutex_;


	std::string pathToFields;
	std::string pathToTextures;

	SDL_Rect* destRectDraw;

	SDL_Texture* path;

	int tileSize; //!< Cella mérete		
	int map[ROWS][COLS]; //! < Itt tároljuk el az adott pályát	

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