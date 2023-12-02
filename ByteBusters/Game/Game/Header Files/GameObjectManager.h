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

	enum PlayerTypes //!< player t�pusok arra az esetre ha t�bb j�t�kos lesz
	{
		player //only one texture
	};
	enum EnemyTypes //!< a j�t�kban szerepl� ellens�gek t�pusai
	{
		ape,
		deer,
		homeless,
		joseph,
		rat,
		soldier,
		yusri,
	};
	enum WallTypes //!< A cella t�pusok amik a p�ly�kon szerepelni fognak
	{
		concrete02,
		water,
		lava
	};
	enum ItemTypes //!< Az item t�pusok amiket gy�jthet�nk egy adott p�ly�n
	{
		item
	};
	enum ProjectileTypes // i will work on this mess later
	{
		playerProjectile,
		enemyProjectile
	};



	Player* CreateGameObject(PlayerTypes t, int x, int y); //!< Player l�trehoz�sa pointer vissza ad�sa
	void CreateGameObject(EnemyTypes t, int x, int y); //!< Ellens�g l�terhoz�sa adott poz�ci�ban
	void CreateGameObject(WallTypes t, int x, int y); //!< Fal l�trehoz�sa adott poz�ci�ban
	void CreateGameObject(ItemTypes t, int x, int y); //!< Item l�trehoz�sa adott poz�ci�ban
	void CreateGameObject(ProjectileTypes t, int x, int y, int d); //!< Item l�trehoz�sa adott poz�ci�ban

	void RenderAllGameObjects(); //!< Game objektumok renderel�se
	void UpdateAllGameObjects(); //!< Az objektumok friss�t�se
	void DestroyAllGameObjects(); //!< Az �sszes objektum t�rl�se
	void DestroyAllExceptPlayer(); //!< Az �ssze objektum t�rl�se kiv�tel a j�t�kos

	void ResetPlayer();

	void CheckEnemyHit(int x, int y, int range, bool r);

	void FlagForDelete(Enemy* f);				
	void FlagForDelete(Wall* f);			////my head hurts. really. im in phisical pain (idk how you spell physichal)
	void FlagForDelete(Item* f);			//im off to play WOT
	void FlagForDelete(Projectile* f);	//will continue tomorrow

	bool AreAllItemsPickedUp(); //!< Annak az ellen�rz�se, hogy az �ssze itemet fel vette-e a j�t�kosunk
	
	bool AreJosephAndYusriDead();

private:

	GameObjectManager(int tR);
	static std::shared_ptr<GameObjectManager> instance_;
	static std::mutex mutex_;

	Player* _player; //!< a player objetum mutat�ja
	SDL_Rect* playerRect;

	Enemy* _joseph;
	Enemy* _yusri;

	std::forward_list<Enemy*> enemies; //!< Enemy-k list�ja 
	std::forward_list<Wall*> walls; //!< Falak list�ja
	std::forward_list<Item*> items; //!< Itemek list�ja
	std::forward_list<Projectile*> playerProjectiles;
	std::forward_list<Projectile*> enemyProjectiles;

	std::set<Enemy*> flaggedForDeleteEnemies;
	std::set<Wall*> flaggedForDeleteWalls;
	std::set<Item*> flaggedForDeleteItems;
	std::set<Projectile*> flaggedForDeleteProjectiles;

	void DeleteFlagged();

};