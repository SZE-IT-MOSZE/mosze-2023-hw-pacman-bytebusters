#pragma once
#include "Enemy.h"


class Enemy_Melee : public Enemy
{
public:
	Enemy_Melee(int x, int y, int s, SDL_Texture* t); //!< Típus specifikus konstruktor, pozíció, textúra
	~Enemy_Melee() {}; //!< Enemy destruktor

	void Update() override; //!< Típus specifikus Enemy frissítés

private:
	void Chase(); //!< Player üldözése
	void Attack(); //!< Player megtámadása (megütése)

	enum anim { //!< Animáció kódok
		Idle_R = 0,
		Idle_L = 1,
		Run_R = 2,
		Run_L = 3,
		Attack_R = 4,
		Attack_L = 5,
	};

};
