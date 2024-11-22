#pragma once
#include "Defines.h"
#include "Enemy_NoAttack.h"
#include "GameObjectManager.h"
#include <iostream>

Enemy_NoAttack::Enemy_NoAttack(int x, int y, int s, SDL_Texture* t) : Enemy(x, y, s, t) {
	enemySheetData = {
		{3, 200},
		{3, 200},
		{5, 100},
		{5, 100},
	};

	visionDistance = tileRes * VISIONDISTANCE;
}

void Enemy_NoAttack::Update() {
	for (auto& projectile : *projectiles)
	{
		if (SDL_HasIntersection(&dstRect, projectile->GetDestRectPtr())) {
			SendToDeathRow();
			if (auto lockedPtr = gom.lock())
			{
				lockedPtr->FlagForDelete(this);
				lockedPtr->FlagForDelete(projectile.get());
			}
			break;
		}
	}

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

	if (distance < visionDistance)
	{
		RunAway();
	}
	else {
		Wander();
	}
}

void Enemy_NoAttack::RunAway() {
	if (playerDestRect->x >= dstRect.x)
	{
		xvel = -1;
	}
	else if (playerDestRect->x < dstRect.x) {
		xvel = 1;
	}

	if (playerDestRect->y >= dstRect.y)
	{
		yvel = -1;
	}
	else if (playerDestRect->y < dstRect.y) {
		yvel = 1;
	}
}