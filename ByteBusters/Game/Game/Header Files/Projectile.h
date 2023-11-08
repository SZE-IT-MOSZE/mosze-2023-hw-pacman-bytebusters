#pragma once
#include "GameObject.h"
#include "Wall.h"
#include <forward_list>

class Projectile : public GameObject
{
public:
	Projectile(int x, int y, int s, int d, SDL_Texture* t, std::forward_list<Wall*>& w);
	~Projectile();
	void Update();
	void Render();

	enum ProjectileDirection {
		up = 1,
		down = 2,
		right = 3,
		left = 4
	};

private:
	int xvel, yvel;
	int speed;
	std::forward_list<Wall*>& walls;

	Uint32 frameStart;	// start of render
	int frameDelay;					// length between two renders of this object in milliseconds
	int i;							// frame counter
};
