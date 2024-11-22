#pragma once
#include "Enemy.h"


class Enemy_NoAttack : public Enemy
{
public:
	Enemy_NoAttack(int x, int y, int s, SDL_Texture* t); //!< Típus specifikus konstruktor, pozíció, textúra
	~Enemy_NoAttack() {}; //!< Enemy destruktor

	void Update() override; //!< Típus specifikus Enemy frissítés

private:
	void RunAway(); //!< Menekülés Player elõl
};
