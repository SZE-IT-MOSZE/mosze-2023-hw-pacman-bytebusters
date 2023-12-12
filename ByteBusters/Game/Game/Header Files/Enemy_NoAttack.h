#pragma once
#include "Enemy.h"


class Enemy_NoAttack : public Enemy
{
public:
	Enemy_NoAttack(int x, int y, int s, SDL_Texture* t); //!< T�pus specifikus konstruktor, poz�ci�, text�ra
	~Enemy_NoAttack() {}; //!< Enemy destruktor

	void Update() override; //!< T�pus specifikus Enemy friss�t�s

private:
	void RunAway(); //!< Menek�l�s Player el�l
};
