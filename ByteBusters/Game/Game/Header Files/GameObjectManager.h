#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Item.h"

#include <forward_list>

class GameObjectManager {
public:

	enum PlayerTypes //!< player t�pusok arra az esetre ha t�bb j�t�kos lesz
	{
		player //only one texture
	};

	enum EnemyTypes //!< a j�t�kban szerepl� ellens�get t�pusai
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

	enum WallTypes //!< A wall t�pusok amik a p�ly�kon szerepelni fognak
	{
		concrete02,
		water,
		lava
	};

	enum ItemTypes //!< Az item t�pusok amiket gy�jthet�nk egy adott p�ly�n
	{
		item
	};

	static Player* CreateGameObject(PlayerTypes t, int x, int y); //!< Player l�trehoz�sa pionter vissza ad�sa
	static void CreateGameObject(EnemyTypes t, int x, int y); //!< Ellens�g l�terhoz�sa adott poz�ci�ban
	static void CreateGameObject(WallTypes t, int x, int y); //!< Fal l�trehoz�sa adott poz�ci�ban
	static void CreateGameObject(ItemTypes t, int x, int y); //!< Item l�trehoz�sa adott poz�ci�ban

	static void SetTileSize(int size); //!< Cella m�ter be�ll�t�sa

	static void RenderAllGameObjects(); //!< Game objektumok renderel�se
	static void UpdateAllGameObjects(); //!< Az objektumok friss�t�se
	static void DestroyAllGameObjects(); //!< Az �sszes objektum t�rl�se
	static void DestroyAllExceptPlayer(); //!< Az �ssze objektum t�rl�se kiv�tel a j�t�kos

	static bool AreAllItemsPickedUp(); //!< Annak az ellen�rz�se, hogy az �ssze itemet fel vette-e a j�t�kosunk

	static std::forward_list<Wall*>* GetWalls(); //!<Fal lista mutat�ja  //passing the list by pointer
	static std::forward_list<Enemy*>* GetEnemies();	//!< Enemy lista mutat�ja  //passing the list by pointer
	static std::forward_list<Item*>* GetItems();	//!< Az item lista mutat�ja  //passing the list by pointer
	//static Player* GetPlayer();

private:
	//static int tileSize; // we could save this, but why

	static Player* _player; //!< a player objetum mutat�ja
	static std::forward_list<Enemy*> enemies; //!< Enemy-k list�ja
	static std::forward_list<Wall*> walls; //!< Falak list�ja
	static std::forward_list<Item*> items; //!< Itemek list�ja

};