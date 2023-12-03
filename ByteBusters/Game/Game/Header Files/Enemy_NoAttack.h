#pragma once
#include "Enemy.h"


class Enemy_NoAttack : public Enemy
{
public:
	Enemy_NoAttack(int x, int y, int s, SDL_Texture* t);
	~Enemy_NoAttack();

	void Update() override;

private:
	void RunAway();
};
