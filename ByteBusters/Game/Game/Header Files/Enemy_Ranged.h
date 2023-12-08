#pragma once
#include "Enemy.h"

class Enemy_Ranged : public Enemy
{
public:
	Enemy_Ranged(int x, int y, int s, SDL_Texture* t); //!< T�pus specifikus konstruktor, poz�ci�, text�ra
	~Enemy_Ranged() {}; //!< Enemy destruktor

	void Update() override; //!< T�pus specifikus Enemy friss�t�s

private:
	void Attack(); //!< Player megt�mad�sa (l�v�s)
	void ShootProjectile(int d); //!< L�v�s

	enum anim { //!< Anim�ci� k�dok
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
