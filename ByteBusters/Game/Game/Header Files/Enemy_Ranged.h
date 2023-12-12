#pragma once
#include "Enemy.h"

class Enemy_Ranged : public Enemy
{
public:
	Enemy_Ranged(int x, int y, int s, SDL_Texture* t); //!< Típus specifikus konstruktor, pozíció, textúra
	~Enemy_Ranged() {}; //!< Enemy destruktor

	void Update() override; //!< Típus specifikus Enemy frissítés

private:
	void Attack(); //!< Player megtámadása (lövés)
	void ShootProjectile(int d); //!< Lövés

	enum anim { //!< Animáció kódok
		Idle_R = 0,
		Idle_L = 1,
		Run_R = 2,
		Run_L = 3,
		Attack_R = 4,
		Attack_L = 5,
		Attack_D = 6,
		Attack_U = 7
	};
};
