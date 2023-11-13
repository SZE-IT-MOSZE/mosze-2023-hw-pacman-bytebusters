#pragma once
#include "Projectile.h"
#include "GameObjectManager.h"
#include <iostream>
#include "Game.h"
#include "Defines.h"




Projectile::Projectile(int x, int y, int s, int d, SDL_Texture* t, std::forward_list<Wall*>& w) : walls(w), GameObject(x - (TileSize / PROJECTILE_SIZE_REDUCTION) / 2, y - (TileSize / PROJECTILE_SIZE_REDUCTION) / 2)
//projectile spawns centered on given position
{

	objTexture = t;

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

	destRect->w = destRect->h = TileSize / PROJECTILE_SIZE_REDUCTION;
	srcRect->w = srcRect->h = PROJECTILE_SPRITE_SIZE;

	speed = s * TileSize / DIVIDE_BY_THIS;

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

void Projectile::Render() {
	srcRect->x = frame * PROJECTILE_SPRITE_SIZE; //set the frame to display
	SDL_RenderCopy(Game::renderer, objTexture, srcRect, destRect);
}