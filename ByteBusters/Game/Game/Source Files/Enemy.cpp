#pragma once
#include "Enemy.h"
//#include "GameObjectManager.h"
#include "Game.h"
#include <iostream>
#include "Defines.h"


Enemy::Enemy(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p) : walls(w), projectiles(pr), GameObject(x, y) {
	objTexture = t;

	player = p;
	playerRect = player->getDestRect();

	xvel = 0;
	yvel = 0;

	speed = s * TileSize / DIVIDEBYTHIS;

	visionDistance = TileSize * 5;
	attackDistance = TileSize * 1;

	uninterruptibleAnimation = false;

	frameStart = SDL_GetTicks();	// start of render
	frameDelay = 0;					// length between two renders of this object in milliseconds
	frameCounter = 0;				// frame counter
	row = 0;						// animation to display

}

Enemy::~Enemy() {
	std::cout << "enemy destructor called" << std::endl;
}

void Enemy::Update() {

}

void Enemy::Render() {
	frameDelay = SDL_GetTicks() - frameStart;
	if (frameDelay > sheetData[row][1]) // if time to display next frame
	{
		frameStart = SDL_GetTicks();

		if (!uninterruptibleAnimation) // if NOT playing Shoot or Hit
		{
			if (xvel == 1) // if going right
			{
				facingRight = true;
				row = Run_R;
			}
			else if (xvel == -1) // if going left
			{
				facingRight = false;
				row = Run_L;
			}
			else if (yvel != 0) // if NOT going right/left BUT going up/down
			{
				if (facingRight) // last direction the character was facing
				{
					row = Run_R;
				}
				else
				{
					row = Run_L;
				}
			}
			else // if NOT moving at all
			{
				if (facingRight) // last direction the enemy was facing
				{
					row = Idle_R;
				}
				else
				{
					row = Idle_L;
				}
			}
		}

		if (srcRect->y != row * ENEMYSPRITESIZE) { // if animation change happened
			frameCounter = 0;	// reset counter
			srcRect->y = row * ENEMYSPRITESIZE; // set new animation
		}
		else // if not
		{
			frameCounter++; // increment frames
			if (frameCounter >= sheetData[row][0]) // dont go past last frame (only need to check if incremented frames. everything has a first [0] frame)
			{
				frameCounter = 0; // return to first frame
				uninterruptibleAnimation = false; // the animation has finished
			}

		}
		srcRect->x = frameCounter * ENEMYSPRITESIZE; // finally, set the frame to display
	}

	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
}

void Enemy::CalculatePositions() {
	playerPosX = playerRect->x + playerRect->w / 2;
	playerPosY = playerRect->y + playerRect->h / 2;

	posX = destRect->x + destRect->w / 2;
	posY = destRect->y + destRect->h / 2;
}

int Enemy::CalculateDistance() {
	//std::cout << playerPosX << "," << playerPosY << " | " << posX << "," << posY << " | " << "dist: " << distance << std::endl;
	return sqrt( pow( (playerPosX - posX), 2) + pow( (playerPosY - posY), 2) ); // math class was useful after all
}

bool Enemy::CheckLineOfSight() {

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

int rnd = 0;
void Enemy::Wander() {

	if (rnd)
	{
		rnd--;
		return;
	}

	rnd = rand() % (2 * _UPS);
	//std::cout << rnd << std::endl;
	int rndForVel = rand() % 9;
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
	case 8:
		xvel = 0;
		yvel = 0;
		break;
	default:
		break;
	}
}
