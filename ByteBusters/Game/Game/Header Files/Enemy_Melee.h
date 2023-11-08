#pragma once
#include "Enemy.h"


class Enemy_Melee : public Enemy
{
public:
	Enemy_Melee(int x, int y, int s, SDL_Texture* t, std::forward_list<Wall*>& w, std::forward_list<Projectile*>& pr, Player* p);
	//~Enemy_Melee();

	void Update();

private:
	void Chase();
	void Attack();


	int enemySheetData[8][2]{
		{3, 200},
		{3, 200},
		{5, 100},
		{5, 100},
		{3, 200},
		{3, 200},
	};

	enum anim {
		Idle_R = 0,
		Idle_L = 1,
		Run_R = 2,
		Run_L = 3,
		Attack_R = 4,
		Attack_L = 5,
	};

};
