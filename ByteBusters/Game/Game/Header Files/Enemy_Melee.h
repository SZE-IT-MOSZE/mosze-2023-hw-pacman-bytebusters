#pragma once
#include "Enemy.h"


class Enemy_Melee : public Enemy
{
public:
	Enemy_Melee(int x, int y, int s, SDL_Texture* t); //!< T�pus specifikus konstruktor, poz�ci�, text�ra
	~Enemy_Melee() {}; //!< Enemy destruktor

	void Update() override; //!< T�pus specifikus Enemy friss�t�s

private:
	void Chase(); //!< Player �ld�z�se
	void Attack(); //!< Player megt�mad�sa (meg�t�se)

	enum anim { //!< Anim�ci� k�dok
		Idle_R = 0,
		Idle_L = 1,
		Run_R = 2,
		Run_L = 3,
		Attack_R = 4,
		Attack_L = 5,
	};

};
