#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Item.h"
#include "Projectile.h"

#include <forward_list>


class GameObjectManager {
public:

	enum PlayerTypes //!< player típusok arra az esetre ha több játékos lesz
	{
		player //only one texture
	};

	enum EnemyTypes //!< a játékban szereplõ ellenségek típusai
	{
		ape,
		deer,
		guard,
		homeless,
		joseph,
		rat,
		soldier,
		yusri,
	};

	enum TileTypes //!< A cella típusok amik a pályákon szerepelni fognak
	{
		concrete01,
		concrete02,
		dirt,
		jungle,
		water,
		lava
	};

	enum ItemTypes //!< Az item típusok amiket gyûjthetünk egy adott pályán
	{
		item
	};
	enum ProjectileTypes // i will work on this mess later
	{
		projectile
	};

	static Player* CreateGameObject(PlayerTypes t, int x, int y); //!< Player létrehozása pointer vissza adása
	static void CreateGameObject(EnemyTypes t, int x, int y); //!< Ellenség léterhozása adott pozícióban
	static void CreateGameObject(TileTypes t, int x, int y); //!< Fal létrehozása adott pozícióban
	static void CreateGameObject(ItemTypes t, int x, int y); //!< Item létrehozása adott pozícióban
	static void CreateGameObject(ProjectileTypes t, int x, int y, int d); //!< Item létrehozása adott pozícióban

	static void SetTileSize(int size); //!< Cella méret beállítása

	static void RenderAllGameObjects(); //!< Game objektumok renderelése
	static void UpdateAllGameObjects(); //!< Az objektumok frissítése
	static void DestroyAllGameObjects(); //!< Az összes objektum törlése
	static void DestroyAllExceptPlayer(); //!< Az össze objektum törlése kivétel a játékos



	//static void FlagForDelete(Player* p); why did i write this here (i know i just dont want to admit)
	static void FlagForDelete(Enemy* p);		//my head hurts
	static void FlagForDelete(Wall* p);			//really. im in phisical pain (idk how you spell physichal)
	static void FlagForDelete(Item* p);			//im off to play WOT
	static void FlagForDelete(Projectile* p);	//will continue tomorrow


	static bool AreAllItemsPickedUp(); //!< Annak az ellenõrzése, hogy az össze itemet fel vette-e a játékosunk

	//static std::forward_list<Wall*>* GetWalls(); //!<Fal lista mutatója  //passing the list by pointer
	//static std::forward_list<Enemy*>* GetEnemies();	//!< Enemy lista mutatója  //passing the list by pointer
	//static std::forward_list<Item*>* GetItems();	//!< Az item lista mutatója  //passing the list by pointer
	
	//static Player* GetPlayer();

private:
	//static int tileSize; // we could save this, but why

	static Player* _player; //!< a player objetum mutatója
	static std::forward_list<Enemy*> enemies; //!< Enemy-k listája
	static std::forward_list<Wall*> walls; //!< Falak listája
	static std::forward_list<Item*> items; //!< Itemek listája
	static std::forward_list<Projectile*> projectiles; // !!!!!!!!!!!! other functions with same name but different param

	static std::forward_list<Projectile*> flaggedForDeleteProjectiles;

	static void DeleteFlagged();

};