#pragma once
#include "GameObject.h"
#include "Wall.h"
#include <forward_list>

class Projectile : public GameObject
{
public:
	Projectile(int x, int y, int s, int d, SDL_Texture* t, std::forward_list<Wall*>& w); //projectile spawns centered on given position
	~Projectile();
	void Update();
	void Render();

	enum ProjectileDirection {
		up = 3,
		down = 1,
		right = 0,
		left = 2
	};

private:
	int xvel, yvel;
	int speed;
	std::forward_list<Wall*>& walls;

	int frame;
};
