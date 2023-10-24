#include "Enemy.h"
#include "TextureManager.h"
#include "Game.h"
#include <iostream>

Enemy::Enemy(int x, int y, SDL_Texture* t, Player* p) : GameObject::GameObject(x, y) {
	objTexture = t;

	player = p;

	playerRect = player->getDestRect();

	xvel = 0;
	yvel = 0;

	srand(time(NULL));
}

Enemy::~Enemy() {
	std::cout << "enemy destructor called" << std::endl;

	delete destRect;
}

void Enemy::Update() {
	destRect->x += xvel;

	for (SDL_Rect* wall : Map::mapWalls)
	{
		if (SDL_HasIntersection(destRect, wall)) { // again, walls
			destRect->x -= xvel;
			break;
		}
	}

	destRect->y += yvel;

	for (SDL_Rect* wall : Map::mapWalls)
	{
		if (SDL_HasIntersection(destRect, wall)) { // again, walls
			destRect->y -= yvel;
			break;
		}
	}
	if (CheckLineOfSight())
	{
		Enemy::Chase();
	}
	else {
		Enemy::Wander();
	}


}

void Enemy::Render() {

	//std::cout << "enemy render" << std::endl;
	SDL_RenderCopy(Game::renderer, objTexture, NULL, destRect);
	SDL_RenderDrawLine(Game::renderer, playerPosX, playerPosY, posX, posY);
}

bool Enemy::CheckLineOfSight() {
	if (!player)
	{
		return false;
	}

	playerPosX = playerRect->x + playerRect->w / 2;
	playerPosY = playerRect->y + playerRect->h / 2;

	posX = destRect->x + destRect->w / 2;
	posY = destRect->y + destRect->h / 2;

	//

	for (SDL_Rect* wall : Map::mapWalls)
	{
		if (SDL_IntersectRectAndLine(wall, &playerPosX, &playerPosY, &posX, &posY)) {
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
void Enemy::Wander() { // make counter for how many fraes later it start to wander then substract counter 1 each frame

	if (rnd)
	{
		rnd--;
		return;
	}

	rnd = rand() % 2000;
	int rndForVel = rand() % 5;
	switch (rndForVel)
	{
	case 0:
		xvel = 0;
		break;
	case 1:
		xvel = 1;
		break;
	case 2:
		xvel = -1;
		break;
	case 3:
		yvel = 0;
		break;
	case 4:
		yvel = 1;
		break;
	case 5:
		yvel = -1;
		break;
	default:
		break;
	}
}