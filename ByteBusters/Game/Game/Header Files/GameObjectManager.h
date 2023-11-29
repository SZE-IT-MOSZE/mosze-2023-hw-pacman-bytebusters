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

	static Player* CreateGameObject(PlayerTypes t, int x, int y); //!< Player l�trehoz�sa pointer vissza ad�sa
	static void CreateGameObject(EnemyTypes t, int x, int y); //!< Ellens�g l�terhoz�sa adott poz�ci�ban
	static void CreateGameObject(WallTypes t, int x, int y); //!< Fal l�trehoz�sa adott poz�ci�ban
	static void CreateGameObject(ItemTypes t, int x, int y); //!< Item l�trehoz�sa adott poz�ci�ban
	static void CreateGameObject(ProjectileTypes t, int x, int y, int d); //!< Item l�trehoz�sa adott poz�ci�ban


	static void SetTileSize(int size); //!< Cella m�ret be�ll�t�sa

	static void RenderAllGameObjects(); //!< Game objektumok renderel�se
	static void UpdateAllGameObjects(); //!< Az objektumok friss�t�se
	static void DestroyAllGameObjects(); //!< Az �sszes objektum t�rl�se
	static void DestroyAllExceptPlayer(); //!< Az �ssze objektum t�rl�se kiv�tel a j�t�kos

	static void ResetPlayer();

	static void CheckEnemyHit(int x, int y, int range, bool r);

	static void FlagForDelete(Enemy* f);		
													
	static void FlagForDelete(Wall* f);			////my head hurts. really. im in phisical pain (idk how you spell physichal)
	static void FlagForDelete(Item* f);			//im off to play WOT
	static void FlagForDelete(Projectile* f);	//will continue tomorrow

	static bool AreAllItemsPickedUp(); //!< Annak az ellen�rz�se, hogy az �ssze itemet fel vette-e a j�t�kosunk
	
	static bool AreJosephAndYusriDead();

private:

	static Player* _player; //!< a player objetum mutat�ja
	static SDL_Rect* playerRect;

	static Enemy* _joseph;
	static Enemy* _yusri;

	static std::forward_list<Enemy*> enemies; //!< Enemy-k list�ja

	static std::forward_list<Wall*> walls; //!< Falak list�ja
	static std::forward_list<Item*> items; //!< Itemek list�ja
	static std::forward_list<Projectile*> playerProjectiles;
	static std::forward_list<Projectile*> enemyProjectiles;

	static std::set<Enemy*> flaggedForDeleteEnemies;
	
	static std::set<Wall*> flaggedForDeleteWalls;
	static std::set<Item*> flaggedForDeleteItems;
	static std::set<Projectile*> flaggedForDeleteProjectiles;

	static void DeleteFlagged();

};