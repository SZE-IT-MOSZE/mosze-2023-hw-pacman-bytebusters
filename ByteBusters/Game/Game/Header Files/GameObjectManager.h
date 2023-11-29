#pragma once
#include "Player.h"

#include "Enemy_Melee.h"
#include "Enemy_Ranged.h"
#include "Enemy_NoAttack.h"

#include "Wall.h"
#include "Item.h"
#include "Projectile.h"

#include <forward_list>
#include <set>


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
		homeless,
		joseph,
		rat,
		soldier,
		yusri,
	};
	enum WallTypes //!< A cella típusok amik a pályákon szerepelni fognak
	{
		concrete02,
		water,
		lava
	};
	enum ItemTypes //!< Az item típusok amiket gyûjthetünk egy adott pályán
	{
		item
	};
	enum ProjectileTypes // i will work on this mess later
	{
		playerProjectile,
		enemyProjectile
	};

	static Player* CreateGameObject(PlayerTypes t, int x, int y); //!< Player létrehozása pointer vissza adása
	static void CreateGameObject(EnemyTypes t, int x, int y); //!< Ellenség léterhozása adott pozícióban
	static void CreateGameObject(WallTypes t, int x, int y); //!< Fal létrehozása adott pozícióban
	static void CreateGameObject(ItemTypes t, int x, int y); //!< Item létrehozása adott pozícióban
	static void CreateGameObject(ProjectileTypes t, int x, int y, int d); //!< Item létrehozása adott pozícióban


	static void SetTileSize(int size); //!< Cella méret beállítása

	static void RenderAllGameObjects(); //!< Game objektumok renderelése
	static void UpdateAllGameObjects(); //!< Az objektumok frissítése
	static void DestroyAllGameObjects(); //!< Az összes objektum törlése
	static void DestroyAllExceptPlayer(); //!< Az össze objektum törlése kivétel a játékos

	static void ResetPlayer();

	static void CheckEnemyHit(int x, int y, int range, bool r);

	static void FlagForDelete(Enemy* f);		
													
	static void FlagForDelete(Wall* f);			////my head hurts. really. im in phisical pain (idk how you spell physichal)
	static void FlagForDelete(Item* f);			//im off to play WOT
	static void FlagForDelete(Projectile* f);	//will continue tomorrow

	static bool AreAllItemsPickedUp(); //!< Annak az ellenõrzése, hogy az össze itemet fel vette-e a játékosunk
	
	static bool AreJosephAndYusriDead();

private:

	static Player* _player; //!< a player objetum mutatója
	static SDL_Rect* playerRect;

	static Enemy* _joseph;
	static Enemy* _yusri;

	static std::forward_list<Enemy*> enemies; //!< Enemy-k listája

	static std::forward_list<Wall*> walls; //!< Falak listája
	static std::forward_list<Item*> items; //!< Itemek listája
	static std::forward_list<Projectile*> playerProjectiles;
	static std::forward_list<Projectile*> enemyProjectiles;

	static std::set<Enemy*> flaggedForDeleteEnemies;
	
	static std::set<Wall*> flaggedForDeleteWalls;
	static std::set<Item*> flaggedForDeleteItems;
	static std::set<Projectile*> flaggedForDeleteProjectiles;

	static void DeleteFlagged();

};