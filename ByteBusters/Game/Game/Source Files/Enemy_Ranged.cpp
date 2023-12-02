#pragma once
#include "Enemy_Ranged.h"
#include "GameObjectManager.h"
//#include "Game.h"
#include "Defines.h"
#include <iostream>

Enemy_Ranged::Enemy_Ranged(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p) : Enemy(x, y, s, t, w, pr, p) {
	//delete[] enemySheetData; // memory previously allocated in parent constructor. delete first to avoid memory leak
	//not any more. parents enemySheetData is nullptr
	enemySheetData = new int[8][2]{
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
	delete[] enemySheetData;
}

void Enemy_Ranged::Update() {
	for (Projectile* projectile : projectiles)
	{
		if (SDL_HasIntersection(destRect, projectile->GetDestRect())) {
			if (auto lockedPtr = gom.lock())
			{
				lockedPtr->FlagForDelete(this);
				lockedPtr->FlagForDelete(projectile);
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

	destRect->x += xvel * speed;

	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			destRect->x -= xvel * speed;
			break;
		}
	}

	destRect->y += yvel * speed;

	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			destRect->y -= yvel * speed;
			break;
		}
	}

	CalculatePositions(); // CALL FIRST !!!!!!!!!

	if ( (playerPosX >= posX - tileRes / 2 && playerPosX <= posX + tileRes / 2) || (playerPosY >= posY - tileRes / 2 && playerPosY <= posY + tileRes / 2) )
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
	if (uninterruptibleAnimation) return;
	uninterruptibleAnimation = true;

	CalculatePositions();
	if (abs(playerPosX - posX) <= tileRes/2)
	{
		if (posY >= playerPosY) {
			row = Attack_U;
			ShootProjectile(Projectile::up);
		}
		else if (posY < playerPosY)
		{
			row = Attack_D;
			ShootProjectile(Projectile::down);
		}
	}
	else if (abs(playerPosY - posY) <= tileRes)
	{
		if (posX <= playerPosX) {
			row = Attack_R;
			ShootProjectile(Projectile::right);
		}
		else if (posX > playerPosX)
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
		lockedPtr->CreateGameObject(GameObjectManager::enemyProjectile, posX, posY, d);
	}
	else
	{
		std::cout << "ATTENTION!!! GAMEOBJECT EXISTS WITHOUT MANAGER!!! \n";
	}
}