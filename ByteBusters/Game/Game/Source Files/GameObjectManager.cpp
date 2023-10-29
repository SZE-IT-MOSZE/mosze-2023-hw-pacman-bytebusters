#pragma once
#include "GameObjectManager.h"
#include "TextureManager.h"
#include "Wall.h"
#include <iostream>

//int GameObjectManager::tileSize;

Player* GameObjectManager::_player;
std::forward_list<Enemy*> GameObjectManager::enemies;
std::forward_list<Wall*> GameObjectManager::walls;
std::forward_list<Item*> GameObjectManager::items;

void GameObjectManager::SetTileSize(int s) {
	GameObject::setTileSize(s);
}

std::forward_list<Wall*>* GameObjectManager::GetWalls() {
	return &walls;
}	

std::forward_list<Enemy*>* GameObjectManager::GetEnemies() {
	return &enemies;
}	

std::forward_list<Item*>* GameObjectManager::GetItems() {
	return &items;
}	

Player* GameObjectManager::GetPlayer() {
	return _player;
}



Player* GameObjectManager::CreateGameObject(PlayerTypes t, int x, int y) {
	_player = new Player(x, y, TextureManager::Deerly, walls, items);
	return _player;
}

void GameObjectManager::CreateGameObject(EnemyTypes t, int x, int y) {
	switch (t)
	{
	case GameObjectManager::ape:
		enemies.push_front(new Enemy(x, y, TextureManager::Enemy_Ape, walls, _player));
		break;
	case GameObjectManager::deer:
		enemies.push_front(new Enemy(x, y, TextureManager::Enemy_Deer, walls, _player));
		break;
	case GameObjectManager::guard:
		enemies.push_front(new Enemy(x, y, TextureManager::Enemy_Guard, walls, _player));
		break;
	case GameObjectManager::homeless:
		enemies.push_front(new Enemy(x, y, TextureManager::Enemy_Homeless, walls, _player));
		break;
	case GameObjectManager::soldier:
		enemies.push_front(new Enemy(x, y, TextureManager::Enemy_Soldier, walls, _player));
		break;
	case GameObjectManager::yusri:
		enemies.push_front(new Enemy(x, y, TextureManager::Yusri, walls, _player));
		break;
	case GameObjectManager::joseph:
		enemies.push_front(new Enemy(x, y, TextureManager::Joseph_White, walls, _player));
		break;
	default:
		break;
	}
}

void GameObjectManager::CreateGameObject(WallTypes t, int x, int y) {
	switch (t)
	{
	case GameObjectManager::concrete02:
		walls.push_front(new Wall(x, y, TextureManager::concrete02));
		break;
	case GameObjectManager::water:
		walls.push_front(new Wall(x, y, TextureManager::water));
		break;
	case GameObjectManager::lava:
		walls.push_front(new Wall(x, y, TextureManager::lava));
		break;
	default:
		break;
	}
}

void GameObjectManager::CreateGameObject(ItemTypes t, int x, int y) {
	items.push_front(new Item(x, y, TextureManager::paper));
}


void GameObjectManager::RenderAllGameObjects() {
	for (Enemy* enemy : enemies)
	{
		enemy->Render();
	}
	for (Wall* wall : walls)
	{
		wall->Render();
	}
	for (Item* item : items)
	{
		item->Render();
	}
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
	for (Item* item : items)
	{
		item->Update();
	}
	_player->Update();
}

void GameObjectManager::DestroyAllGameObjects() { 
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	for (Wall* wall : walls)
	{
		delete wall;
	}
	for (Item* item : items)
	{
		delete item;
	}
	delete _player;
}

