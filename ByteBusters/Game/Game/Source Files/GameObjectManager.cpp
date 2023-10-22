#pragma once
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Wall.h"
#include <iostream>

int GameObjectManager::tileSize;

Player* GameObjectManager::_player;
std::set<Enemy*> GameObjectManager::enemies;
std::set<Wall*> GameObjectManager::walls;
//std::set<Item*> GameObjectManager::items;

void GameObjectManager::SetTileSize(int size) {
	tileSize = size;
}

Player* GameObjectManager::CreateGameObject(PlayerTypes t, int x, int y) {
	_player = new Player(x, y, tileSize, tileSize, TextureManager::Deerly);
	return _player;
}

void GameObjectManager::CreateGameObject(EnemyTypes t, int x, int y) {
	switch (t)
	{
	case GameObjectManager::ape:
		enemies.insert(new Enemy(x, y, tileSize, tileSize, TextureManager::Enemy_Ape, _player));
		break;
	case GameObjectManager::deer:
		enemies.insert(new Enemy(x, y, tileSize, tileSize, TextureManager::Enemy_Deer, _player));
		break;
	case GameObjectManager::guard:
		enemies.insert(new Enemy(x, y, tileSize, tileSize, TextureManager::Enemy_Guard, _player));
		break;
	case GameObjectManager::homeless:
		enemies.insert(new Enemy(x, y, tileSize, tileSize, TextureManager::Enemy_Homeless, _player));
		break;
	case GameObjectManager::soldier:
		enemies.insert(new Enemy(x, y, tileSize, tileSize, TextureManager::Enemy_Soldier, _player));
		break;
	case GameObjectManager::yusri:
		enemies.insert(new Enemy(x, y, tileSize, tileSize, TextureManager::Yusri, _player));
		break;
	case GameObjectManager::joseph:
		enemies.insert(new Enemy(x, y, tileSize, tileSize, TextureManager::Joseph_White, _player));
		break;
	default:
		break;
	}
}

void GameObjectManager::CreateGameObject(WallTypes t, int x, int y) {
	switch (t)
	{
	case GameObjectManager::concrete02:
		walls.insert(new Wall(x, y, tileSize, tileSize, TextureManager::concrete02));
		break;
	case GameObjectManager::water:
		walls.insert(new Wall(x, y, tileSize, tileSize, TextureManager::water));
		break;
	case GameObjectManager::lava:
		walls.insert(new Wall(x, y, tileSize, tileSize, TextureManager::lava));
		break;
	default:
		break;
	}
}

void GameObjectManager::CreateGameObject(ItemTypes t, int x, int y) {
	//items.insert(new); item class doesnt exist yet
}

void GameObjectManager::DestroyAllGameObjects() {
	delete _player;
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	for (Wall* wall : walls)
	{
		delete wall;
	}
	/*for (Item* item : items)
	{
		delete item;
	}*/
}

void GameObjectManager::RenderAllGameObjects() {
	//std::cout << "GOM Render" << std::endl;
	for (Enemy* enemy : enemies)
	{
		enemy->Render();
	}
	for (Wall* wall : walls)
	{
		wall->Render();
	}
	/*for (Item* item : items)
	{
		item;
	}*/
	_player->Render();
}

void GameObjectManager::UpdateAllGameObjects() {
	
	for (Enemy* enemy : enemies)
	{
		enemy->Update();
	}
	/*for (Wall* wall : walls) //why would i do this?
	{
		wall->Update();
	}*/
	/*for (Item* item : items)
	{
		item;
	}*/
	_player->Update();
}


