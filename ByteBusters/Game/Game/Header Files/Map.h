#pragma once
#include "SDL.h"
#include "Defines.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include <mutex>
#include <string>

class Map { 

public:

	static std::shared_ptr<Map> GetInstance(const int tileSize); //!< Singleton instance
	Map(Map& other) = delete; //!< Törölt copy konstruktor
	void operator=(const Map&) = delete; //!< Törölt = operátor
	~Map() {}; //!< Destruktor

	void SaveMapNumber(int mapNum); //!< Adott pályaszám mentése file-ba
	int LoadMapNumber(); //!< Mentett pályaszám betöltése file-ból
	int LoadMap(int lvl); //!< Adott pálya betöltése
	void SpawnGameObjects(int lvl); //!< Objektumok létehozása az adott pályához
	void DrawMap(); //!< Az adott pálya hátterének a kirajzolása

private:

	Map(int tR); //!< Konstruktor, cellaméret
	static std::weak_ptr<Map> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard

	std::shared_ptr<GameObjectManager> gom; //!< GameObjectManager osztály példánya
	std::string pathToFields; //!< Pálya file-ok elérése útja
	SDL_Rect destRectDraw; //!< Háttér kirajzolásához szükséges
	SDL_Texture* path; //!< Aktuális háttér

	int tileRes; //!< Cella méret
	int map[ROWS][COLS]; //!< Aktuális pálya tárolása

	struct levelData { //!< Egy pálya adatai alapértékekkel
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

	levelData lvlData[MAPS]; //!< Összes pálya adatai

};