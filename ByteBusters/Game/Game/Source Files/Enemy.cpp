#pragma once
#include "Game.h"
#include "Enemy.h"
#include "Defines.h"
#include <iostream>


Enemy::Enemy(int x, int y, int s, SDL_Texture* t) : GameObject(x, y) {

	objTexture = t;

	newRow = 0;
	player = nullptr;
	playerPos.x = playerPos.y = 0;
	thisPos.x = thisPos.y = 0;
	playerDestRect = nullptr;
	projectiles = nullptr;
	walls = nullptr;

	if (auto lockedPtr = gom.lock())
	{
		player = lockedPtr->GetPlayer();
		playerDestRect = player->GetDestRectPtr();
		walls = lockedPtr->GetWalls();
		projectiles = lockedPtr->GetPlayerProjectiles();
	}

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

}

void Enemy::Render() {
	frameDelay = SDL_GetTicks() - frameStart;

	if (!uninterruptibleAnimation) { // if there is no uninterruptible animation
		if (xvel == 1)
		{
			facingRight = true;
		}
		else if (xvel == -1)
		{
			facingRight = false;
		}

		if (xvel == 0 && yvel == 0) // if standing still
		{
			if (facingRight) // faced right last time
			{
				newRow = Idle_R;
			}
			else // faced left last time
			{
				newRow = Idle_L;
			}
		}
		else // if moving
		{
			if (facingRight) // faced right last time
			{
				newRow = Run_R;
			}
			else // faced left last time
			{
				newRow = Run_L;
			}
		}
	}

	if (frameDelay > enemySheetData[row][1] || newRow != row) // if time to display next frame OR a change has happened
	{
		
		frameStart = SDL_GetTicks();

		if (newRow != row) { // if animation change happened
			row = newRow; // set new row
			frameCounter = 0;	// reset counter
			srcRect.y = row * ENEMY_SPRITE_SIZE; // set new animation
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
		srcRect.x = frameCounter * ENEMY_SPRITE_SIZE; // finally, set the frame to display
	}

	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &dstRect);
}

int Enemy::CalculateDistance() {
	playerPos = player->GetCenterPosition();
	thisPos = GetCenterPosition();
	return (int)sqrt( pow( (playerPos.x - thisPos.x), 2) + pow( (playerPos.y - thisPos.y), 2) ); // math class was useful after all
}

bool Enemy::CheckLineOfSight() {
	playerPos = player->GetCenterPosition();
	thisPos = GetCenterPosition();
	for (auto& wall : *walls)
	{
		if (SDL_IntersectRectAndLine(wall->GetDestRectPtr(), &(playerPos.x), &(playerPos.y), &(thisPos.x), &(thisPos.y))) {
			return false;
		}
	}
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

void Enemy::SendToDeathRow() {
	if (auto lockedPtr = gom.lock())
	{
		// .size() should be after the end if interpreted as an index, 
		// but the spritesheet data does not contain the last row where the the static image is, so it points to exactly that
		lockedPtr->PushToDeathRow(objTexture, dstRect.x, dstRect.y, (int)(enemySheetData.size())); 
	}
}