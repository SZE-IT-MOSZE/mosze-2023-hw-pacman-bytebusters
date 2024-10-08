#pragma once
#include "Game.h"
#include "Defines.h"
#include "TextureManager.h"
#include "GameObjectManager.h"
#include <iostream>
#include <algorithm>

std::weak_ptr<GameObjectManager> GameObjectManager::instance_;
std::mutex GameObjectManager::mutex_;

std::shared_ptr<GameObjectManager> GameObjectManager::GetInstance(const int tR) {
	std::lock_guard<std::mutex> lock(mutex_);
	std::shared_ptr<GameObjectManager> sharedInstance;
	if (!(sharedInstance = instance_.lock())) {
		sharedInstance = std::shared_ptr<GameObjectManager>(new GameObjectManager(tR));
		instance_ = sharedInstance;
	}
	return sharedInstance;
}

GameObjectManager::GameObjectManager(const int tR) {
	tileRes = tR;

	_player = nullptr;
	playerDestRect = nullptr;

	_joseph = nullptr;
	_yusri = nullptr;

	DeadFrameDst.x = DeadFrameDst.y = 0;
	DeadFrameDst.w = DeadFrameDst.h = tileRes;

	DeadFrameSrc.x = DeadFrameSrc.y = 0;
	DeadFrameSrc.w = DeadFrameSrc.h = ENEMY_SPRITE_SIZE;
}

bool GameObjectManager::AreAllItemsPickedUp() {
	return items.empty();
}

bool GameObjectManager::AreJosephAndYusriDead()
{
	for (auto& enemy : enemies)
	{
		if (enemy.get() == _joseph) return false;
		if (enemy.get() == _yusri) return false;
	}
	return true;
}

Player* GameObjectManager::CreateGameObject(PlayerTypes t, int x, int y) {
	_player = std::make_unique<Player>(x, y, PLAYER_SPEED, TextureManager::Deerly);
	playerDestRect = _player->GetDestRectPtr();
	return _player.get();
}

void GameObjectManager::CreateGameObject(EnemyTypes t, int x, int y) {
	switch (t)
	{
	case GameObjectManager::rat:
		enemies.push_front(std::make_unique<Enemy_Melee>(x, y, FAST_ENEMY_SPEED, TextureManager::Enemy_Rat));
		break;
	case GameObjectManager::ape:
		enemies.push_front(std::make_unique<Enemy_Melee>(x, y, SLOW_ENEMY_SPEED, TextureManager::Enemy_Ape));
		break;
	case GameObjectManager::deer:
		enemies.push_front(std::make_unique<Enemy_Melee>(x, y, FAST_ENEMY_SPEED, TextureManager::Enemy_Deer));
		break;
	case GameObjectManager::homeless:
		enemies.push_front(std::make_unique<Enemy_Melee>(x, y, SLOW_ENEMY_SPEED, TextureManager::Enemy_Homeless));
		break;
	case GameObjectManager::soldier:
		enemies.push_front(std::make_unique<Enemy_Ranged>(x, y, SLOW_ENEMY_SPEED, TextureManager::Enemy_Soldier));
		break;
	case GameObjectManager::yusri:
		enemies.push_front(std::make_unique<Enemy_NoAttack>(x, y, FAST_ENEMY_SPEED, TextureManager::Yusri));
		_yusri = enemies.front().get();
		break;
	case GameObjectManager::joseph:
		enemies.push_front(std::make_unique<Enemy_NoAttack>(x, y, FAST_ENEMY_SPEED, TextureManager::Joseph_White));
		_joseph = enemies.front().get();
		break;
	default:
		break;
	}
}

void GameObjectManager::CreateGameObject(WallTypes t, int x, int y) {
	switch (t)
	{
	case GameObjectManager::concrete02:
		walls.push_front(std::make_unique<Wall>(x, y, TextureManager::concrete02));
		break;
	case GameObjectManager::water:
		walls.push_front(std::make_unique<Wall>(x, y, TextureManager::water));
		break;
	case GameObjectManager::lava:
		walls.push_front(std::make_unique<Wall>(x, y, TextureManager::lava));
		break;
	default:
		break;
	}
}

void GameObjectManager::CreateGameObject(ItemTypes t, int x, int y) {
	items.push_front(std::make_unique<Item>(x, y, TextureManager::paper));
}

void GameObjectManager::CreateGameObject(ProjectileTypes t, int x, int y, int d) {
	switch (t)
	{
	case GameObjectManager::playerProjectile:
		playerProjectiles.push_front(std::make_unique<Projectile>(x, y, PROJECTILE_SPEED, d, TextureManager::projectile));
		break;
	case GameObjectManager::enemyProjectile:
		enemyProjectiles.push_front(std::make_unique<Projectile>(x, y, PROJECTILE_SPEED, d, TextureManager::projectile));
		break;
	default:
		break;
	}
}

