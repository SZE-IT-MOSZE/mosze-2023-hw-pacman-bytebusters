#pragma once
#include "GameObjectManager.h"
#include "TextureManager.h"
#include <iostream>
#include "Defines.h"

std::shared_ptr<GameObjectManager> GameObjectManager::instance_{ nullptr };
std::mutex GameObjectManager::mutex_;

std::shared_ptr<GameObjectManager> GameObjectManager::GetInstance(const int tR) {
	std::lock_guard<std::mutex> lock(mutex_);
	if (!instance_) {
		instance_ = std::shared_ptr<GameObjectManager>(new GameObjectManager(tR));
		//cant use make_shared() without some "black magic" to make the private constructor visible for make_shared()
	}
	return instance_;
}

GameObjectManager::GameObjectManager(const int tR) {
	GameObject::setTileSize(tR);

	_player = nullptr;
	playerRect = nullptr;

	_joseph = nullptr;
	_yusri = nullptr;
}

GameObjectManager::~GameObjectManager() {
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

bool GameObjectManager::AreAllItemsPickedUp() {
	return items.empty();
}

bool GameObjectManager::AreJosephAndYusriDead()
{
	for (auto enemy : enemies)
	{
		if (enemy == _joseph) return false;
		if (enemy == _yusri) return false;
	}
	return true;
}

Player* GameObjectManager::CreateGameObject(PlayerTypes t, int x, int y) {
	_player = new Player(x, y, PLAYER_SPEED, TextureManager::Deerly, walls, items, enemyProjectiles);
	playerRect = _player->GetDestRect();
	return _player;
}

void GameObjectManager::CreateGameObject(EnemyTypes t, int x, int y) {
	switch (t)
	{
	case GameObjectManager::rat:
		enemies.push_front(new Enemy_Melee(x, y, FAST_ENEMY_SPEED, TextureManager::Enemy_Rat, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::ape:
		enemies.push_front(new Enemy_Melee(x, y, SLOW_ENEMY_SPEED, TextureManager::Enemy_Ape, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::deer:
		enemies.push_front(new Enemy_Melee(x, y, FAST_ENEMY_SPEED, TextureManager::Enemy_Deer, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::homeless:
		enemies.push_front(new Enemy_Melee(x, y, SLOW_ENEMY_SPEED, TextureManager::Enemy_Homeless, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::soldier:
		enemies.push_front(new Enemy_Ranged(x, y, SLOW_ENEMY_SPEED, TextureManager::Enemy_Soldier, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::yusri:
		_yusri = new Enemy_NoAttack(x, y, FAST_ENEMY_SPEED, TextureManager::Yusri, walls, playerProjectiles, _player);
		enemies.push_front(_yusri);
		break;
	case GameObjectManager::joseph:
		_joseph = new Enemy_NoAttack(x, y, FAST_ENEMY_SPEED, TextureManager::Joseph_White, walls, playerProjectiles, _player);
		enemies.push_front(_joseph);
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

void GameObjectManager::CreateGameObject(ProjectileTypes t, int x, int y, int d) {
	switch (t)
	{
	case GameObjectManager::playerProjectile:
		playerProjectiles.push_front(new Projectile(x, y, PROJECTILE_SPEED, d, TextureManager::projectile, walls));
		break;
	case GameObjectManager::enemyProjectile:
		enemyProjectiles.push_front(new Projectile(x, y, PROJECTILE_SPEED, d, TextureManager::projectile, walls));
		break;
	default:
		break;
	}

}

void GameObjectManager::RenderAllGameObjects() {
	
	for (auto enemy : enemies)
	{
		enemy->Render();
	}
	for (auto wall : walls)
	{
		wall->Render();
	}
	for (auto item : items)
	{
		item->Render();
	}
	for (auto projectile : playerProjectiles)
	{
		projectile->Render();
	}
	for (auto projectile : enemyProjectiles)
	{
		projectile->Render();
	}
	_player->Render();
}

void GameObjectManager::UpdateAllGameObjects() {
	
	for (auto enemy : enemies)
	{
		enemy->Update();
	}
	for (auto item : items)
	{
		item->Update();
	}
	for (auto projectile : playerProjectiles)
	{
		projectile->Update();
	}
	for (auto projectile : enemyProjectiles)
	{
		projectile->Update();
	}
	_player->Update();

	DeleteFlagged();
}

void GameObjectManager::DestroyAllExceptPlayer() {
	for (auto enemy : enemies)
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
	for (Projectile* projectile : playerProjectiles)
	{
		delete projectile;
	}
	playerProjectiles.clear();
	for (Projectile* projectile : enemyProjectiles)
	{
		delete projectile;
	}
	enemyProjectiles.clear();
}

void GameObjectManager::ResetPlayer() {
	_player->Reset();
}

void GameObjectManager::DestroyAllGameObjects() { 
	DestroyAllExceptPlayer();
	if (_player != nullptr)
	{
		delete _player;
	}
}

/////////////////////////////////////////////////////////////// FLAGGING AND DELETEION
void GameObjectManager::FlagForDelete(Enemy* f) {
	flaggedForDeleteEnemies.insert(f);
}

void GameObjectManager::FlagForDelete(Wall* f) {
	flaggedForDeleteWalls.insert(f);
}

void GameObjectManager::FlagForDelete(Item* f) {
	flaggedForDeleteItems.insert(f);
}

void GameObjectManager::FlagForDelete(Projectile* f) {
	flaggedForDeleteProjectiles.insert(f);
}

void GameObjectManager::DeleteFlagged() { // (for items a lighter built in version is working currently in Player.cpp)

	for (auto f : flaggedForDeleteEnemies)
	{
		enemies.remove(f);
		delete f;
	}
	flaggedForDeleteEnemies.clear();

	/*for (Item* f : flaggedForDeleteItems)
	{
		items.remove(f);
		delete f;
	}
	flaggedForDeleteItems.clear();*/

	for (Projectile* f : flaggedForDeleteProjectiles)
	{
		playerProjectiles.remove(f);
		enemyProjectiles.remove(f);
		delete f;
	}
	flaggedForDeleteProjectiles.clear();

}

void GameObjectManager::CheckEnemyHit(int x, int y, int range, bool right) { // okay, this iiiiis a bit bad
	SDL_Rect* enemyRect;
	int distance;
	for (auto enemy : enemies)
	{
		enemyRect = enemy->GetDestRect();
		if (SDL_HasIntersection(playerRect, enemyRect)) {
			FlagForDelete(enemy);
			continue;
		}
		distance = (int)sqrt(pow((playerRect->x - enemyRect->x), 2) + pow((playerRect->y - enemyRect->y), 2)); // make position getters for players and enemyies (all gameobject at that point)
		if (distance < range)
		{
			if ( (right && (playerRect->x < enemyRect->x)) || (playerRect->x > enemyRect->x) )
			{
				FlagForDelete(enemy);
			}
		}
	}
}
