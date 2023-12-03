#pragma once
#include "Enemy_Ranged.h"
#include "GameObjectManager.h"
//#include "Game.h"
#include "Defines.h"
#include <iostream>

Enemy_Ranged::Enemy_Ranged(int x, int y, int s, SDL_Texture* t) : Enemy(x, y, s, t) {
	enemySheetData = {
		{3, 200},
		{3, 200},
		{5, 100},
		{5, 100},
		{3, 200},
		{3, 200},
		{3, 200},
		{3, 200}
	};
}

Enemy_Ranged::~Enemy_Ranged() {
}

void Enemy_Ranged::Update() {
	for (auto& projectile : *projectiles)
	{
		if (SDL_HasIntersection(&dstRect, projectile->GetDestRectPtr())) {
			if (auto lockedPtr = gom.lock())
			{
				lockedPtr->FlagForDelete(this);
				lockedPtr->FlagForDelete(projectile.get());
			}
			else
			{
				std::cout << "ATTENTION!!! GAMEOBJECT EXISTS WITHOUT MANAGER!!! \n";
			}
			break;
			break;
		}
	}

	if (uninterruptibleAnimation) return;

	dstRect.x += xvel * speed;

	for (auto& wall : *walls)
	{
		if (SDL_HasIntersection(&dstRect, wall->GetDestRectPtr())) {
			dstRect.x -= xvel * speed;
			break;
		}
	}

	dstRect.y += yvel * speed;

	for (auto& wall : *walls)
	{
		if (SDL_HasIntersection(&dstRect, wall->GetDestRectPtr())) {
			dstRect.y -= yvel * speed;
			break;
		}
	}

	thisPos = GetCenterPosition();
	playerPos = player->GetCenterPosition();

	if ( (playerPos.x >= thisPos.x - tileRes / 2 && playerPos.x <= thisPos.x + tileRes / 2) || (playerPos.y >= thisPos.y - tileRes / 2 && playerPos.y <= thisPos.y + tileRes / 2) )
	{
		if (CheckLineOfSight()) 
		{
			xvel = yvel = 0;
			Attack();
			return;
		}
	}

	Wander();
}

void Enemy_Ranged::Attack(){
	// positions were previously set in Update()
	if (uninterruptibleAnimation) return;
	uninterruptibleAnimation = true;

	if (abs(playerPos.x - thisPos.x) <= tileRes/2)
	{
		if (thisPos.y >= playerPos.y) {
			row = Attack_U;
			ShootProjectile(Projectile::up);
		}
		else if (thisPos.y < playerPos.y)
		{
			row = Attack_D;
			ShootProjectile(Projectile::down);
		}
	}
	else if (abs(playerPos.y - thisPos.y) <= tileRes)
	{
		if (thisPos.x <= playerPos.x) {
			row = Attack_R;
			ShootProjectile(Projectile::right);
		}
		else if (thisPos.x > playerPos.x)
		{
			row = Attack_L;
			ShootProjectile(Projectile::left);
		}
	} 
	//else
	//{
	//	std::cout << "ATTACK WAS CALLED BUT NO PLAYER TO SHOOT" << std::endl;
	//}
}

void Enemy_Ranged::ShootProjectile(int d) {
	if (auto lockedPtr = gom.lock())
	{
		lockedPtr->CreateGameObject(GameObjectManager::enemyProjectile, thisPos.x, thisPos.y, d);
	}
	else
	{
		std::cout << "ATTENTION!!! GAMEOBJECT EXISTS WITHOUT MANAGER!!! \n";
	}
}