#pragma once
#include "GameObjectManager.h"
#include "TextureManager.h"
#include <iostream>
#include "Defines.h"

Player* GameObjectManager::_player;
SDL_Rect* GameObjectManager::playerRect;
std::forward_list<Enemy*> GameObjectManager::enemies;
//std::forward_list<Enemy*> GameObjectManager::meleeEnemies;
//std::forward_list<Enemy*> GameObjectManager::rangedEnemies;
//std::forward_list<Enemy*> GameObjectManager::noAttackEnemies;

//std::forward_list<Enemy_Melee*> GameObjectManager::meleeEnemies;
//std::forward_list<Enemy_Ranged*> GameObjectManager::rangedEnemies;
//std::forward_list<Enemy_NoAttack*> GameObjectManager::noAttackEnemies;

std::forward_list<Wall*> GameObjectManager::walls;
std::forward_list<Item*> GameObjectManager::items;
std::forward_list<Projectile*> GameObjectManager::playerProjectiles;
std::forward_list<Projectile*> GameObjectManager::enemyProjectiles;

std::set<Enemy*> GameObjectManager::flaggedForDeleteEnemies;
//std::set<Enemy_Melee*> GameObjectManager::flaggedForDeleteMeleeEnemies;
//std::set<Enemy_Ranged*> GameObjectManager::flaggedForDeleteRangedEnemies;
//std::set<Enemy_NoAttack*> GameObjectManager::flaggedForDeleteNoAttackEnemies;

std::set<Wall*> GameObjectManager::flaggedForDeleteWalls;
std::set<Item*> GameObjectManager::flaggedForDeleteItems;
std::set<Projectile*> GameObjectManager::flaggedForDeleteProjectiles;

void GameObjectManager::SetTileSize(int s) {
	GameObject::setTileSize(s);
}

bool GameObjectManager::AreAllItemsPickedUp() {
	std::cout << "Items left: " << std::distance(items.begin(), items.end()) << "\n";
	return items.empty();
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
		enemies.push_front(new Enemy_NoAttack(x, y, FAST_ENEMY_SPEED, TextureManager::Yusri, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::joseph:
		enemies.push_front(new Enemy_NoAttack(x, y, FAST_ENEMY_SPEED, TextureManager::Joseph_White, walls, playerProjectiles, _player));
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
		//std::cout << "playerProjectile" << std::endl;
		playerProjectiles.push_front(new Projectile(x, y, PROJECTILE_SPEED, d, TextureManager::projectile, walls));
		break;
	case GameObjectManager::enemyProjectile:
		//std::cout << "enemyProjectile" << std::endl;
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
	/*for (Wall* wall : walls) //why would i do this?
	{
		wall->Update();
	}*/
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
	delete _player;
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

	/*for (Wall* f : flaggedForDeleteWalls) // why would we do this? i know. but im not telling.
	{
		walls.remove(f);
		delete f;
	}
	flaggedForDeleteWalls.clear();*/

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
