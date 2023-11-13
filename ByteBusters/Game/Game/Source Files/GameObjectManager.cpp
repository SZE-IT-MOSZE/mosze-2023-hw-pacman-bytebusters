#pragma once
#include "GameObjectManager.h"
#include "TextureManager.h"
#include <iostream>
#include "Defines.h"

Player* GameObjectManager::_player;
SDL_Rect* GameObjectManager::playerRect;

//std::forward_list<Enemy*> GameObjectManager::enemies;
std::forward_list<Enemy_Melee*> GameObjectManager::meleeEnemies;
std::forward_list<Enemy_Ranged*> GameObjectManager::rangedEnemies;
std::forward_list<Enemy_NoAttack*> GameObjectManager::noAttackEnemies;

std::forward_list<Wall*> GameObjectManager::walls;
std::forward_list<Item*> GameObjectManager::items;
std::forward_list<Projectile*> GameObjectManager::playerProjectiles;
std::forward_list<Projectile*> GameObjectManager::enemyProjectiles;

//std::set<Enemy*> GameObjectManager::flaggedForDeleteEnemies;
std::set<Enemy_Melee*> GameObjectManager::flaggedForDeleteMeleeEnemies;
std::set<Enemy_Ranged*> GameObjectManager::flaggedForDeleteRangedEnemies;
std::set<Enemy_NoAttack*> GameObjectManager::flaggedForDeleteNoAttackEnemies;

std::set<Wall*> GameObjectManager::flaggedForDeleteWalls;
std::set<Item*> GameObjectManager::flaggedForDeleteItems;
std::set<Projectile*> GameObjectManager::flaggedForDeleteProjectiles;

void GameObjectManager::SetTileSize(int s) {
	GameObject::setTileSize(s);
}

