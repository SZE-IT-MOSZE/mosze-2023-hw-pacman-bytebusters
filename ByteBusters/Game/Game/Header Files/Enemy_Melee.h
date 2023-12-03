#pragma once
#include "Enemy.h"


class Enemy_Melee : public Enemy
{
public:
	Enemy_Melee(int x, int y, int s, SDL_Texture* t);
	~Enemy_Melee();

	void Update() override;

private:
	void Chase();
	void Attack();

	enum anim {
		Idle_R = 0,
		Idle_L = 1,
		Run_R = 2,
		Run_L = 3,
		Attack_R = 4,
		Attack_L = 5,
	};

};
