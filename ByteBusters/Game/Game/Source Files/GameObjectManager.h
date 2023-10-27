#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Item.h"

#include <forward_list>

class GameObjectManager {
public:

	enum PlayerTypes
	{
		player //only one texture
	};

	enum EnemyTypes
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

	enum WallTypes
	{
		concrete02,
		water,
		lava
	};

	enum ItemTypes
	{
		item
	};

	static Player* CreateGameObject(PlayerTypes t, int x, int y);
	static void CreateGameObject(EnemyTypes t, int x, int y);
	static void CreateGameObject(WallTypes t, int x, int y);
	static void CreateGameObject(ItemTypes t, int x, int y);

	static void SetTileSize(int size);

	static void RenderAllGameObjects();

	static void UpdateAllGameObjects();

	static void DestroyAllGameObjects();

	static std::forward_list<Wall*>* GetWalls();	//passing the list by pointer
	static std::forward_list<Enemy*>* GetEnemies();	//passing the list by pointer
	static std::forward_list<Item*>* GetItems();	//passing the list by pointer
	static Player* GetPlayer();

private:
	//static int tileSize; // we could save this, but why

	static Player* _player;
	static std::forward_list<Enemy*> enemies;
	static std::forward_list<Wall*> walls;
	static std::forward_list<Item*> items;

};