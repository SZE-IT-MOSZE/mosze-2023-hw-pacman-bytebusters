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

#include <mutex>

class GameObjectManager {
public:

	static std::shared_ptr<GameObjectManager> GetInstance(const int tR);
	GameObjectManager(GameObjectManager& other) = delete;
	void operator=(const GameObjectManager&) = delete;
	~GameObjectManager();

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



	Player* CreateGameObject(PlayerTypes t, int x, int y); //!< Player létrehozása pointer vissza adása
	void CreateGameObject(EnemyTypes t, int x, int y); //!< Ellenség léterhozása adott pozícióban
	void CreateGameObject(WallTypes t, int x, int y); //!< Fal létrehozása adott pozícióban
	void CreateGameObject(ItemTypes t, int x, int y); //!< Item létrehozása adott pozícióban
	void CreateGameObject(ProjectileTypes t, int x, int y, int d); //!< Item létrehozása adott pozícióban

	void RenderAllGameObjects(); //!< Game objektumok renderelése
	void UpdateAllGameObjects(); //!< Az objektumok frissítése
	void DestroyAllGameObjects(); //!< Az összes objektum törlése
	void DestroyAllExceptPlayer(); //!< Az össze objektum törlése kivétel a játékos

	void ResetPlayer();

	void CheckEnemyHit(int x, int y, int range, bool r);

	void FlagForDelete(Enemy* f);				
	void FlagForDelete(Wall* f);			////my head hurts. really. im in phisical pain (idk how you spell physichal)
	void FlagForDelete(Item* f);			//im off to play WOT
	void FlagForDelete(Projectile* f);	//will continue tomorrow

	bool AreAllItemsPickedUp(); //!< Annak az ellenõrzése, hogy az össze itemet fel vette-e a játékosunk
	
	bool AreJosephAndYusriDead();

private:

	GameObjectManager(int tR);
	static std::shared_ptr<GameObjectManager> instance_;
	static std::mutex mutex_;

	Player* _player; //!< a player objetum mutatója
	SDL_Rect* playerRect;

	Enemy* _joseph;
	Enemy* _yusri;

	std::forward_list<Enemy*> enemies; //!< Enemy-k listája 
	std::forward_list<Wall*> walls; //!< Falak listája
	std::forward_list<Item*> items; //!< Itemek listája
	std::forward_list<Projectile*> playerProjectiles;
	std::forward_list<Projectile*> enemyProjectiles;

	std::set<Enemy*> flaggedForDeleteEnemies;
	std::set<Wall*> flaggedForDeleteWalls;
	std::set<Item*> flaggedForDeleteItems;
	std::set<Projectile*> flaggedForDeleteProjectiles;

	void DeleteFlagged();

};