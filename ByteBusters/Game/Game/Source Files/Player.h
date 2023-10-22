#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player(int startX, int startY, int targetResW, int targetResH, SDL_Texture* t);
	~Player();

	void Update();
	void Render();

	void SetVelX(int vel);
	void SetVelY(int vel);

private:

	int xvel;
	int yvel;

};