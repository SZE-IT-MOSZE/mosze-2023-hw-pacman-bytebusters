#pragma once
#include "Enemy_Ranged.h"
#include "GameObjectManager.h"
//#include "Game.h"
#include "Defines.h"
#include <iostream>

Enemy_Ranged::Enemy_Ranged(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p) : Enemy(x, y, s, t, w, pr, p) {

}

void Enemy_Ranged::Update() {
	for (Projectile* projectile : projectiles)
	{
		if (SDL_HasIntersection(destRect, projectile->GetDestRect())) {
			GameObjectManager::FlagForDelete(this);
			GameObjectManager::FlagForDelete(projectile);
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

	if ( (playerPosX >= posX - TileSize / 2 && playerPosX <= posX + TileSize / 2) || (playerPosY >= posY - TileSize / 2 && playerPosY <= posY + TileSize / 2) )
	{
		if (CheckLineOfSight()) 
		{
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
	if (playerPosX - posX <= TileSize)
	{
		if (posY > playerPosY) {
			GameObjectManager::CreateGameObject(GameObjectManager::projectile, posX, posY, Projectile::up);
			row = Attack_U;
		}
		else
		{
			GameObjectManager::CreateGameObject(GameObjectManager::projectile, posX, posY, Projectile::down);
			row = Attack_D;
		}
	}
	else if (playerPosY - posY <= TileSize)
	{
		if (posX > playerPosX) {
			GameObjectManager::CreateGameObject(GameObjectManager::projectile, posX, posY, Projectile::right);
			row = Attack_R;
		}
		else
		{
			GameObjectManager::CreateGameObject(GameObjectManager::projectile, posX, posY, Projectile::left);
			row = Attack_L;
		}
	} 
	else
	{
		std::cout << "ATTACK WAS CALLED BUT NO PLAYER TO SHOOT" << std::endl;
	}
}