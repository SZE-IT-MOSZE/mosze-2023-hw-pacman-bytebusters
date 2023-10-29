#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Wall.h"
#include <time.h>
#include <forward_list>


class Enemy : public GameObject {
public:
	Enemy(int x, int y, SDL_Texture* t, std::forward_list<Wall*>& w, Player* p);
	~Enemy();

	void Update();
	void Render();

private:
	Player* player; //player is still a pointer. only lists are references
	SDL_Rect* playerRect;
	std::forward_list<Wall*>& walls;

	bool CheckLineOfSight();
	void Chase();
	void Wander();

	int xvel, yvel;

	int playerPosX, playerPosY;
	int posX, posY;

	int visionDistance;

};