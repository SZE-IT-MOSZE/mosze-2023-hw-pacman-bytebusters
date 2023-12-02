#pragma once
#include "Enemy.h"
//#include "GameObjectManager.h"
#include "Game.h"
#include <iostream>
#include "Defines.h"


Enemy::Enemy(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p) : walls(w), projectiles(pr), GameObject(x, y) {
	objTexture = t;

	player = p;
	playerRect = player->GetDestRect();

	playerPosX = playerPosY = 0;
	posX = posY = 0;

	xvel = yvel = 0;
	

	speed = s * tileRes / DIVIDE_BY_THIS;

	distance = 0;
	visionDistance = 0;
	attackDistance = 0;

	uninterruptibleAnimation = false;

	frameStart = SDL_GetTicks();	// start of render
	frameDelay = 0;					// length between two renders of this object in milliseconds
	frameCounter = 0;				// frame counter
	row = 0;						// animation to display
	facingRight = true;

	enemySheetData = nullptr;

}

Enemy::~Enemy() {

}

//bool printed = false;
void Enemy::Render() {
	frameDelay = SDL_GetTicks() - frameStart;
	if (frameDelay > enemySheetData[row][1]) // if time to display next frame
	{

		//if (true /*!printed*/)
		//{
		//	for (size_t i = 0; i < std::size(enemySheetData); i++)
		//	{
		//		for (size_t j = 0; j < std::size(enemySheetData[i]); j++)
		//		{
		//			std::cout << "[" << enemySheetData[i][j] << "]";
		//		}
		//		std::cout << std::endl;
		//	}
		//	std::cout << std::endl;
		//	printed = true;
		//}

		/*std::cout << "ROW:    " << row << std::endl;
		std::cout << "FRAMES: " << enemySheetData[row][0] << std::endl;
		std::cout << "DELAY:  " << enemySheetData[row][1] << std::endl;*/


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

		if (srcRect->y != row * ENEMY_SPRITE_SIZE) { // if animation change happened
			frameCounter = 0;	// reset counter
			srcRect->y = row * ENEMY_SPRITE_SIZE; // set new animation
		}
		else // if not
		{
			frameCounter++; // increment frames
			if (frameCounter >= enemySheetData[row][0]) // dont go past last frame (only need to check if incremented frames. everything has a first [0] frame)
			{
				frameCounter = 0; // return to first frame
				uninterruptibleAnimation = false; // the animation has finished
			}

		}
		srcRect->x = frameCounter * ENEMY_SPRITE_SIZE; // finally, set the frame to display
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
	return (int)sqrt( pow( (playerPosX - posX), 2) + pow( (playerPosY - posY), 2) ); // math class was useful after all
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
