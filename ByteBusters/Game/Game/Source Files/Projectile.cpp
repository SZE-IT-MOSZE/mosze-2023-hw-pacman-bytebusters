#pragma once
#include "Projectile.h"
#include "GameObjectManager.h"
#include <iostream>
#include "Game.h"
#include "Defines.h"


enum direction {
	up = 1,
	down = 2,
	right = 3,
	left = 4
};

Projectile::Projectile(int x, int y, int s, int d, SDL_Texture* t, std::forward_list<Wall*>& w) : walls(w), GameObject(x, y)
{
	objTexture = t;

	xvel = yvel = 0;
	switch (d)
	{
	case up:
		yvel = -1;
		break;
	case down:
		yvel = 1;
		break;
	case left:
		xvel = -1;
		break;
	case right:
		xvel = 1;
		break;
	default:
		break;
	}

	srcRect->w = srcRect->h = PROJECTILESPRITESIZE;

	frameStart = SDL_GetTicks();	// start of render
	frameDelay = 0;					// length between two renders of this object in milliseconds
	i = 0;							// frame counter

	speed = s * TileSize / DIVIDEBYTHIS;

}

Projectile::~Projectile()
{
	std::cout << "Projectile destructor called" << std::endl;
}

void Projectile::Update()
{
	destRect->x += xvel * speed;
	destRect->y += yvel * speed;
	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			GameObjectManager::FlagForDelete(this);
			return;
		}
	}
}

int sheetData[2] = { 2, 100 };

void Projectile::Render() {
	frameDelay = SDL_GetTicks() - frameStart;
	if (frameDelay > sheetData[1]) // if time to display next frame
	{
		frameStart = SDL_GetTicks();
		
		i++; // increment frames
		if (i >= sheetData[0]) // dont go past last frame
		{
			i = 0; // return to first frame
		}

		srcRect->x = i * PROJECTILESPRITESIZE; // finally, set the frame to display
	}

	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
}