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
	Map(Map& other) = delete; //!< T�r�lt copy konstruktor
	void operator=(const Map&) = delete; //!< T�r�lt = oper�tor
	~Map() {}; //!< Destruktor

	void SaveMapNumber(int mapNum); //!< Adott p�lyasz�m ment�se file-ba
	int LoadMapNumber(); //!< Mentett p�lyasz�m bet�lt�se file-b�l
	int LoadMap(int lvl); //!< Adott p�lya bet�lt�se
	void SpawnGameObjects(int lvl); //!< Objektumok l�tehoz�sa az adott p�ly�hoz
	void DrawMap(); //!< Az adott p�lya h�tter�nek a kirajzol�sa

private:

	Map(int tR); //!< Konstruktor, cellam�ret
	static std::weak_ptr<Map> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard

	std::shared_ptr<GameObjectManager> gom; //!< GameObjectManager oszt�ly p�ld�nya
	std::string pathToFields; //!< P�lya file-ok el�r�se �tja
	SDL_Rect destRectDraw; //!< H�tt�r kirajzol�s�hoz sz�ks�ges
	SDL_Texture* path; //!< Aktu�lis h�tt�r

	int tileRes; //!< Cella m�ret
	int map[ROWS][COLS]; //!< Aktu�lis p�lya t�rol�sa

	struct levelData { //!< Egy p�lya adatai alap�rt�kekkel
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

	levelData lvlData[MAPS]; //!< �sszes p�lya adatai

};