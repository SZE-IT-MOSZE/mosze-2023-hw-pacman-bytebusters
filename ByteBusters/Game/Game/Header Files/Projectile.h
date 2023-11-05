#pragma once
#include "GameObject.h"
#include "Wall.h"
#include <forward_list>

class Projectile : public GameObject
{
public:
	Projectile(int x, int y, int d, SDL_Texture* t, std::forward_list<Wall*>& w);
	~Projectile();
	void Update();

private:
	int xvel, yvel;
	std::forward_list<Wall*>& walls;

};
