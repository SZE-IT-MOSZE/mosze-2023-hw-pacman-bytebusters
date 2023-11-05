#include "Projectile.h"
#include "GameObjectManager.h"
#include <iostream>

enum direction {
	up = 1,
	down = 2,
	right = 3,
	left = 4
};

Projectile::Projectile(int x, int y, int d, SDL_Texture* t, std::forward_list<Wall*>& w) : walls(w), GameObject(x, y)
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
}

Projectile::~Projectile()
{
	std::cout << "Projectile destructor called" << std::endl;
}

void Projectile::Update()
{
	destRect->x += xvel;
	destRect->y += yvel;
	for (Wall* wall : walls)
	{
		if (SDL_HasIntersection(destRect, wall->GetDestRect())) {
			GameObjectManager::FlagForDelete(this);
			return;
		}
	}
}