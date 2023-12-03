#pragma once
#include "GameObject.h"
#include "Wall.h"
#include <forward_list>

class Projectile : public GameObject
{
public:
	//projectile spawns centered on given position
	Projectile(int x, int y, int s, int d, SDL_Texture* t); 
	~Projectile();
	void Update() override;
	void Render() override;

	enum ProjectileDirection {
		up = 3,
		down = 1,
		right = 0,
		left = 2
	};

private:
	int xvel, yvel;
	int speed;
	const std::forward_list<std::unique_ptr<Wall>>* walls;

	int frame;
};
