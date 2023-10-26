#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Item.h"

#include <set>
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

	static void DestroyAllGameObjects();

	static void SetTileSize(int size);

	static void RenderAllGameObjects();

	static void UpdateAllGameObjects();




private:
	static int tileSize;

	static Player* _player;
	static std::forward_list<Enemy*> enemies;
	static std::forward_list<Wall*> walls;
	static std::forward_list<Item*> items;

};