bool GameObjectManager::AreAllItemsPickedUp() {
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
		meleeEnemies.push_front(new Enemy_Melee(x, y, FAST_ENEMY_SPEED, TextureManager::Enemy_Rat, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::ape:
		meleeEnemies.push_front(new Enemy_Melee(x, y, SLOW_ENEMY_SPEED, TextureManager::Enemy_Ape, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::deer:
		meleeEnemies.push_front(new Enemy_Melee(x, y, FAST_ENEMY_SPEED, TextureManager::Enemy_Deer, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::homeless:
		meleeEnemies.push_front(new Enemy_Melee(x, y, SLOW_ENEMY_SPEED, TextureManager::Enemy_Homeless, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::soldier:
		rangedEnemies.push_front(new Enemy_Ranged(x, y, SLOW_ENEMY_SPEED, TextureManager::Enemy_Soldier, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::yusri:
		noAttackEnemies.push_front(new Enemy_NoAttack(x, y, FAST_ENEMY_SPEED, TextureManager::Yusri, walls, playerProjectiles, _player));
		break;
	case GameObjectManager::joseph:
		noAttackEnemies.push_front(new Enemy_NoAttack(x, y, FAST_ENEMY_SPEED, TextureManager::Joseph_White, walls, playerProjectiles, _player));
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

int framteStart = SDL_GetTicks();
void GameObjectManager::RenderAllGameObjects() {
	
	//if ( SDL_GetTicks() - framteStart > 500) // if time to display next frame
	//{
	//	std::cout << "P: " << distance(playerProjectiles.begin(), playerProjectiles.end()) << std::endl;
	//	std::cout << "E: " << distance(enemyProjectiles.begin(), enemyProjectiles.end()) << std::endl;
	//	framteStart = SDL_GetTicks();
	//}
	
	for (Enemy_Melee* enemy : meleeEnemies)
	{
		enemy->Render();
	}
	for (Enemy_Ranged* enemy : rangedEnemies)
	{
		enemy->Render();
	}
	for (Enemy_NoAttack* enemy : noAttackEnemies)
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
	for (Projectile* projectile : playerProjectiles)
	{
		projectile->Render();
	}
	for (Projectile* projectile : enemyProjectiles)
	{
		projectile->Render();
	}
	_player->Render();
}

void GameObjectManager::UpdateAllGameObjects() {
	
	for (Enemy_Melee* enemy : meleeEnemies)
	{
		enemy->Update();
	}
	for (Enemy_Ranged* enemy : rangedEnemies)
	{
		enemy->Update();
	}
	for (Enemy_NoAttack* enemy : noAttackEnemies)
	{
		enemy->Update();
	}
	/*for (Wall* wall : walls) //walls dont have to be updated on current version
	{
		wall->Update();
	}*/
	for (Item* item : items)
	{
		item->Update();
	}
	for (Projectile* projectile : playerProjectiles)
	{
		projectile->Update();
	}
	for (Projectile* projectile : enemyProjectiles)
	{
		projectile->Update();
	}
	_player->Update();

	DeleteFlagged();
}

void GameObjectManager::DestroyAllExceptPlayer() {
	for (Enemy_Melee* enemy : meleeEnemies)
	{
		delete enemy;
	}
	meleeEnemies.clear();
	for (Enemy_Ranged* enemy : rangedEnemies)
	{
		delete enemy;
	}
	rangedEnemies.clear();
	for (Enemy_NoAttack* enemy : noAttackEnemies)
	{
		delete enemy;
	}
	noAttackEnemies.clear();
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

void GameObjectManager::DestroyAllGameObjects() { 
	DestroyAllExceptPlayer();
	delete _player;
}

/////////////////////////////////////////////////////////////// FLAGGING AND DELETEION
void GameObjectManager::FlagForDelete(Enemy_Melee* f) {
	flaggedForDeleteMeleeEnemies.insert(f);
}

void GameObjectManager::FlagForDelete(Enemy_Ranged* f) {
	flaggedForDeleteRangedEnemies.insert(f);
}

void GameObjectManager::FlagForDelete(Enemy_NoAttack* f) {
	flaggedForDeleteNoAttackEnemies.insert(f);
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

void GameObjectManager::DeleteFlagged() { 
	// for items a lighter built in version is working currently in Player.cpp
	// for the rest we need this to avoid invalidating the iterator while looping above the list

	
	for (Enemy_Melee* f : flaggedForDeleteMeleeEnemies)
	{
		meleeEnemies.remove(f);
		delete f;
	}
	flaggedForDeleteMeleeEnemies.clear();

	for (Enemy_Ranged* f : flaggedForDeleteRangedEnemies)
	{
		rangedEnemies.remove(f);
		delete f;
	}
	flaggedForDeleteRangedEnemies.clear();

	for (Enemy_NoAttack* f : flaggedForDeleteNoAttackEnemies)
	{
		noAttackEnemies.remove(f);
		delete f;
	}
	flaggedForDeleteNoAttackEnemies.clear();

	/*for (Wall* f : flaggedForDeleteWalls)
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

//implement hit=true if hitboxes overlap
void GameObjectManager::CheckEnemyHit(int x, int y, int range, bool right) { // this had to be impemented here to avoid circular references in headers
	SDL_Rect* enemyRect;
	int distance;
	for (Enemy_Melee* enemy : meleeEnemies)
	{
		enemyRect = enemy->GetDestRect();
		distance = sqrt(pow((playerRect->x - enemyRect->x), 2) + pow((playerRect->y - enemyRect->y), 2)); // make position getters for players and enemyies (all gameobject at that point)
		if (distance < range)
		{
			if (right && (playerRect->x < enemyRect->x))
			{
				FlagForDelete(enemy);
			}
			else if (playerRect->x > enemyRect->x)
			{
				FlagForDelete(enemy);
			}
		}
	}
	for (Enemy_Ranged* enemy : rangedEnemies)
	{
		enemyRect = enemy->GetDestRect();
		distance = sqrt(pow((playerRect->x - enemyRect->x), 2) + pow((playerRect->y - enemyRect->y), 2)); // make position getters for players and enemyies (all gameobject at that point)
		if (distance < range)
		{
			if (right && (playerRect->x < enemyRect->x))
			{
				FlagForDelete(enemy);
			}
			else if (playerRect->x > enemyRect->x)
			{
				FlagForDelete(enemy);
			}
		}
	}
	for (Enemy_NoAttack* enemy : noAttackEnemies)
	{
		enemyRect = enemy->GetDestRect();
		distance = sqrt(pow((playerRect->x - enemyRect->x), 2) + pow((playerRect->y - enemyRect->y), 2)); // make position getters for players and enemyies (all gameobject at that point)
		if (distance < range)
		{
			if (right && (playerRect->x < enemyRect->x))
			{
				FlagForDelete(enemy);
			}
			else if (playerRect->x > enemyRect->x)
			{
				FlagForDelete(enemy);
			}
		}
	}
}
