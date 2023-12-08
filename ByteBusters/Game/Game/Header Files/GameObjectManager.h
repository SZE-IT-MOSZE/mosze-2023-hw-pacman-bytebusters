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

	static std::shared_ptr<GameObjectManager> GetInstance(const int tR); //!< Singleton GetInstance, cellaméret
	GameObjectManager(GameObjectManager& other) = delete; //!< Törölt copy konstruktor
	void operator=(const GameObjectManager&) = delete; //!< Törölt = operátor
	~GameObjectManager() {}; //!< Destruktor

	enum PlayerTypes //!< Játékos
	{
		player //only one texture
	};
	enum EnemyTypes //!< Ellenség típusok
	{
		ape,
		deer,
		homeless,
		joseph,
		rat,
		soldier,
		yusri,
	};
	enum WallTypes //!< Fal típusok
	{
		concrete02,
		water,
		lava
	};
	enum ItemTypes //!< Item
	{
		item
	};
	enum ProjectileTypes //!< Játékos vagy Ellenség lövedék
	{
		playerProjectile,
		enemyProjectile
	};
	enum Direction { //!< Irányok számokra kódolva
		up = 0,
		down = 1,
		right = 2,
		left = 3
	};

	Player* CreateGameObject(PlayerTypes t, int x, int y); //!< Player létrehozása, pointer vissza adása
	void CreateGameObject(EnemyTypes t, int x, int y); //!< Ellenség léterhozása adott pozícióban
	void CreateGameObject(WallTypes t, int x, int y); //!< Fal létrehozása adott pozícióban
	void CreateGameObject(ItemTypes t, int x, int y); //!< Item létrehozása adott pozícióban
	void CreateGameObject(ProjectileTypes t, int x, int y, int d); //!< Item létrehozása adott pozícióban

	void RenderAllGameObjects(); //!< Game objektumok megjelenítése
	void UpdateAllGameObjects(); //!< Az objektumok frissítése
	void DestroyAllExceptPlayer(); //!< Az össze objektum törlése, kivétel a játékos

	void ResetPlayer(); //!< Játékos visszaállítása alapállapotba

	void CheckEnemyHit(int range, bool r); //!< A játékos megütötte-e az ellenséget, ütés távolság, irány

	void FlagForDelete(Enemy* f); //!< Ellenség megjelölésre törlésre
	void FlagForDelete(Wall* f); //!< Fal megjelölésre törlésre
	void FlagForDelete(Item* f); //!< Item megjelölésre törlésre
	void FlagForDelete(Projectile* f); //!< Lövedék megjelölésre törlésre

	bool AreAllItemsPickedUp(); //!< Az össze item-et fel vette-e a játékos
	
	bool AreJosephAndYusriDead(); //!< A fõ ellenségek halottak-e 

	std::forward_list<std::unique_ptr<Enemy>>*		GetEnemies() { return &enemies; } //!< Ellenségek listájának lekérése
	std::forward_list<std::unique_ptr<Wall>>*		GetWalls() { return &walls; } //!< Falak listájának lekérése
	std::forward_list<std::unique_ptr<Item>>*		GetItems() { return &items; } //!< Item-ek listájának lekérése
	std::forward_list<std::unique_ptr<Projectile>>*	GetPlayerProjectiles() { return &playerProjectiles; } //!< Játékos lövedékek listájának lekérése
	std::forward_list<std::unique_ptr<Projectile>>*	GetEnemyProjectiles() { return &enemyProjectiles; } //!< Játékos lövedékek listájának lekérése
	Player* GetPlayer() { return _player.get(); }  //!< Játékos lekérése

private:

	GameObjectManager(int tR); //!< Privát konstruktor
	static std::weak_ptr<GameObjectManager> instance_; //!< Singleton instance
	static std::mutex mutex_; //!< Thread guard

	std::unique_ptr<Player> _player; //!< Játékos objektum
	const SDL_Rect* playerRect; //!< Játékos hitbox

	Enemy* _joseph; //!< Joseph (fontos ellenség)
	Enemy* _yusri; //!< yusri (fontos ellenség)

	std::forward_list<std::unique_ptr<Enemy>>		enemies; //!< Ellenségek-k listája 
	std::forward_list<std::unique_ptr<Wall>>		walls; //!< Falak listája
	std::forward_list<std::unique_ptr<Item>>		items; //!< Itemek listája
	std::forward_list<std::unique_ptr<Projectile>>	playerProjectiles; //!< Játékos lövedékeinek listája
	std::forward_list<std::unique_ptr<Projectile>>	enemyProjectiles; //!< Ellenségek lövedékeinek listája

	std::set<Enemy*>				flaggedForDeleteEnemies; //!< Törlésre jelölt ellenségek
	std::set<Wall*>					flaggedForDeleteWalls; //!< Törlésre jelölt falak
	std::set<Item*>					flaggedForDeleteItems; //!< Törlésre jelölt item-ek
	std::set<Projectile*>			flaggedForDeleteProjectiles; //!< Törlésre jelölt lövedékek

	void DeleteFlagged(); //!< Törlésre jelölt objektumok törlése

};