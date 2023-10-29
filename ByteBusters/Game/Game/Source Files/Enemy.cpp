#pragma once
#include "Enemy.h"
#include "GameObjectManager.h"
#include "Game.h"
#include <iostream>

Enemy::Enemy(int x, int y, SDL_Texture* t, std::forward_list<Wall*>& w, Player* p) : walls(w), GameObject(x, y) {
	objTexture = t;

	player = p;
	playerRect = player->getDestRect();

	xvel = 0;
	yvel = 0;


	srand(time(NULL));

	/*std::cout << "-------------------------------" << std::endl;
	for (size_t i = 0; i < 10; i++)
	{
		std::cout << rand() << std::endl;
	}
	std::cout << "-------------------------------" << std::endl;*/

	visionDistance = TileSize * 5;
}

Enemy::~Enemy() {
	std::cout << "enemy destructor called" << std::endl;
}

void Enemy::Update() {
	destRect->x += xvel;

	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			destRect->x -= xvel;
			break;
		}
	}

	destRect->y += yvel;

	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			destRect->y -= yvel;
			break;
		}
	}

	if (CheckLineOfSight())
	{
		Chase();
	}
	else {
		Wander();
	}


}

void Enemy::Render() {

	//std::cout << "enemy render" << std::endl;
	SDL_RenderCopy(Game::renderer, objTexture, NULL, destRect);
	
}

bool Enemy::CheckLineOfSight() {

	playerPosX = playerRect->x + playerRect->w / 2;
	playerPosY = playerRect->y + playerRect->h / 2;

	posX = destRect->x + destRect->w / 2;
	posY = destRect->y + destRect->h / 2;

	int distance = sqrt( pow( (playerPosX - posX), 2) + pow( (playerPosY - posY), 2) );
	//std::cout << playerPosX << "," << playerPosY << " | " << posX << "," << posY << " | " << "dist: " << distance << std::endl;
	

	if (distance > visionDistance)
	{
		//std::cout << "False" << std::endl;
		return false;
	}
	
	for (Wall* wall : walls)
	{
		if (SDL_IntersectRectAndLine(wall->GetDestRect(), &playerPosX, &playerPosY, &posX, &posY)) {
			
			//std::cout << "False" << std::endl;
			return false;
		}
	}
	
	//std::cout << "True" << std::endl;
	return true;
}

void Enemy::Chase() {
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

int rnd = 0;
void Enemy::Wander() {

	if (rnd)
	{
		rnd--;
		return;
	}

	rnd = rand() % 2000;
	//std::cout << rnd << std::endl;
	int rndForVel = rand() % 8;
	switch (rndForVel)
	{
	case 0:
		xvel = 0;
		yvel = -1;
		break;
	case 1:
		xvel = 1;
		yvel = -1;
		break;
	case 2:
		xvel = 1;
		yvel = 0;
		break;
	case 3:
		xvel = 1;
		yvel = 1;
		break;
	case 4:
		xvel = 0;
		yvel = 1;
		break;
	case 5:
		xvel = -1;
		yvel = 1;
		break;
	case 6:
		xvel = -1;
		yvel = 0;
		break;
	case 7:
		xvel = -1;
		yvel = -1;
		break;
	default:
		break;
	}
}