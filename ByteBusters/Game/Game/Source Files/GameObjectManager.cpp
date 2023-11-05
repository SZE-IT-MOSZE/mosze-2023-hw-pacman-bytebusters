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
std::forward_list<Projectile*> GameObjectManager::projectiles;

std::forward_list<Projectile*> GameObjectManager::flaggedForDeleteProjectiles;

void GameObjectManager::SetTileSize(int s) {
	GameObject::setTileSize(s);
}

//std::forward_list<Wall*>* GameObjectManager::GetWalls() {
//	return &walls;
//}	
//
//std::forward_list<Enemy*>* GameObjectManager::GetEnemies() {
//	return &enemies;
//}	
//
//std::forward_list<Item*>* GameObjectManager::GetItems() {
//	return &items;
//}	

bool GameObjectManager::AreAllItemsPickedUp() {
	return items.empty();
}

//Player* GameObjectManager::GetPlayer() {
//	return _player;
//}

Player* GameObjectManager::CreateGameObject(PlayerTypes t, int x, int y) {
	_player = new Player(x, y, TextureManager::Deerly, walls, items);
	return _player;
}

void GameObjectManager::CreateGameObject(EnemyTypes t, int x, int y) {
	switch (t)
	{
	case GameObjectManager::rat:
		enemies.push_front(new Enemy(x, y, TextureManager::Enemy_Rat, walls, _player));
		break;
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

void GameObjectManager::CreateGameObject(TileTypes t, int x, int y) {
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

void GameObjectManager::CreateGameObject(ProjectileTypes t, int x, int y, int d) {
	projectiles.push_front(new Projectile(x, y, d, TextureManager::err_, walls));
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
	for (Projectile* projectile : projectiles)
	{
		projectile->Render();
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
	for (Projectile* projectile : projectiles)
	{
		projectile->Update();
	}
	_player->Update();

	DeleteFlagged();
}

void GameObjectManager::DestroyAllExceptPlayer() {
	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
	enemies.clear();
	for (Wall* wall : walls)
	{
		delete wall;
	}
	walls.clear();
	for (Item* item : items)
	{
		delete item;
	}
	items.clear(); // items should be empty at the end of a map
	for (Projectile* projectile : projectiles)
	{
		delete projectile;
	}
	projectiles.clear();
}

void GameObjectManager::DestroyAllGameObjects() { 
	DestroyAllExceptPlayer();
	delete _player;
}

void GameObjectManager::FlagForDelete(Projectile* p) {
	flaggedForDeleteProjectiles.push_front(p);
}

void GameObjectManager::DeleteFlagged() {
	for (Projectile* flaggedProjectile : flaggedForDeleteProjectiles)
	{
		projectiles.remove(flaggedProjectile);
		delete flaggedProjectile;
	}
	flaggedForDeleteProjectiles.clear();
}