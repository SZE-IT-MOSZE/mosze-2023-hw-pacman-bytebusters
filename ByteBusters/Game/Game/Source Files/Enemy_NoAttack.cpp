#pragma once
#include "Enemy_NoAttack.h"
#include "GameObjectManager.h"
//#include "Game.h"
#include "Defines.h"
#include <iostream>


Enemy_NoAttack::Enemy_NoAttack(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p) : Enemy(x, y, s, t, w, pr, p) {
	enemySheetData = new int[4][2]{
		{3, 200},
		{3, 200},
		{5, 100},
		{5, 100},
	};

	visionDistance = TileSize * 5;
}

Enemy_NoAttack::~Enemy_NoAttack() {
	delete[] enemySheetData;
}

void Enemy_NoAttack::Update() {
	for (Projectile* projectile : projectiles)
	{
		if (SDL_HasIntersection(destRect, projectile->GetDestRect())) {
			GameObjectManager::FlagForDelete(this);
			GameObjectManager::FlagForDelete(projectile);
			break;
		}
	}

	//if (uninterruptibleAnimation) return;

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
	if (playerRect->x >= destRect->x)
	{
		xvel = -1;
	}
	else if (playerRect->x < destRect->x) {
		xvel = 1;
	}

	if (playerRect->y >= destRect->y)
	{
		yvel = -1;
	}
	else if (playerRect->y < destRect->y) {
		yvel = 1;
	}
}