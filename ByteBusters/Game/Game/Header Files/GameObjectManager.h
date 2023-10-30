#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Item.h"

#include <forward_list>

class GameObjectManager {
public:

	enum PlayerTypes //!< player típusok arra az esetre ha több játékos lesz
	{
		player //only one texture
	};

	enum EnemyTypes //!< a játékban szereplõ ellenséget típusai
	{
		ape,
		deer,
		guard,
		homeless,
		soldier,
		yusri,
		joseph
		//random option might be added later
	};

	enum WallTypes //!< A wall típusok amik a pályákon szerepelni fognak
	{
		concrete02,
		water,
		lava
	};

	enum ItemTypes //!< Az item típusok amiket gyûjthetünk egy adott pályán
	{
		item
	};

	static Player* CreateGameObject(PlayerTypes t, int x, int y); //!< Player létrehozása pionter vissza adása
	static void CreateGameObject(EnemyTypes t, int x, int y); //!< Ellenség léterhozása adott pozícióban
	static void CreateGameObject(WallTypes t, int x, int y); //!< Fal létrehozása adott pozícióban
	static void CreateGameObject(ItemTypes t, int x, int y); //!< Item létrehozása adott pozícióban

	static void SetTileSize(int size); //!< Cella méter beállítása

	static void RenderAllGameObjects(); //!< Game objektumok renderelése
	static void UpdateAllGameObjects(); //!< Az objektumok frissítése
	static void DestroyAllGameObjects(); //!< Az összes objektum törlése
	static void DestroyAllExceptPlayer(); //!< Az össze objektum törlése kivétel a játékos

	static bool AreAllItemsPickedUp(); //!< Annak az ellenõrzése, hogy az össze itemet fel vette-e a játékosunk

	static std::forward_list<Wall*>* GetWalls(); //!<Fal lista mutatója  //passing the list by pointer
	static std::forward_list<Enemy*>* GetEnemies();	//!< Enemy lista mutatója  //passing the list by pointer
	static std::forward_list<Item*>* GetItems();	//!< Az item lista mutatója  //passing the list by pointer
	//static Player* GetPlayer();

private:
	//static int tileSize; // we could save this, but why

	static Player* _player; //!< a player objetum mutatója
	static std::forward_list<Enemy*> enemies; //!< Enemy-k listája
	static std::forward_list<Wall*> walls; //!< Falak listája
	static std::forward_list<Item*> items; //!< Itemek listája

};