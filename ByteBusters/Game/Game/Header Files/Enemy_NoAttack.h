#pragma once
#include "Enemy.h"


class Enemy_NoAttack : public Enemy
{
public:
	Enemy_NoAttack(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p);
	~Enemy_NoAttack();

	void Update() override;

private:
	void RunAway();
};
