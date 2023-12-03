#pragma once
#include "Projectile.h"
#include "GameObjectManager.h"
#include <iostream>
#include "Game.h"
#include "Defines.h"




//projectile spawns centered on given position
Projectile::Projectile(int x, int y, int s, int d, SDL_Texture* t) : GameObject(x - (tileRes / PROJECTILE_SIZE_REDUCTION) / 2, y - (tileRes / PROJECTILE_SIZE_REDUCTION) / 2)
{
	objTexture = t;

	if (auto lockedPtr = gom.lock())
	{
		walls = lockedPtr->GetWalls();
	}
	else
	{
		std::cout << "ATTENTION!!! GAMEOBJECT EXISTS WITHOUT MANAGER!!! \n";
	}

	xvel = yvel = 0;
	switch (d)
	{
	case up:
		frame = up;
		yvel = -1;
		break;
	case down:
		frame = down;
		yvel = 1;
		break;
	case left:
		frame = left;
		xvel = -1;
		break;
	case right:
		frame = right;
		xvel = 1;
		break;
	default:
		frame = up;
		break;
	}

	dstRect.w = dstRect.h = tileRes / PROJECTILE_SIZE_REDUCTION;
	srcRect.w = srcRect.h = PROJECTILE_SPRITE_SIZE;

	//todo, destrect to actual position

	speed = s * tileRes / DIVIDE_BY_THIS;
	/*std::cout << "speed: " << speed << std::endl;
	if (speed > PROJECTILESPRITESIZE)
	{
		std::cout << "TOO HIGH PROJECTILE SPEED!!!" << std::endl;
	}*/

}

Projectile::~Projectile()
{
	//std::cout << "Projectile destructor called" << std::endl;
}

void Projectile::Update()
{
	dstRect.x += xvel * speed;
	dstRect.y += yvel * speed;
	for (auto& wall : *walls)
	{
		if (SDL_HasIntersection(&dstRect, wall->GetDestRectPtr())) {
			if (auto lockedPtr = gom.lock())
			{
				lockedPtr->FlagForDelete(this);
			}
			else
			{
				std::cout << "ATTENTION!!! GAMEOBJECT EXISTS WITHOUT MANAGER!!! \n";
			}
			return;
		}
	}
}

void Projectile::Render() {
	srcRect.x = frame * PROJECTILE_SPRITE_SIZE; //set the frame to display
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &dstRect);
}