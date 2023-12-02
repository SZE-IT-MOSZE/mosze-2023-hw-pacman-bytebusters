#pragma once
#include "Enemy_Melee.h"
#include "GameObjectManager.h"
//#include "Game.h"
#include "Defines.h"
#include <iostream>

Enemy_Melee::Enemy_Melee(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p) : Enemy(x, y, s, t, w, pr, p) {
	//delete[] enemySheetData; // memory previously allocated in parent constructor. delete first to avoid memory leak
	//not any more. parents enemySheetData is nullptr
	enemySheetData = new int[6][2]{
		{3, 200},
		{3, 200},
		{5, 100},
		{5, 100},
		{3, 200},
		{3, 200},
	};

	visionDistance = tileRes * 5;
	attackDistance = tileRes;
}

Enemy_Melee::~Enemy_Melee() {
	delete[] enemySheetData;
}

void Enemy_Melee::Update() {
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
	if (playerRect->x > destRect->x)
	{
		xvel = 1;
	}
	else if (playerRect->x < destRect->x) {
		xvel = -1;
	}
	else {
		xvel = 0;
	}

	if (playerRect->y > destRect->y)
	{
		yvel = 1;
	}
	else if (playerRect->y < destRect->y) {
		yvel = -1;
	}
	else {
		yvel = 0;
	}
}