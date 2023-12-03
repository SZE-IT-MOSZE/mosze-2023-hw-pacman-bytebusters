#pragma once
#include "Enemy_Melee.h"
#include "GameObjectManager.h"
#include "Defines.h"
#include <iostream>

Enemy_Melee::Enemy_Melee(int x, int y, int s, SDL_Texture* t) : Enemy(x, y, s, t) {
	enemySheetData = {
		{3, 200},
		{3, 200},
		{5, 100},
		{5, 100},
		{3, 200},
		{3, 200},
	};

	visionDistance = tileRes * VISIONDISTANCE;
	attackDistance = tileRes * ATTACKDISTANCE;
}

Enemy_Melee::~Enemy_Melee() {
}

void Enemy_Melee::Update() {
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

	distance = CalculateDistance();

	if (distance > visionDistance) // if too far
	{
		Wander();
		return;
	}

	if (distance < attackDistance) // if close enough
	{
		Attack();
		return;
	}

	if (CheckLineOfSight()) // only check line of sight if player is actually close enough to see and we didnt attack already
	{
		Chase();
	}
}

void Enemy_Melee::Attack() {
	//std::cout << "ATTACK" << std::endl;
	if (uninterruptibleAnimation) return;
	uninterruptibleAnimation = true;
	if (facingRight)
	{
		row = Attack_R;
	}
	else
	{
		row = Attack_L;
	}
	player->DamagePlayer();
}

void Enemy_Melee::Chase() {
	if (playerRect->x > dstRect.x)
	{
		xvel = 1;
	}
	else if (playerRect->x < dstRect.x) {
		xvel = -1;
	}
	else {
		xvel = 0;
	}

	if (playerRect->y > dstRect.y)
	{
		yvel = 1;
	}
	else if (playerRect->y < dstRect.y) {
		yvel = -1;
	}
	else {
		yvel = 0;
	}
}