void GameObjectManager::RenderAllGameObjects() {
	DrawDeathRow();
	for (auto& enemy : enemies)
	{
		enemy->Render();
	}
	for (auto& wall : walls)
	{
		wall->Render();
	}
	for (auto& item : items)
	{
		item->Render();
	}
	for (auto& projectile : playerProjectiles)
	{
		projectile->Render();
	}
	for (auto& projectile : enemyProjectiles)
	{
		projectile->Render();
	}
	if (_player)
	{
		_player->Render();
	}
}

void GameObjectManager::UpdateAllGameObjects() {
	for (auto& enemy : enemies)
	{
		enemy->Update();
	}
	for (auto& item : items)
	{
		item->Update();
	}
	for (auto& projectile : playerProjectiles)
	{
		projectile->Update();
	}
	for (auto& projectile : enemyProjectiles)
	{
		projectile->Update();
	}
	if (_player)
	{
		_player->Update();
	}
	DeleteFlagged();
}

void GameObjectManager::DestroyAllExceptPlayer() {
	enemies.clear();
	walls.clear();
	items.clear(); // items should be empty at the end of a map
	playerProjectiles.clear();
	enemyProjectiles.clear();
	DeathRow.clear();
}

void GameObjectManager::ResetPlayer() {
	_player->Reset();
}

void GameObjectManager::PushToDeathRow(SDL_Texture* t, int x, int y, int r) {
	DeathRow.push_front( DeadEnemy { t, x, y, r } );
}

void GameObjectManager::DrawDeathRow() {
	for (auto e : DeathRow)
	{
		DeadFrameDst.x = e.posX;
		DeadFrameDst.y = e.posY;
		DeadFrameSrc.y = e.sheetRow * ENEMY_SPRITE_SIZE;
		SDL_RenderCopy(Game::renderer, e.deadTexture, &DeadFrameSrc, &DeadFrameDst);
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

void GameObjectManager::DeleteFlagged() {
	enemies.remove_if(
		[&](const std::unique_ptr<Enemy>& e) { 
			return std::any_of(
				flaggedForDeleteEnemies.begin(), 
				flaggedForDeleteEnemies.end(),
				[&](const Enemy* f) { 
					return e.get() == f; 
				}
			); 
		}
	);
	flaggedForDeleteEnemies.clear();

	items.remove_if([&](
		const std::unique_ptr<Item>& e) {
			return std::any_of(
				flaggedForDeleteItems.begin(), 
				flaggedForDeleteItems.end(),
				[&](const Item* f) { 
					return e.get() == f; 
				}
			);
		}
	);
	flaggedForDeleteItems.clear();

	playerProjectiles.remove_if(
		[&](const std::unique_ptr<Projectile>& e) {
			return std::any_of(
				flaggedForDeleteProjectiles.begin(), 
				flaggedForDeleteProjectiles.end(),
				[&](const Projectile* f) { 
					return e.get() == f; 
				}
			);
		}
	);
	enemyProjectiles.remove_if(
		[&](const std::unique_ptr<Projectile>& e) {
			return std::any_of(
				flaggedForDeleteProjectiles.begin(), 
				flaggedForDeleteProjectiles.end(),
				[&](const Projectile* f) { 
					return e.get() == f; 
				}
			);
		}
	);
	flaggedForDeleteProjectiles.clear();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameObjectManager::CheckEnemyHit(int range, bool right) { // todo: review this
	SDL_Point playerPos = _player->GetCenterPosition();
	SDL_Point enemyPos;
	int distance;
	for (auto& enemy : enemies)
	{
		enemyPos = enemy->GetCenterPosition();
		if (SDL_HasIntersection(playerDestRect, enemy->GetDestRectPtr())) {
			enemy->SendToDeathRow();
			FlagForDelete(enemy.get());
			continue;
		}
		distance = (int)sqrt(pow((playerPos.x - enemyPos.x), 2) + pow((playerPos.y - enemyPos.y), 2));
		if (distance < range)
		{
			if ( right && (playerDestRect->x <= enemyPos.x))
			{
				enemy->SendToDeathRow();
				FlagForDelete(enemy.get());
			}
			else if (!right && (playerDestRect->x + playerDestRect->w >= enemyPos.x))
			{
				enemy->SendToDeathRow();
				FlagForDelete(enemy.get());
			}
		}
	}
}
