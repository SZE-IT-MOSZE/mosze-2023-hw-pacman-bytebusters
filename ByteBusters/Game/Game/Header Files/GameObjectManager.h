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
		guard,
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
		projectile
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



	//static void FlagForDelete(Player* p); why did i write this here (i know i just dont want to admit)
	//static void FlagForDelete(Enemy* f);		
	static void FlagForDelete(Enemy_Melee* f);
	static void FlagForDelete(Enemy_Ranged* f);
	static void FlagForDelete(Enemy_NoAttack* f);
												//my head hurts
	static void FlagForDelete(Wall* f);			//really. im in phisical pain (idk how you spell physichal)
	static void FlagForDelete(Item* f);			//im off to play WOT
	static void FlagForDelete(Projectile* f);	//will continue tomorrow

	static bool AreAllItemsPickedUp(); //!< Annak az ellen�rz�se, hogy az �ssze itemet fel vette-e a j�t�kosunk
	
private:

	//static int tileSize; // we could save this, but why

	static Player* _player; //!< a player objetum mutat�ja

	//static std::forward_list<Enemy*> enemies; //!< Enemy-k list�ja

	static std::forward_list<Enemy_Melee*> meleeEnemies;
	static std::forward_list<Enemy_Ranged*> rangedEnemies; 
	static std::forward_list<Enemy_NoAttack*> noAttackEnemies; 

	static std::forward_list<Wall*> walls; //!< Falak list�ja
	static std::forward_list<Item*> items; //!< Itemek list�ja
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