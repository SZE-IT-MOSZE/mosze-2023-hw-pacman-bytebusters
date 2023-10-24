#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
	Player(int x, int y, SDL_Texture* t);
	~Player();

	void Update();
	void Render();

	void SetVelX(int vel);
	void SetVelY(int vel);

	SDL_Rect* getDestRect() { return destRect; }

private:

	int xvel;
	int yvel;

};