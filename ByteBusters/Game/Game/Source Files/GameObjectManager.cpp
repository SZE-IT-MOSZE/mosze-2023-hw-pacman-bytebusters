#pragma once
#include "GameObjectManager.h"
#include "TextureManager.h"
#include <iostream>
#include "Defines.h"


//int GameObjectManager::tileSize;

Player* GameObjectManager::_player;

//std::forward_list<Enemy*> GameObjectManager::enemies;
std::forward_list<Enemy_Melee*> GameObjectManager::meleeEnemies;
std::forward_list<Enemy_Ranged*> GameObjectManager::rangedEnemies;
std::forward_list<Enemy_NoAttack*> GameObjectManager::noAttackEnemies;

std::forward_list<Wall*> GameObjectManager::walls;
std::forward_list<Item*> GameObjectManager::items;
std::forward_list<Projectile*> GameObjectManager::projectiles;

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
	_player = new Player(x, y, PLAYERSPEED, TextureManager::Deerly, walls, items);
	return _player;
}

void GameObjectManager::CreateGameObject(EnemyTypes t, int x, int y) {
	switch (t)
	{
	case GameObjectManager::rat:
		meleeEnemies.push_front(new Enemy_Melee(x, y, FASTENEMYSPEED, TextureManager::Enemy_Rat, walls, projectiles, _player));
		break;
	case GameObjectManager::ape:
		meleeEnemies.push_front(new Enemy_Melee(x, y, SLOWENEMYSPEED, TextureManager::Enemy_Ape, walls, projectiles, _player));
		break;
	case GameObjectManager::deer:
		meleeEnemies.push_front(new Enemy_Melee(x, y, FASTENEMYSPEED, TextureManager::Enemy_Deer, walls, projectiles, _player));
		break;
	case GameObjectManager::guard:
		rangedEnemies.push_front(new Enemy_Ranged(x, y, SLOWENEMYSPEED, TextureManager::Enemy_Guard, walls, projectiles, _player));
		break;
	case GameObjectManager::homeless:
		meleeEnemies.push_front(new Enemy_Melee(x, y, SLOWENEMYSPEED, TextureManager::Enemy_Homeless, walls, projectiles, _player));
		break;
	case GameObjectManager::soldier:
		rangedEnemies.push_front(new Enemy_Ranged(x, y, SLOWENEMYSPEED, TextureManager::Enemy_Soldier, walls, projectiles, _player));
		break;
	case GameObjectManager::yusri:
		noAttackEnemies.push_front(new Enemy_NoAttack(x, y, FASTENEMYSPEED, TextureManager::Yusri, walls, projectiles, _player));
		break;
	case GameObjectManager::joseph:
		noAttackEnemies.push_front(new Enemy_NoAttack(x, y, FASTENEMYSPEED, TextureManager::Joseph_White, walls, projectiles, _player));
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
	projectiles.push_front(new Projectile(x, y, PROJECTILESPEED, d, TextureManager::projectile, walls));
}


void GameObjectManager::RenderAllGameObjects() {
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
	for (Projectile* projectile : projectiles)
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

void GameObjectManager::DeleteFlagged() { // uncomment if implemented (for items a lighter built in version is working currently in Player.cpp)

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
		projectiles.remove(f);
		delete f;
	}
	flaggedForDeleteProjectiles.clear();

}