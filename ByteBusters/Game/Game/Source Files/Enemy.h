#pragma once
#include "GameObject.h"
#include <time.h>
#include "Player.h"

class Enemy : public GameObject {
public:
	Enemy(int startX, int startY, int targetResW, int targetResH, SDL_Texture* t, Player* p);
	~Enemy();

	void Update();
	void Render();
	//void UpdatePlayerPosition();

private:
	GameObject* player;
	SDL_Rect* playerRect;

	void SetVelX(int vel);
	void SetVelY(int vel);

	bool CheckLineOfSight();
	void Chase();
	void Wander();

	int xvel, yvel;

	int playerPosX, playerPosY;
	int posX, posY;

};