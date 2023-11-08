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
		guard,
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
		projectile
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



	//static void FlagForDelete(Player* p); why did i write this here (i know i just dont want to admit)
	//static void FlagForDelete(Enemy* f);		
	static void FlagForDelete(Enemy_Melee* f);
	static void FlagForDelete(Enemy_Ranged* f);
	static void FlagForDelete(Enemy_NoAttack* f);
												//my head hurts
	static void FlagForDelete(Wall* f);			//really. im in phisical pain (idk how you spell physichal)
	static void FlagForDelete(Item* f);			//im off to play WOT
	static void FlagForDelete(Projectile* f);	//will continue tomorrow

	static bool AreAllItemsPickedUp(); //!< Annak az ellenõrzése, hogy az össze itemet fel vette-e a játékosunk
	
private:

	//static int tileSize; // we could save this, but why

	static Player* _player; //!< a player objetum mutatója

	//static std::forward_list<Enemy*> enemies; //!< Enemy-k listája

	static std::forward_list<Enemy_Melee*> meleeEnemies;
	static std::forward_list<Enemy_Ranged*> rangedEnemies; 
	static std::forward_list<Enemy_NoAttack*> noAttackEnemies; 

	static std::forward_list<Wall*> walls; //!< Falak listája
	static std::forward_list<Item*> items; //!< Itemek listája
	static std::forward_list<Projectile*> projectiles;

	//static std::set<Enemy_Melee*> flaggedForDeleteEnemies;
	static std::set<Enemy_Melee*> flaggedForDeleteMeleeEnemies;
	static std::set<Enemy_Ranged*> flaggedForDeleteRangedEnemies;
	static std::set<Enemy_NoAttack*> flaggedForDeleteNoAttackEnemies;  // used <set> because if a collision happens with a wall and an enemy at the same time it would get inserted twice and that would result in the code trying to delete it twice. which is bad.
	
	static std::set<Wall*> flaggedForDeleteWalls;
	static std::set<Item*> flaggedForDeleteItems;
	static std::set<Projectile*> flaggedForDeleteProjectiles;

	static void DeleteFlagged();

};