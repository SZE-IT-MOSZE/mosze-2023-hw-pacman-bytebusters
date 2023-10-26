#pragma once
#include "GameObject.h"
#include <time.h>
#include "Player.h"

class Enemy : public GameObject {
public:
	Enemy(int x, int y, SDL_Texture* t, Player* p);
	~Enemy();

	void Update();
	void Render();

private:
	Player* player;
	SDL_Rect* playerRect;

	bool CheckLineOfSight();
	void Chase();
	void Wander();

	int xvel, yvel;

	int playerPosX, playerPosY;
	int posX, posY;

};