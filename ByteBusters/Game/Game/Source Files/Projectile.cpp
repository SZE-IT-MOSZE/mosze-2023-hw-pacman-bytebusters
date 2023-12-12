#pragma once
#include "Game.h"
#include "Defines.h"
#include "Projectile.h"
#include "GameObjectManager.h"
#include <iostream>

enum projectileFrameDirection {
	up = 3,
	down = 1,
	right = 0,
	left = 2
};

//projectile spawns centered on given position
Projectile::Projectile(int x, int y, int s, int d, SDL_Texture* t) : GameObject(x , y) // <- tileRes wont work here
{
	objTexture = t;

	dstRect.x -= (tileRes / PROJECTILE_SIZE_REDUCTION) / 2; // tileRes is not known before GameObject constructor gets called
	dstRect.y -= (tileRes / PROJECTILE_SIZE_REDUCTION) / 2; // tileRes is not known before GameObject constructor gets called

	walls = nullptr;

	if (auto lockedPtr = gom.lock())
	{
		walls = lockedPtr->GetWalls();
	}

	xvel = yvel = 0;
	switch (d)
	{
	case GameObjectManager::up:
		frame = up;
		yvel = -1;
		break;
	case GameObjectManager::down:
		frame = down;
		yvel = 1;
		break;
	case GameObjectManager::left:
		frame = left;
		xvel = -1;
		break;
	case GameObjectManager::right:
		frame = right;
		xvel = 1;
		break;
	default:
		frame = up;
		break;
	}
	srcRect.x = frame * PROJECTILE_SPRITE_SIZE; //set the frame to display

	dstRect.w = dstRect.h = tileRes / PROJECTILE_SIZE_REDUCTION;
	srcRect.w = srcRect.h = PROJECTILE_SPRITE_SIZE;

	speed = s * tileRes / DIVIDE_BY_THIS;

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
			return;
		}
	}
}

void Projectile::Render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &dstRect);
}