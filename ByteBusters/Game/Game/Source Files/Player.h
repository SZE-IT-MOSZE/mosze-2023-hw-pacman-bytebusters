#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player(int startX, int startY, int targetResW, int targetResH);
	~Player();

	void Update();

	void SetVelX(int vel);
	void SetVelY(int vel);

private:

	int xvel;
	int yvel;

};